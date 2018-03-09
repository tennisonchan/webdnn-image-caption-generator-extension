# -*- coding: utf-8 -*-

"""
Converts model for WebDNN to run on web browser

1. ResNet feature extractor + image feature embedding
2. Sentence generator

Targeting for WebDNN 1.1.0.
It does not support LSTM layer's conversion and input switching (image feature / word vector),
so constructing IR manually is needed.

Model 1:
[image] -> ResNet-50 -> image_vec -> [image_embedded_feature]

Model 2:
[image_embedded_feature] -> ElementwiseMul |
                                           |-> ElementwiseSum -> lstm -> out_word -> [word_probability]
[word id] -> word_vec    -> ElementwiseMul |

ElementwiseMul is used as switch for selecting which input is supplied to LSTM.
When image_embedded_feature is used, corresponding multiplication value is set to 1, otherwise, 0.
image_vec layer is used in model 1 to reduce unnecessary computation in model 2.
"""

import argparse
import json
import os
import sys
import pickle

import chainer
import chainer.computational_graph
import numpy as np

from webdnn.backend.interface.generator import generate_descriptor
from webdnn.graph.axis import Axis
from webdnn.graph.graph import Graph
from webdnn.graph.operators.axiswise_bias import AxiswiseBias
from webdnn.graph.operators.elementwise_mul import ElementwiseMul
from webdnn.graph.operators.elementwise_sum import ElementwiseSum
from webdnn.graph.operators.linear import Linear
from webdnn.graph.operators.lstm import LSTM
from webdnn.graph.operators.softmax import Softmax
from webdnn.graph.order import OrderNC, OrderC, OrderCN, OrderNTC, OrderNT
from webdnn.graph.traverse import dump_dot
from webdnn.graph.variable import Variable
from webdnn.graph.variables.constant_variable import ConstantVariable
from webdnn.graph.operators.embedding import Embedding
from webdnn.frontend.chainer.converter import ChainerConverter
from webdnn.util import console

from net import ImageCaption

resnet_link = None


def get_resnet_io_variable(nn_input=None):
    global resnet_link
    if resnet_link is None:
        resnet_link = chainer.links.model.vision.resnet.ResNet50Layers()
    out_layer_name = "pool5"
    if nn_input is None:
        nn_input = chainer.Variable(
            np.zeros((1, 3, 224, 224), dtype=np.float32))

    nn_output = resnet_link(nn_input, layers=[out_layer_name])[out_layer_name]
    return nn_input, nn_output


def generate_graph_model1(caption_net):
    resnet_in, resnet_out = get_resnet_io_variable()
    image_vec_out = caption_net.image_vec(resnet_out)
    converter = ChainerConverter()
    graph = converter.convert([resnet_in], [image_vec_out])
    return graph


