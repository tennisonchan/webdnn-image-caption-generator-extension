
#include <stdlib.h>
#include <math.h>

float static_buffer[62777984];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {59411584,59261056,50176,3,3,50176};
int meta_buf_1[] = {59261056,24526720,1,3,224,224,112,112,7,7,1,1,2,2,3,3};
int meta_buf_2[] = {24526720,0,36205184,12544,64,147};
int meta_buf_3[] = {9408,36205184,36205184,64,64,64,12544};
int meta_buf_4[] = {36205184,56852608,1,112,112,64,56,56,3,3,2,2,0,0};
int meta_buf_5[] = {56852608,57856128,64,3136,3136,64};
int meta_buf_6[] = {57856128,58658944,3136,64,64,3136};
int meta_buf_7[] = {58658944,9472,35402368,3136,256,64};
int meta_buf_8[] = {57856128,59060352,3136,64,64,3136};
int meta_buf_9[] = {59060352,25856,58859648,3136,64,64};
int meta_buf_10[] = {29952,58859648,58458240,64,64,64,3136};
int meta_buf_11[] = {58458240,26370688,1,64,56,56,56,56,3,3,1,1,1,1,1,1};
int meta_buf_12[] = {26370688,30016,57655424,3136,64,576};
int meta_buf_13[] = {66880,57655424,57655424,64,64,64,3136};
int meta_buf_14[] = {57655424,66944,38613632,3136,256,64};
int meta_buf_15[] = {83328,35402368,38613632,40219264,256,256,3136,256,3136};
int meta_buf_16[] = {40219264,41022080,3136,256,256,3136};
int meta_buf_17[] = {41022080,83584,56451200,3136,64,256};
int meta_buf_18[] = {99968,56451200,56451200,64,64,64,3136};
int meta_buf_19[] = {56451200,28177024,1,64,56,56,56,56,3,3,1,1,1,1,1,1};
int meta_buf_20[] = {28177024,100032,58257536,3136,64,576};
int meta_buf_21[] = {136896,58257536,58257536,64,64,64,3136};
int meta_buf_22[] = {58257536,136960,37810816,3136,256,64};
int meta_buf_23[] = {153344,37810816,40219264,43430528,256,3136,3136,256,3136};
int meta_buf_24[] = {43430528,39416448,3136,256,256,3136};
int meta_buf_25[] = {39416448,153600,57053312,3136,64,256};
int meta_buf_26[] = {169984,57053312,56651904,64,64,64,3136};
int meta_buf_27[] = {56651904,29983360,1,64,56,56,56,56,3,3,1,1,1,1,1,1};
int meta_buf_28[] = {29983360,170048,57454720,3136,64,576};
int meta_buf_29[] = {206912,57454720,57454720,64,64,64,3136};
int meta_buf_30[] = {57454720,206976,42627712,3136,256,64};
int meta_buf_31[] = {223360,43430528,42627712,43430528,3136,256,3136,256,3136};
int meta_buf_32[] = {43430528,41824896,3136,256,256,3136};
int meta_buf_33[] = {41824896,58056832,1,256,56,56,28,28,1,1,1,1,2,2,0,0};
int meta_buf_34[] = {58056832,223616,50555520,784,512,256};
int meta_buf_35[] = {43430528,37008000,3136,256,256,3136};
int meta_buf_36[] = {37008000,57254016,1,256,56,56,28,28,1,1,1,1,2,2,0,0};
int meta_buf_37[] = {57254016,354688,61569152,784,128,256};
int meta_buf_38[] = {387456,61569152,61569152,128,128,128,784};
int meta_buf_39[] = {61569152,34499200,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_40[] = {34499200,387584,61368448,784,128,1152};
int meta_buf_41[] = {535040,61368448,61268096,128,128,128,784};
int meta_buf_42[] = {61268096,535168,50956928,784,512,128};
int meta_buf_43[] = {600704,50555520,50956928,51358336,512,512,784,512,784};
int meta_buf_44[] = {51358336,51759744,784,512,512,784};
int meta_buf_45[] = {51759744,601216,61468800,784,128,512};
int meta_buf_46[] = {666752,61468800,61468800,128,128,128,784};
int meta_buf_47[] = {61468800,33596032,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_48[] = {33596032,666880,61167744,784,128,1152};
int meta_buf_49[] = {814336,61167744,59562112,128,128,128,784};
int meta_buf_50[] = {59562112,814464,48548480,784,512,128};
int meta_buf_51[] = {880000,51358336,48548480,46942848,784,512,784,512,784};
int meta_buf_52[] = {46942848,50154112,784,512,512,784};
int meta_buf_53[] = {50154112,880512,60967040,784,128,512};
int meta_buf_54[] = {946048,60967040,60967040,128,128,128,784};
int meta_buf_55[] = {60967040,31789696,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_56[] = {31789696,946176,60766336,784,128,1152};
int meta_buf_57[] = {1093632,60766336,60766336,128,128,128,784};
int meta_buf_58[] = {60766336,1093760,47344256,784,512,128};
int meta_buf_59[] = {1159296,46942848,47344256,46942848,784,512,784,512,784};
int meta_buf_60[] = {46942848,47745664,784,512,512,784};
int meta_buf_61[] = {47745664,1159808,60364928,784,128,512};
int meta_buf_62[] = {1225344,60364928,60364928,128,128,128,784};
int meta_buf_63[] = {60364928,32692864,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_64[] = {32692864,1225472,61067392,784,128,1152};
int meta_buf_65[] = {1372928,61067392,61067392,128,128,128,784};
int meta_buf_66[] = {61067392,1373056,49752704,784,512,128};
int meta_buf_67[] = {1438592,46942848,49752704,48147072,784,512,784,512,784};
int meta_buf_68[] = {48147072,48949888,784,512,512,784};
int meta_buf_69[] = {48949888,60565632,1,512,28,28,14,14,1,1,1,1,2,2,0,0};
int meta_buf_70[] = {60565632,1439104,54845568,196,1024,512};
int meta_buf_71[] = {48147072,49351296,784,512,512,784};
int meta_buf_72[] = {49351296,60465280,1,512,28,28,14,14,1,1,1,1,2,2,0,0};
int meta_buf_73[] = {60465280,1963392,61769856,196,256,512};
int meta_buf_74[] = {2094464,61769856,61769856,256,256,256,196};
int meta_buf_75[] = {61769856,44684928,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_76[] = {44684928,2094720,61820032,196,256,2304};
int meta_buf_77[] = {2684544,61820032,61820032,256,256,256,196};
int meta_buf_78[] = {61820032,2684800,54644864,196,1024,256};
int meta_buf_79[] = {2946944,54845568,54644864,53641344,1024,1024,196,1024,196};
int meta_buf_80[] = {53641344,53239936,196,1024,1024,196};
int meta_buf_81[] = {53239936,2947968,62070912,196,256,1024};
int meta_buf_82[] = {3210112,62070912,62070912,256,256,256,196};
int meta_buf_83[] = {62070912,44233344,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_84[] = {44233344,3210368,62221440,196,256,2304};
int meta_buf_85[] = {3800192,62221440,62020736,256,256,256,196};
int meta_buf_86[] = {62020736,3800448,55246976,196,1024,256};
int meta_buf_87[] = {4062592,53641344,55246976,53641344,196,1024,196,1024,196};
int meta_buf_88[] = {53641344,53039232,196,1024,1024,196};
int meta_buf_89[] = {53039232,4063616,61719680,196,256,1024};
int meta_buf_90[] = {4325760,61719680,62121088,256,256,256,196};
int meta_buf_91[] = {62121088,46039680,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_92[] = {46039680,4326016,62171264,196,256,2304};
int meta_buf_93[] = {4915840,62171264,62171264,256,256,256,196};
int meta_buf_94[] = {62171264,4916096,56250496,196,1024,256};
int meta_buf_95[] = {5178240,56250496,53641344,54243456,1024,196,196,1024,196};
int meta_buf_96[] = {54243456,53842048,196,1024,1024,196};
int meta_buf_97[] = {53842048,5179264,61669504,196,256,1024};
int meta_buf_98[] = {5441408,61669504,61669504,256,256,256,196};
int meta_buf_99[] = {61669504,45588096,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_100[] = {45588096,5441664,62321792,196,256,2304};
int meta_buf_101[] = {6031488,62321792,62321792,256,256,256,196};
int meta_buf_102[] = {62321792,6031744,55849088,196,1024,256};
int meta_buf_103[] = {6293888,54243456,55849088,53440640,196,1024,196,1024,196};
int meta_buf_104[] = {53440640,54042752,196,1024,1024,196};
int meta_buf_105[] = {54042752,6294912,62371968,196,256,1024};
int meta_buf_106[] = {6557056,62371968,62371968,256,256,256,196};
int meta_buf_107[] = {62371968,45136512,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_108[] = {45136512,6557312,62422144,196,256,2304};
int meta_buf_109[] = {7147136,62422144,62271616,256,256,256,196};
int meta_buf_110[] = {62271616,7147392,52838528,196,1024,256};
int meta_buf_111[] = {7409536,53440640,52838528,56049792,196,1024,196,1024,196};
int meta_buf_112[] = {56049792,55447680,196,1024,1024,196};
int meta_buf_113[] = {55447680,7410560,62472320,196,256,1024};
int meta_buf_114[] = {7672704,62472320,62472320,256,256,256,196};
int meta_buf_115[] = {62472320,46491264,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_116[] = {46491264,7672960,61920384,196,256,2304};
int meta_buf_117[] = {8262784,61920384,61920384,256,256,256,196};
int meta_buf_118[] = {61920384,8263040,54444160,196,1024,256};
int meta_buf_119[] = {8525184,56049792,54444160,56049792,196,1024,196,1024,196};
int meta_buf_120[] = {56049792,55046272,196,1024,1024,196};
int meta_buf_121[] = {55046272,61970560,1,1024,14,14,7,7,1,1,1,1,2,2,0,0};
int meta_buf_122[] = {61970560,8526208,60264576,49,2048,1024};
int meta_buf_123[] = {56049792,55648384,196,1024,1024,196};
int meta_buf_124[] = {55648384,61870208,1,1024,14,14,7,7,1,1,1,1,2,2,0,0};
int meta_buf_125[] = {61870208,10623360,62547584,49,512,1024};
int meta_buf_126[] = {11147648,62547584,62673024,512,512,512,49};
int meta_buf_127[] = {62673024,52386944,1,512,7,7,7,7,3,3,1,1,1,1,1,1};
int meta_buf_128[] = {52386944,11148160,62748288,49,512,4608};
int meta_buf_129[] = {13507456,62748288,62748288,512,512,512,49};
int meta_buf_130[] = {62748288,13507968,60866688,49,2048,512};
int meta_buf_131[] = {14556544,60866688,60264576,59762816,2048,2048,49,2048,49};
int meta_buf_132[] = {59762816,59863168,49,2048,2048,49};
int meta_buf_133[] = {59863168,14558592,62572672,49,512,2048};
int meta_buf_134[] = {15607168,62572672,62572672,512,512,512,49};
int meta_buf_135[] = {62572672,52612736,1,512,7,7,7,7,3,3,1,1,1,1,1,1};
int meta_buf_136[] = {52612736,15607680,62723200,49,512,4608};
int meta_buf_137[] = {17966976,62723200,62698112,512,512,512,49};
int meta_buf_138[] = {62698112,17967488,59963520,49,2048,512};
int meta_buf_139[] = {19016064,59762816,59963520,60164224,49,2048,49,2048,49};
int meta_buf_140[] = {60164224,60665984,49,2048,2048,49};
int meta_buf_141[] = {60665984,19018112,62597760,49,512,2048};
int meta_buf_142[] = {20066688,62597760,62522496,512,512,512,49};
int meta_buf_143[] = {62522496,52161152,1,512,7,7,7,7,3,3,1,1,1,1,1,1};
int meta_buf_144[] = {52161152,20067200,62622848,49,512,4608};
int meta_buf_145[] = {22426496,62622848,62647936,512,512,512,49};
int meta_buf_146[] = {62647936,22427008,59662464,49,2048,512};
int meta_buf_147[] = {23475584,60164224,59662464,60063872,49,2048,2048,2048,49};
int meta_buf_148[] = {60063872,62773376,1,7,7,2048,1,1,7,7,1,1,0,0};
int meta_buf_149[] = {62773376,62775424,2048};
int meta_buf_150[] = {62775424,23477632,62777472,1,512,2048};
int meta_buf_151[] = {24526208,62777472,62777472,512};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38,meta_buf_39,meta_buf_40,meta_buf_41,meta_buf_42,meta_buf_43,meta_buf_44,meta_buf_45,meta_buf_46,meta_buf_47,meta_buf_48,meta_buf_49,meta_buf_50,meta_buf_51,meta_buf_52,meta_buf_53,meta_buf_54,meta_buf_55,meta_buf_56,meta_buf_57,meta_buf_58,meta_buf_59,meta_buf_60,meta_buf_61,meta_buf_62,meta_buf_63,meta_buf_64,meta_buf_65,meta_buf_66,meta_buf_67,meta_buf_68,meta_buf_69,meta_buf_70,meta_buf_71,meta_buf_72,meta_buf_73,meta_buf_74,meta_buf_75,meta_buf_76,meta_buf_77,meta_buf_78,meta_buf_79,meta_buf_80,meta_buf_81,meta_buf_82,meta_buf_83,meta_buf_84,meta_buf_85,meta_buf_86,meta_buf_87,meta_buf_88,meta_buf_89,meta_buf_90,meta_buf_91,meta_buf_92,meta_buf_93,meta_buf_94,meta_buf_95,meta_buf_96,meta_buf_97,meta_buf_98,meta_buf_99,meta_buf_100,meta_buf_101,meta_buf_102,meta_buf_103,meta_buf_104,meta_buf_105,meta_buf_106,meta_buf_107,meta_buf_108,meta_buf_109,meta_buf_110,meta_buf_111,meta_buf_112,meta_buf_113,meta_buf_114,meta_buf_115,meta_buf_116,meta_buf_117,meta_buf_118,meta_buf_119,meta_buf_120,meta_buf_121,meta_buf_122,meta_buf_123,meta_buf_124,meta_buf_125,meta_buf_126,meta_buf_127,meta_buf_128,meta_buf_129,meta_buf_130,meta_buf_131,meta_buf_132,meta_buf_133,meta_buf_134,meta_buf_135,meta_buf_136,meta_buf_137,meta_buf_138,meta_buf_139,meta_buf_140,meta_buf_141,meta_buf_142,meta_buf_143,meta_buf_144,meta_buf_145,meta_buf_146,meta_buf_147,meta_buf_148,meta_buf_149,meta_buf_150,meta_buf_151};

extern "C" void init() {
    //static_buffer = (float*)malloc(62777984 * sizeof(float));
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

void transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    float * v2 = (static_buffer + meta_buffer[1]);
    const int v3 = meta_buffer[2];
    const int v4 = meta_buffer[3];
    const int D0 = meta_buffer[4];
    const int D1 = meta_buffer[5];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v5 = v1[d0*v3 + d1];
            float v6;
            {
                v6 = v5;
            }
            v2[d0 + d1*v4] = v6;
        }
    }
}


void im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(const int * meta_buffer)
{
    const float *im = (static_buffer + meta_buffer[0]);
    float *col = (static_buffer + meta_buffer[1]);

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[3];
    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int DH = meta_buffer[10];
    const int DW = meta_buffer[11];
    const int SH = meta_buffer[12];
    const int SW = meta_buffer[13];
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

    for (int gid = 0; gid < N*H2*W2*KH*KW*C1; gid += 1) {
        const int c1 = gid % C1;
        const int kw = gid / C1 % KW;
        const int kh = gid / C1 / KW % KH;
        const int w2 = gid / C1 / KW / KH % W2;
        const int h2 = gid / C1 / KW / KH / W2 % H2;
        const int  n = gid / C1 / KW / KH / W2 / H2;

        const int h1 = h2 * SH - PH + kh * DH;
        const int w1 = w2 * SW - PW + kw * DW;

        col[gid] = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n*H1+h1)*W1+w1)*C1+c1];
    }
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


void fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int v4 = meta_buffer[3];
    const int v5 = meta_buffer[4];
    const int D0 = meta_buffer[5];
    const int D1 = meta_buffer[6];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v6 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v7 = v2[d0 + d1*v4];
            float v8;
            {
                v8 = v7 + v6;
            }
            float v9;
            {
                v9 = v8 > 0 ? v8 : 0;
            }
            v3[d0 + d1*v5] = v9;
        }
    }
}


void maxpooling2d_386ebef75ea973afd833e12e5ea8f6c97456944cd3812afb94b9bb4e(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int H1 = meta_buffer[3];
    const int W1 = meta_buffer[4];
    const int C = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];

    for (int gid = 0; gid < N * H2 * W2 * C; gid += 1) {
        const int c = gid % C;
        const int w2 = gid / C % W2;
        const int h2 = gid / C / W2 % H2;
        const int n = gid / C / W2 / H2;

        float v = -1e7;
        for (int kh = 0; kh < KH; kh++) {
            const int h1 = h2 * SH - PH + kh;
            if (h1 < 0 || h1 >= H1) continue;

            for (int kw = 0; kw < KW; kw++) {
                const int w1 = w2 * SW - PW + kw;
                if (w1 < 0 || w1 >= W1) continue;

                v = v > X[((n * H1 + h1) * W1 + w1) * C + c] ? v : X[((n * H1 + h1) * W1 + w1) * C + c];
            }
        }

        Y[gid] = v;
    }
}


void fusedelementwise_675f21c46771650d2cc89a20d25d5539c744bb0953013cc9cef73e09(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0 + d1*v5];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v10 + v9;
            }
            float v12;
            {
                v12 = v11 + v8;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            v4[d0*v7 + d1] = v13;
        }
    }
}


