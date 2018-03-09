
#include <metal_stdlib>
using namespace metal;

#define OPTIMIZE 1

kernel void embedding_5681741bb5b48844184ce968ca45a9acbe6bfb0e8ea9da87a38098a2(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint global_index[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float *X = (static_buffer + meta_buffer[0]);
    device float       *Y = (static_buffer + meta_buffer[1]);
    const device float *W = (static_buffer + meta_buffer[2]);

    const int T = meta_buffer[3];
    const int N = meta_buffer[4];
    const int C = meta_buffer[5];

    for (int gid = global_index; gid < N * T; gid += num_threads) {
        const int t = gid % T;
        const int n = gid / T;

        const int word = (int)X[gid];
        for (int c = 0; c < C; c++) {
            Y[(n * T + t) * C + c] = W[word * C + c];
        }
    }
}


kernel void fusedelementwise_8e9d606b17a50c4bcd26495c38d60d95077f4a2c4c89461b008dfbff(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    const device float * v4 = (static_buffer + meta_buffer[3]);
    device float * v5 = (static_buffer + meta_buffer[4]);
    const int D0 = meta_buffer[5];
    int d0;
    for (d0 = gid; d0 < D0; d0 += num_threads) {
        const float v6 = v1[d0];
        const float v7 = v3[d0];
        float v8;
        {
            v8 = v6 * v7;
        }
        const float v9 = v2[d0];
        const float v10 = v4[d0];
        float v11;
        {
            v11 = v9 * v10;
        }
        float v12;
        {
            v12 = v11 + v8;
        }
        v5[d0] = v12;
    }
}


kernel void lstm_22bf557d912dc882a179f628ee2189854cff077c666d942d8299f4f2(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer[[buffer(2)]],
                          uint global_index[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
#define USE_INITIAL_C 1
#define USE_INITIAL_H 1
#define activation_function(x) (metal::precise::tanh(x))
#define recurrent_activation_function(x) (metal::precise::tanh(0.5f * (x)) * 0.5f + 0.5f)
#define RETURN_SEQUENCES 0

    const device float  *X         = (static_buffer + meta_buffer[0]);
          device float  *XH        = (static_buffer + meta_buffer[7]);
    const device float  *W_all     = (static_buffer + meta_buffer[8]);
          device float  *workspace = (static_buffer + meta_buffer[9]);
          device float  *Y         = (static_buffer + meta_buffer[1]);
          device float  *final_C   = (static_buffer + meta_buffer[10]);
    const device float  *b         = (static_buffer + meta_buffer[2]);

#if USE_INITIAL_C
    const device float  *initial_C = (static_buffer + meta_buffer[11]);
#endif
#if USE_INITIAL_H
    const device float  *initial_H = (static_buffer + meta_buffer[12]);
#endif

    const int N  = meta_buffer[3];
    const int T  = meta_buffer[4];
    const int C1 = meta_buffer[5];
    const int C2 = meta_buffer[6];

    device float *XH_X = XH;
    device float *XH_H = XH + C1 * N;

    //reset output and cell state
    for (int gid = global_index; gid < N * C2; gid += num_threads)
    {
#if USE_INITIAL_H
        XH_H[gid] = initial_H[gid];
#else
        XH_H[gid] = 0;
#endif

#if USE_INITIAL_C
        final_C[gid] = initial_C[gid];
#else
        final_C[gid] = 0;
#endif
    }

    for (int t = 0; t < T; t++)
    {
        for (int gid = global_index; gid < C1 * N; gid += num_threads)
        {
            const int n = gid % N;
            const int c1 = gid / N;
            XH_X[gid] = X[(n * T + t) * C1 + c1];
        }

        threadgroup_barrier(mem_flags::mem_device);

        //FIXME: replace here to more efficient sgemv implementation.
        // `4` means the number of hidden matrices (input, forget, activation, output).
        for (int gid = global_index; gid < C2 * 4 * N; gid += num_threads)
        {
            const int n = gid % N;
            const int c2_4 = gid / N;

            float v = b[c2_4];

            for (int c1c2 = 0; c1c2 < C1 + C2; c1c2++)
            {
                v += XH[c1c2 * N + n] * W_all[c1c2 * C2 * 4 + c2_4];
            }

            workspace[gid] = v;
        }

        threadgroup_barrier(mem_flags::mem_device);

        for (int gid = global_index; gid < C2 * N; gid += num_threads)
        {
            const int n = gid % N;
            const int c2 = gid / N;

            float i = workspace[gid + N * C2 * 0];
            float f = workspace[gid + N * C2 * 1];
            float a = workspace[gid + N * C2 * 2];
            float o = workspace[gid + N * C2 * 3];
            float c = final_C[n * C2 + c2];

            i = recurrent_activation_function(i);
            f = recurrent_activation_function(f);
            a = activation_function(a);
            o = recurrent_activation_function(o);

            c = a * i + c * f;

            final_C[n * C2 + c2] = c;
            const float h = activation_function(c) * o;
            XH_H[gid] = h;

#if RETURN_SEQUENCES
            Y[(n * T + t) * C2 + c2] = h;
#endif
        }
    }

#if !RETURN_SEQUENCES
    //copy final output to output variable
    for (int gid = global_index; gid < C2 * N; gid += num_threads)
    {
        const int n = gid % N;
        const int c2 = gid / N;
        Y[n * C2 + c2] = XH_H[gid];
    }
#endif

#undef USE_INITIAL_C
#undef USE_INITIAL_H
#undef activation_function
#undef recurrent_activation_function
#undef RETURN_SEQUENCES
}
    

kernel void transpose_004b4f39e9e976c3a0c2492294b329e4263fa637435784552851f71d(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    device float * v2 = (static_buffer + meta_buffer[1]);
    const int D0 = meta_buffer[2];
    int d0;
    for (d0 = gid; d0 < D0; d0 += num_threads) {
        const float v3 = v1[d0];
        float v4;
        {
            v4 = v3;
        }
        v2[d0] = v4;
    }
}


kernel void tensordot_92d010c077e5e47e7d25245f52cbec2d36848fa15bbaf804a3bb662a(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index[[thread_index_in_threadgroup]],
                          uint2 group_position[[threadgroup_position_in_grid]])
{
#define M_DIVIDABLE_BY_64 0
#define N_DIVIDABLE_BY_64 0
#define K_DIVIDABLE_BY_8 1

#define A_STRIDE_K M
#define A_STRIDE_M 1

#define B_STRIDE_K N
#define B_STRIDE_N 1

#if K_DIVIDABLE_BY_8 && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64 && OPTIMIZE
    const device float4 *load_target4 = (index & 32)
        ? (const device float4 *)((static_buffer + meta_buffer[1]))
        : (const device float4 *)((static_buffer + meta_buffer[0]));
#else
    const device float *load_target = (index & 32)
        ? ((static_buffer + meta_buffer[1]))
        : ((static_buffer + meta_buffer[0]));
#endif

    const int M = meta_buffer[3];
    const int N = meta_buffer[4];

    const int K = meta_buffer[5];

    threadgroup float4 shared4[32 * 8 * 2];

    const int stride_k = (index & 32) ? B_STRIDE_K : A_STRIDE_K;
    const int stride_mn = (index & 32) ? B_STRIDE_N : A_STRIDE_M;

    const int m_offset = index & 7;
    const int n_offset = index >> 3;

    const int mn_load_offset = ((index & 32) ? group_position.y : group_position.x) * 64 + (index & 15) * 4;
    const int k_load_offset = ((index & 16) ? 1 : 0);

    int track0 = mn_load_offset * stride_mn + (k_load_offset + 0) * stride_k;
    int track2 = track0 + 2 * stride_k;
    int track4 = track0 + 4 * stride_k;
    int track6 = track0 + 6 * stride_k;

#if !OPTIMIZE || !M_DIVIDABLE_BY_64 || !N_DIVIDABLE_BY_64
    const int max_MN = (index & 32) ? N : M;
#endif

    int shared_offset4 = ((index & 32) ? 16 : 0) + k_load_offset * 32 + (index & 15);
    int read_A_offset4 = m_offset * 2;
    int read_B_offset4 = n_offset * 2 + 16;

    float4 result[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int k = 0;

    while (k < K)
    {
        {
#if OPTIMIZE && K_DIVIDABLE_BY_8
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
        #if OPTIMIZE
            shared4[shared_offset4 + 32 * 0] = load_target4[track0 >> 2];
            shared4[shared_offset4 + 32 * 2] = load_target4[track2 >> 2];
            shared4[shared_offset4 + 32 * 4] = load_target4[track4 >> 2];
            shared4[shared_offset4 + 32 * 6] = load_target4[track6 >> 2];
        #else
            shared4[shared_offset4 + 32 * 0] = float4(
                load_target[track0 + stride_mn * 0],
                load_target[track0 + stride_mn * 1],
                load_target[track0 + stride_mn * 2],
                load_target[track0 + stride_mn * 3]
            );
            shared4[shared_offset4 + 32 * 2] = float4(
                load_target[track2 + stride_mn * 0],
                load_target[track2 + stride_mn * 1],
                load_target[track2 + stride_mn * 2],
                load_target[track2 + stride_mn * 3]
            );
            shared4[shared_offset4 + 32 * 4] = float4(
                load_target[track4 + stride_mn * 0],
                load_target[track4 + stride_mn * 1],
                load_target[track4 + stride_mn * 2],
                load_target[track4 + stride_mn * 3]
            );
            shared4[shared_offset4 + 32 * 6] = float4(
                load_target[track6 + stride_mn * 0],
                load_target[track6 + stride_mn * 1],
                load_target[track6 + stride_mn * 2],
                load_target[track6 + stride_mn * 3]
            );
        #endif
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            );
            shared4[shared_offset4 + 32 * 2] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            );
            shared4[shared_offset4 + 32 * 4] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            );
            shared4[shared_offset4 + 32 * 6] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            );
    #endif

            k += 8;
#else
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 3]
            );
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 3]
            );
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 3]
            );
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 3]
            );
            k += 2;
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            );
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            );
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            );
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            );
            k += 2;
    #endif
