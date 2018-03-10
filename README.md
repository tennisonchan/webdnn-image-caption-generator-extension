# WebDNN Image Caption Generator

A chrome extension using [WebDNN](https://github.com/mil-tokyo/webdnn) to generate image caption when hovering on images.

[Download form Chrome Store](https://chrome.google.com/webstore/detail/acpidmnklkfcjgajfboinepbfojhegpk/)

This repos is to demonstrate how to use WebDNN on the client-side, chrome extension in this case. The [Chrome Extension generator](https://github.com/yeoman/generator-chrome-extension) is used to generate the extension boilerplate.

## Getting Started

For development, you need to load/reload extension after starting gulp watch for Live-reload to work.

```bash
# npm watch
gulp watch --sass
```

## The Steps

There are mainly 2 parts: Converting WebDNN and Implementing the models on client-side.

1.  Converting WebDNN using pre-train `caption_gen_resnet.model` model and `coco.pkl` dataset. Since Chrome doesn't support WebGPU yet, we use WebAssembly as backend. The models were generated and moved into the folder `app/`, but if you want to modify the models, you can run the following lind.

```bash
# npm run convert:webdnn
python py/convert_webdnn.py --backend webassembly --sentence datasets/coco.pkl --model models/caption_gen_resnet.mode && mv ./webdnn ./app
```

2.  Using WebDNN to load the image feature model and caption generation model in browser. [line](https://github.com/tennisonchan/webdnn-image-caption-generator-extension/blob/master/app/scripts.babel/background.js#L10)
3.  Generating image feature by passing the image array into the image feature model. [line](https://github.com/tennisonchan/webdnn-image-caption-generator-extension/blob/master/app/scripts.babel/ImageCaptionGenerator.js#L32)
4.  Generating caption by passing the image feature into the caption generation model. [line](https://github.com/tennisonchan/webdnn-image-caption-generator-extension/blob/master/app/scripts.babel/ImageCaptionGenerator.js#L41)

## Measurements

The following data is the average time taken of generating a sentence in 10 runs. The image feature extraction takes around 6 seconds, the longest among all.

| Measurements                        | Average Time (ms) |
| ----------------------------------- | ----------------- |
| Load Image Runner                   | 2608.9            |
| Load Caption Runner                 | 1143.44           |
| Extract image feature               | 5803.77           |
| Generate Caption from image feature | 511.77            |

![chart](https://user-images.githubusercontent.com/719938/37243260-870f46e0-24b1-11e8-93c6-59d9e3049297.png)

## TroubleShotings

### FileNotFoundError: [Errno 2] No such file or directory: 'python2': 'python2'

* Install Python 2 by `brew install python@2`
* Update `~/.bashrc` by adding this line `export PATH="/usr/local/opt/python@2/bin:$PATH"`
* Reload the Bash startup file `source ~/.bashrc`

### fatal error: 'Eigen/Dense' file not found

This fatal error occurs due to the `eigen3` cannot be included

* Install eigen by `brew install eigen`
* Add the following lines in the file `$(brew --prefix)/lib/python3.6/site-packages/webdnn/backend/webassembly/generator.py`

```python
  # After both line 54 and 83
  # args = ["em++"]
  args.append("-I")
  args.append("/usr/local/include/eigen3")
```

## Reference

* https://github.com/mil-tokyo/webdnn - WebDNN runs deep neural network (DNN) pre-trained model on web browser.
* https://milhidaka.github.io/chainer-image-caption/ - Generating image caption demo
* https://github.com/milhidaka/webdnn-exercise - Exercise of basic usage of WebDNN