void fusedelementwise_115284ed8b0aab4a61dd53b6da76f2455cc7ee08add6153c0151c8cd(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0 + d1*v5];
            const float v10 = v3[d0*v6 + d1];
            float v11;
            {
                v11 = v9 + v10;
            }
            float v12;
            {
                v12 = v8 + v11;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            v4[d0*v7 + d1] = v13;
        }
    }
}


void fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0*v5 + d1];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v10 + v9;
            }
            float v12;
            {
                v12 = v8 + v11;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            v4[d0*v7 + d1] = v13;
        }
    }
}


void fusedelementwise_f8d6d8b290dcee52fb6c31ce1de943640bfd9d97be73c8eb51a002bd(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0 + d1*v5];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v9 + v10;
            }
            float v12;
            {
                v12 = v11 + v8;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            v4[d0*v7 + d1] = v13;
        }
    }
}


void fusedelementwise_d4c42aff878e5d25b6cb2a9c80bb8f8c9c0c9be6f23bc9328e4dbaab(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0*v5 + d1];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v10 + v9;
            }
            float v12;
            {
                v12 = v8 + v11;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            v4[d0 + d1*v7] = v13;
        }
    }
}


void averagepooling2d_167ba3530ad0582a26158b6cba3a2591c52450ea74d70f4957952ea5(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int H1 = meta_buffer[3];
    const int W1 = meta_buffer[4];
    const int C = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];

    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];

    for (int gid = 0; gid < N * H2 * W2 * C; gid += 1) {
        const int c = gid % C;
        const int w2 = gid / C % W2;
        const int h2 = gid / C / W2 % H2;
        const int n = gid / C / W2 / H2;

        float v = 0;
        for (int kh = 0; kh < KH; kh++) {
            const int h1 = h2 * SH - PH + kh;
            if (h1 < 0 || h1 >= H1) continue;

            for (int kw = 0; kw < KW; kw++) {
                const int w1 = w2 * SW - PW + kw;
                if (w1 < 0 || w1 >= W1) continue;

                v += X[((n * H1 + h1) * W1 + w1) * C + c];
            }
        }
        v /= KH * KW;

        Y[gid] = v;
    }
}