#endif
        }

        threadgroup_barrier(mem_flags::mem_threadgroup);

        {
            for (int k_sub = 0; k_sub < 8; k_sub++)
            {
                float4 a00 = shared4[32 * k_sub + read_A_offset4 + 0];
                float4 a01 = shared4[32 * k_sub + read_A_offset4 + 1];
                float4 b00 = shared4[32 * k_sub + read_B_offset4 + 0];
                float4 b01 = shared4[32 * k_sub + read_B_offset4 + 1];

                result[4][0]  += b00[0] * a00[2];
                result[4][1]  += b00[1] * a00[2];
                result[0][1]  += b00[1] * a00[0];
                result[0][0]  += b00[0] * a00[0];
                result[6][0]  += b00[0] * a00[3];
                result[6][1]  += b00[1] * a00[3];
                result[2][1]  += b00[1] * a00[1];
                result[2][0]  += b00[0] * a00[1];
                result[12][0] += b00[0] * a01[2];
                result[12][1] += b00[1] * a01[2];
                result[8][1]  += b00[1] * a01[0];
                result[8][0]  += b00[0] * a01[0];
                result[14][0] += b00[0] * a01[3];
                result[14][1] += b00[1] * a01[3];
                result[10][1] += b00[1] * a01[1];
                result[10][0] += b00[0] * a01[1];

                result[14][2] += b00[2] * a01[3];
                result[14][3] += b00[3] * a01[3];
                result[10][3] += b00[3] * a01[1];
                result[10][2] += b00[2] * a01[1];
                result[12][2] += b00[2] * a01[2];
                result[12][3] += b00[3] * a01[2];
                result[8][3]  += b00[3] * a01[0];
                result[8][2]  += b00[2] * a01[0];
                result[6][2]  += b00[2] * a00[3];
                result[6][3]  += b00[3] * a00[3];
                result[2][3]  += b00[3] * a00[1];
                result[2][2]  += b00[2] * a00[1];
                result[4][2]  += b00[2] * a00[2];
                result[4][3]  += b00[3] * a00[2];
                result[0][3]  += b00[3] * a00[0];
                result[0][2]  += b00[2] * a00[0];

                result[5][0]  += b01[0] * a00[2];
                result[5][1]  += b01[1] * a00[2];
                result[1][1]  += b01[1] * a00[0];
                result[1][0]  += b01[0] * a00[0];
                result[7][0]  += b01[0] * a00[3];
                result[7][1]  += b01[1] * a00[3];
                result[3][1]  += b01[1] * a00[1];
                result[3][0]  += b01[0] * a00[1];
                result[13][0] += b01[0] * a01[2];
                result[13][1] += b01[1] * a01[2];
                result[9][1]  += b01[1] * a01[0];
                result[9][0]  += b01[0] * a01[0];
                result[15][0] += b01[0] * a01[3];
                result[15][1] += b01[1] * a01[3];
                result[11][1] += b01[1] * a01[1];
                result[11][0] += b01[0] * a01[1];

                result[15][2] += b01[2] * a01[3];
                result[15][3] += b01[3] * a01[3];
                result[11][3] += b01[3] * a01[1];
                result[11][2] += b01[2] * a01[1];
                result[13][2] += b01[2] * a01[2];
                result[13][3] += b01[3] * a01[2];
                result[9][3]  += b01[3] * a01[0];
                result[9][2]  += b01[2] * a01[0];
                result[7][2]  += b01[2] * a00[3];
                result[7][3]  += b01[3] * a00[3];
                result[3][3]  += b01[3] * a00[1];
                result[3][2]  += b01[2] * a00[1];
                result[5][2]  += b01[2] * a00[2];
                result[5][3]  += b01[3] * a00[2];
                result[1][3]  += b01[3] * a00[0];
                result[1][2]  += b01[2] * a00[0];
            }
        }

        shared_offset4 ^= 32 * 8;
        read_A_offset4 ^= 32 * 8;
        read_B_offset4 ^= 32 * 8;
        track0 += stride_k * 8;
        track2 += stride_k * 8;
        track4 += stride_k * 8;
        track6 += stride_k * 8;
    }

    {

#if OPTIMIZE && N_DIVIDABLE_BY_64
        device float4 *C4 = (device float4 *)((static_buffer + meta_buffer[2]));
        const int N4 = N >> 2;
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {

    #if !M_DIVIDABLE_BY_64
            if (m >= M) continue;
    #endif

            const int n = group_position.y * 16 + n_offset * 2;
            float4 result0 = result[m_sub * 2 + 0];
            float4 result1 = result[m_sub * 2 + 1];

            C4[m * N4 + n + 0] = result0;
            C4[m * N4 + n + 1] = result1;

            m++;
        }
#else
        device float *C = (static_buffer + meta_buffer[2]);
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {
            int n = group_position.y * 64 + n_offset * 8;

            for (int n_sub1 = 0; n_sub1 < 2; n_sub1++)
            {
                for (int n_sub2 = 0; n_sub2 < 4; n_sub2++)
                {

    #if OPTIMIZE && M_DIVIDABLE_BY_64
                    (         n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #else
                    (m < M && n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #endif
                    n++;
                }
            }

            m++;
        }
#endif

    }

#undef M_DIVIDABLE_BY_64
#undef N_DIVIDABLE_BY_64
#undef K_DIVIDABLE_BY_8
#undef A_STRIDE_K
#undef B_STRIDE_K
#undef A_STRIDE_M
#undef B_STRIDE_N
}


kernel void elementwiseadd_59df3b0d6feefd576062ac58c68e6dade28056ea47dd0a57294bdf90(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    device float * v3 = (static_buffer + meta_buffer[2]);
    const int D0 = meta_buffer[3];
    int d0;
    for (d0 = gid; d0 < D0; d0 += num_threads) {
        const float v4 = v1[d0];
        const float v5 = v2[d0];
        float v6;
        {
            v6 = v5 + v4;
        }
        v3[d0] = v6;
    }
}


kernel void softmax_c5c1093e2f2f79baae8036b89eb70752cc1a574cf4c28310442568eb(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float *X = (static_buffer + meta_buffer[0]);
    device float *Y = (static_buffer + meta_buffer[1]);
    const int D1 = meta_buffer[2];
    const int D2 = meta_buffer[3];
    const int D3 = meta_buffer[4];

    for (int gid = index; gid < D1 * D3; gid += num_threads) {
        const int d3 = gid % D3;
        const int d1 = gid / D3;

        float set_max = 0.0f;
        for (int d2 = 0; d2 < D2; d2++) {
            float val = X[(d1 * D2 + d2) * D3 + d3];
            if (val > set_max) {
                set_max = val;
            }
        }

        float sum_exp = 0.0f;
        for (int d2 = 0; d2 < D2; d2++) {
            float val = X[(d1 * D2 + d2) * D3 + d3];
            float exp_x = exp(val - set_max);
            sum_exp += exp_x;
            Y[(d1 * D2 + d2) * D3 + d3] = exp_x;
        }

        for (int d2 = 0; d2 < D2; d2++) {
            Y[(d1 * D2 + d2) * D3 + d3] /= sum_exp;
        }
    }
}
