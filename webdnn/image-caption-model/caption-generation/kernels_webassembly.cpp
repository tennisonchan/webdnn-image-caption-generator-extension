
#include <stdlib.h>
#include <math.h>

float static_buffer[11124915];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {11124914,11122866,0,8793,1,1,512};
int meta_buf_1[] = {11120818,11121330,11122866,11124402,11120818,512};
int meta_buf_2[] = {11120818,11122354,11123890,5552640,4504064,512,1,1,512,4502016,11123378,11121842};
int meta_buf_3[] = {11122354,6601216,11112025,1,8793,512};
int meta_buf_4[] = {11103232,11112025,11112025,8793};
int meta_buf_5[] = {11112025,11112025,1,8793};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5};

extern "C" void init() {
    //static_buffer = (float*)malloc(11124915 * sizeof(float));
}

extern "C" float* get_static_buffer(void) {
    return static_buffer;
}

extern "C" float* allocate_dynamic_buffer(int count) {
    if (dynamic_buffer) {
        free(dynamic_buffer);
        dynamic_buffer = nullptr;
    }
    dynamic_buffer = (float*)malloc(count * sizeof(float));
    return dynamic_buffer;
}

extern "C" float* get_dynamic_buffer(void) {
    return dynamic_buffer;
}
extern "C" void set_placeholder_value(int kernel_order, int offset, int value) {
    meta_buffers[kernel_order][offset] = value;
}

void embedding_bff664a25d5cd866fdc2b62a606caa6eb07d8ca9703906d8f951028d(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const float *W = (static_buffer + meta_buffer[2]);
    const int vocabulary = meta_buffer[3];
    const int sequence_len = meta_buffer[4];
    const int batch_size = meta_buffer[5];
    const int dim = meta_buffer[6];

    for (int gid = 0; gid < batch_size * sequence_len; gid += 1) {
        int t = gid % sequence_len;
        int batch = gid / sequence_len;

        int word = (int)X[gid];
        for (int d = 0; d < dim; d++) {
            Y[gid * dim + d] = W[word * dim + d];
        }
    }
}