def _convert_lstm_to_webdnn_order(x):
    # NOTE:
    # In WebDNN, W_i, W_h, and b contains weights about input gate(v_i), forget gate(v_f) activated value(v_a), and output gate(v_o)
    # based on this order (v_i, v_f, v_a, v_o). However in chainer, they are packed in different order (v_a, v_i, v_f, and v_o).
    # Also, webdnn packs this weights as an tensor whose shape is (C1 or C2, 4, C2), but chainer packs as (C1 or C2, C2, 4)
    # Based on webdnn/test/operators_test/lstm_test.py
    # inverse conversion of x.reshape(x.shape[0], 4, x.shape[1] //
    # 4).swapaxes(1, 2)[:, :, [2, 0, 1, 3]].reshape(x.shape)
    return x.reshape(x.shape[0], x.shape[1] // 4, 4).swapaxes(1, 2)[:, [1, 2, 0, 3], :].reshape(x.shape)


def generate_graph_model2(caption_net, hidden_num):
    # inputs
    var_input_img = Variable([1, 1, hidden_num], OrderNTC)
    var_input_word = Variable([1, 1], OrderNT)
    var_switch_img = Variable([1, 1, hidden_num], OrderNTC)
    var_switch_word = Variable([1, 1, hidden_num], OrderNTC)
    var_last_h = Variable([1, hidden_num], OrderNC)
    var_last_c = Variable([1, hidden_num], OrderNC)

    # prepare for lstm
    var_emb_word, = Embedding(None)(var_input_word, ConstantVariable(
        caption_net.word_vec.W.data, OrderCN))  # OrderNTC
    var_lstm_input = (var_emb_word * var_switch_word) + \
        (var_input_img * var_switch_img)

    # lstm
    lstm_opr = LSTM(None, use_bias=True, return_sequences=False,
                    activation="tanh", recurrent_activation="sigmoid",
                    use_initial_h=True, use_initial_c=True)
    w_input = _convert_lstm_to_webdnn_order(caption_net.lstm.upward.W.data.T)
    w_hidden = _convert_lstm_to_webdnn_order(caption_net.lstm.lateral.W.data.T)
    b = _convert_lstm_to_webdnn_order(
        caption_net.lstm.upward.b.data[None, :])[0]
    var_lstm_h, var_lstm_c = lstm_opr(x=var_lstm_input,
                                      w_input=ConstantVariable(
                                          w_input, OrderCN),
                                      w_hidden=ConstantVariable(
                                          w_hidden, OrderCN),
                                      b=ConstantVariable(b, OrderC),
                                      initial_h=var_last_h, initial_c=var_last_c)

    # word probability
    var_word_score, = Linear(None)(var_lstm_h, ConstantVariable(
        caption_net.out_word.W.data.T, OrderCN))
    var_word_score_biased, = AxiswiseBias(None, axis=Axis.C)(var_word_score,
                                                             ConstantVariable(caption_net.out_word.b.data, OrderC))
    var_word_prob, = Softmax(None, axis=Axis.C)(var_word_score_biased)

    return Graph([var_input_img, var_input_word, var_switch_img, var_switch_word, var_last_h, var_last_c],
                 [var_word_prob, var_lstm_h, var_lstm_c])


def generate_example_io(caption_net, word_ids, image_path):
    import PIL.Image
    input_img_feat = resnet_link.extract([PIL.Image.open(image_path)], layers=["pool5"])[
        "pool5"]  # Chainer.Variable(1, 2048)
    caption_net.lstm.reset_state()
    input_img_embedded = caption_net.image_vec(input_img_feat)
    image_lstm_output = caption_net.lstm(input_img_embedded)
    bos_raw_vec = chainer.Variable(
        np.array([[word_ids["<S>"]]], dtype=np.int32))
    bos_word_vec = caption_net.word_vec(bos_raw_vec)
    bos_lstm_output = caption_net.lstm(bos_word_vec)
    bos_word_score = caption_net.out_word(bos_lstm_output)
    bos_word_prob = chainer.functions.softmax(bos_word_score)
    return {"input_img_embedded": input_img_embedded.data.flatten().tolist(),
            "image_lstm_output": image_lstm_output.data.flatten().tolist(),
            "bos_raw_vec": bos_raw_vec.data.flatten().tolist(),
            "bos_lstm_output": bos_lstm_output.data.flatten().tolist(),
            "bos_word_prob": bos_word_prob.data.flatten().tolist()}


def main():
    sys.setrecursionlimit(10000)  # workaround for deep copying large graph

    parser = argparse.ArgumentParser()
    parser.add_argument("--backend", default="webgpu,webassembly")
    parser.add_argument("--encoding", default="eightbit")
    parser.add_argument('--out', '-o', default='webdnn/image-caption-model',
                        help='Directory to output the graph descriptor')
    parser.add_argument('--sentence', '-s', required=True, type=str,
                        help='sentence dataset file path')
    parser.add_argument('--model', '-m', required=True, type=str,
                        help='input model file path')
    parser.add_argument("--example_image",
                        help="example image for comparing output")
    parser.add_argument("--visualize_ir", action="store_true")

    args = parser.parse_args()

    os.makedirs(args.out, exist_ok=True)
    out_dir_graph1 = os.path.join(args.out, "image-feature")
    out_dir_graph2 = os.path.join(args.out, "caption-generation")

    hidden_num = 512
    with open(args.sentence, 'rb') as f:
        sentence_dataset = pickle.load(f)
    word_ids = sentence_dataset['word_ids']
    word_num = len(word_ids)
    id_to_word = [""] * word_num
    for k, v in word_ids.items():
        id_to_word[v] = k

    with open(os.path.join(args.out, "word_data.json"), "w") as f:
        json.dump({"id_to_word": id_to_word,
                   "bos_id": word_ids["<S>"],
                   "eos_id": word_ids["</S>"],
                   "word_num": word_num,
                   "hidden_num": hidden_num}, f)

    caption_net = ImageCaption(
        word_num=word_num, feature_num=2048, hidden_num=hidden_num)
    chainer.serializers.load_hdf5(args.model, caption_net)
    graph1 = generate_graph_model1(caption_net)
    graph2 = generate_graph_model2(caption_net, hidden_num=hidden_num)

    if args.example_image:
        example_io = generate_example_io(
            caption_net, word_ids, args.example_image)
        with open(os.path.join(args.out, "example_io.json"), "w") as f:
            json.dump(example_io, f)

    if args.visualize_ir:
        ir_dot_path = os.path.join(args.out, "ir.dot")
        with open(ir_dot_path, "w") as f:
            f.write(dump_dot(graph2))
        console.stderr(
            f"IR graph can be visualized with graphviz command: 'dot {ir_dot_path} -T png -o output.png'")

    any_backend_failed = False
    last_backend_exception = None
    for backend in args.backend.split(","):
        try:
            graph_exec_data = generate_descriptor(
                backend, graph1, constant_encoder_name=args.encoding)
            graph_exec_data.save(out_dir_graph1)
            graph_exec_data = generate_descriptor(
                backend, graph2, constant_encoder_name=args.encoding)
            graph_exec_data.save(out_dir_graph2)
        except Exception as ex:
            any_backend_failed = True
            last_backend_exception = ex
            console.error(
                f"Failed generating descriptor for backend {backend}: {str(ex)}\n")

    if any_backend_failed:
        raise last_backend_exception


if __name__ == "__main__":
    with chainer.using_config('train', False):
        with chainer.using_config('enable_backprop', True):
            main()