void transpose_6c1a5765207ae813be68b295e01081389ed8f452899e3a431cad37f6(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    float * v2 = (static_buffer + meta_buffer[1]);
    const int D0 = meta_buffer[2];
    int d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        const float v3 = v1[d0];
        float v4;
        {
            v4 = v3;
        }
        v2[d0] = v4;
    }
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

extern "C" void run() {
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_0);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_1);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_2);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_3);
maxpooling2d_386ebef75ea973afd833e12e5ea8f6c97456944cd3812afb94b9bb4e(meta_buf_4);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_5);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_6);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_7);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_8);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_9);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_10);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_11);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_12);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_13);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_14);
fusedelementwise_675f21c46771650d2cc89a20d25d5539c744bb0953013cc9cef73e09(meta_buf_15);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_16);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_17);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_18);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_19);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_20);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_21);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_22);
fusedelementwise_115284ed8b0aab4a61dd53b6da76f2455cc7ee08add6153c0151c8cd(meta_buf_23);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_24);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_25);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_26);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_27);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_28);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_29);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_30);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_31);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_32);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_33);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_34);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_35);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_36);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_37);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_38);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_39);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_40);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_41);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_42);
fusedelementwise_675f21c46771650d2cc89a20d25d5539c744bb0953013cc9cef73e09(meta_buf_43);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_44);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_45);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_46);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_47);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_48);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_49);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_50);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_51);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_52);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_53);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_54);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_55);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_56);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_57);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_58);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_59);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_60);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_61);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_62);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_63);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_64);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_65);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_66);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_67);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_68);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_69);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_70);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_71);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_72);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_73);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_74);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_75);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_76);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_77);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_78);
fusedelementwise_675f21c46771650d2cc89a20d25d5539c744bb0953013cc9cef73e09(meta_buf_79);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_80);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_81);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_82);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_83);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_84);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_85);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_86);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_87);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_88);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_89);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_90);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_91);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_92);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_93);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_94);
fusedelementwise_115284ed8b0aab4a61dd53b6da76f2455cc7ee08add6153c0151c8cd(meta_buf_95);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_96);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_97);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_98);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_99);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_100);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_101);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_102);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_103);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_104);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_105);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_106);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_107);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_108);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_109);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_110);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_111);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_112);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_113);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_114);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_115);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_116);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_117);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_118);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_119);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_120);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_121);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_122);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_123);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_124);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_125);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_126);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_127);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_128);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_129);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_130);
fusedelementwise_f8d6d8b290dcee52fb6c31ce1de943640bfd9d97be73c8eb51a002bd(meta_buf_131);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_132);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_133);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_134);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_135);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_136);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_137);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_138);
fusedelementwise_574ad6e5a75238f13cdd59f4b7030394f3060f36cc91cc03826eedec(meta_buf_139);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_140);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_141);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_142);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_143);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_144);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_145);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_146);
fusedelementwise_d4c42aff878e5d25b6cb2a9c80bb8f8c9c0c9be6f23bc9328e4dbaab(meta_buf_147);
averagepooling2d_167ba3530ad0582a26158b6cba3a2591c52450ea74d70f4957952ea5(meta_buf_148);
transpose_6c1a5765207ae813be68b295e01081389ed8f452899e3a431cad37f6(meta_buf_149);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_150);
elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(meta_buf_151);

}