void fusedelementwise_81998e28049ebb818a4b96f44804a844fd65b00be4b75c5f78b3a80a(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int D0 = meta_buffer[5];
    int d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        const float v6 = v2[d0];
        const float v7 = v4[d0];
        float v8;
        {
            v8 = v7 * v6;
        }
        const float v9 = v1[d0];
        const float v10 = v3[d0];
        float v11;
        {
            v11 = v10 * v9;
        }
        float v12;
        {
            v12 = v11 + v8;
        }
        v5[d0] = v12;
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void lstm_08c1ac19a876ea425178f49b82045c77167557e8ffbbd9fa0687f591(const int * meta_buffer)
{

    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    float *mem_c = (static_buffer + meta_buffer[2]);
    float *W_input = (static_buffer + meta_buffer[3]);
    float *W_hidden = (static_buffer + meta_buffer[4]);
    const int input_dim = meta_buffer[5];
    const int sequence_len = meta_buffer[6];
    const int batch_size = meta_buffer[7];
    const int hidden_dim = meta_buffer[8];
    const int hidden_dim4 = hidden_dim * 4;
    const int ofs_i = 0;
    const int ofs_f = hidden_dim * 1;
    const int ofs_c = hidden_dim * 2;
    const int ofs_o = hidden_dim * 3;
    float *b = (static_buffer + meta_buffer[9]);
Eigen::Map<Eigen::RowVectorXf > vec_b(b, hidden_dim4);

    auto activation = [](float x) {
        
        return tanhf(x);
        
    };

    auto recurrent_activation = [](float x) {
        
        x = 1.0F / (1.0 + expf(-x));
        return x;
        
    };

    
        const float *initial_c = (static_buffer + meta_buffer[10]);
        for (int i = 0; i < hidden_dim * batch_size; i++) {
            mem_c[i] = initial_c[i];
        }
        
    float *mem_h = new float[hidden_dim * batch_size]();
    
        const float *initial_h = (static_buffer + meta_buffer[11]);
        for (int i = 0; i < hidden_dim * batch_size; i++) {
            mem_h[i] = initial_h[i];
        }
        
    float *mem_v = new float[hidden_dim4 * batch_size](); // i, f, c, o
    float *mem_x_t = new float[input_dim * batch_size]();
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > mat_v(mem_v, batch_size, hidden_dim4);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > mat_h(mem_h, batch_size, hidden_dim);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > mat_x_t(mem_x_t, batch_size, input_dim);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > mat_w_input(W_input, input_dim, hidden_dim4);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > mat_w_hidden(W_hidden, hidden_dim, hidden_dim4);

    for (int t = 0; t < sequence_len; t++) {
        // copy x of current time
        for (int n = 0; n < batch_size; n++) {
            for (int dim = 0; dim < input_dim; dim++) {
                mem_x_t[dim + n * input_dim] = X[(n * sequence_len + t) * input_dim + dim];
            }
        }

        mat_v.noalias() = mat_x_t * mat_w_input + mat_h * mat_w_hidden;
        mat_v.rowwise() += vec_b;

        for (int n = 0; n < batch_size; n++) {
            // update c, h
            for (int dim = 0; dim < hidden_dim; dim++) {
                float val_i = mem_v[dim + ofs_i + n * hidden_dim4];
                float val_f = mem_v[dim + ofs_f + n * hidden_dim4];
                float val_c = mem_v[dim + ofs_c + n * hidden_dim4];
                float val_o = mem_v[dim + ofs_o + n * hidden_dim4];
                val_i = recurrent_activation(val_i);
                val_f = recurrent_activation(val_f);
                float val_last_c = mem_c[dim + n * hidden_dim];
                val_c = activation(val_c) * val_i + val_last_c * val_f;
                mem_c[dim + n * hidden_dim] = val_c;
                mem_h[dim + n * hidden_dim] = activation(val_c) * recurrent_activation(val_o);
            }
        }

        //write output on sequence
#ifdef SEQUENCE_OUTPUT
        for (int n = 0; n < batch_size; n++) {
            for (int dim = 0; dim < hidden_dim; dim++) {
                Y[(n * sequence_len + t) * hidden_dim + dim] = mem_h[n * hidden_dim + dim];
            }
        }
#endif
    }

    // write output
#ifndef SEQUENCE_OUTPUT
    for (int i = 0; i < batch_size * hidden_dim; i++) {
        Y[i] = mem_h[i];
    }
#endif

    delete[] mem_h;
    delete[] mem_v;
    delete[] mem_x_t;
#undef SEQUENCE_OUTPUT
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(const int * meta_buffer)
{
    float *A = (static_buffer + meta_buffer[0]);
    float *B = (static_buffer + meta_buffer[1]);
    float *C = (static_buffer + meta_buffer[2]);

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, meta_buffer[3], meta_buffer[5]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> > b_mat(B, meta_buffer[5], meta_buffer[4]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, meta_buffer[3], meta_buffer[4]);

    c_mat.noalias() = a_mat * b_mat;
}


void elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int D0 = meta_buffer[3];
    int d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        const float v4 = v1[d0];
        const float v5 = v2[d0];
        float v6;
        {
            v6 = v5 + v4;
        }
        v3[d0] = v6;
    }
}


void softmax_be4c2fae32b9326b0ca891226ac9234de828aecba508a30394d8a57e(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int C = meta_buffer[3];

    for (int n = 0; n < N; n++) {
        float set_max = X[n * C];
        for (int c = 0; c < C; c++) {
            float val = X[n * C + c];
            if (val > set_max) {
                set_max = val;
            }
        }

        float sum_exp = 0.0F;
        for (int c = 0; c < C; c++) {
            float val = X[n * C + c];
            float exp_x = expf(val - set_max);
            sum_exp += exp_x;
            Y[n * C + c] = exp_x;
        }

        for (int c = 0; c < C; c++) {
            Y[n * C + c] /= sum_exp;
        }
    }
}

extern "C" void run() {
embedding_bff664a25d5cd866fdc2b62a606caa6eb07d8ca9703906d8f951028d(meta_buf_0);
fusedelementwise_81998e28049ebb818a4b96f44804a844fd65b00be4b75c5f78b3a80a(meta_buf_1);
lstm_08c1ac19a876ea425178f49b82045c77167557e8ffbbd9fa0687f591(meta_buf_2);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_3);
elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(meta_buf_4);
softmax_be4c2fae32b9326b0ca891226ac9234de828aecba508a30394d8a57e(meta_buf_5);

}

