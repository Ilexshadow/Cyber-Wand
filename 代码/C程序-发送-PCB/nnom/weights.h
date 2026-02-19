#include "nnom.h"

/* Weights, bias and Q format */
#define TENSOR_CONV1D_KERNEL_0 {24, 74, 75, -38, 81, 41, -17, 33, -9, 38, -53, -88, -45, -43, -19, 26, -67, -12, -23, 24, 47, -24, 77, 69, -91, 19, 64, -34, -36, -29, -68, -21, 91, -102, -52, 71, -4, -78, -80, 20, -27, 8, 53, -16, -89, 46, -78, -74, 29, -91, -8, 66, -28, -76, 71, 88, -6, 79, 59, -72, 84, 17, -30, -14, 63, 70, 10, 20, 75, 26, 49, 95, 33, 76, -37, 68, 94, 9, -46, 72, -27, -81, 10, -36, -57, 58, -7, 25, -54, -65, -55, 90, 58, -35, 82, 52, -97, 55, 67, -45, 40, 36, 65, -48, 109, 7, -67, 71, 38, 94, 43, 60, 52, 95, 53, 4, 32, 4, -19, 24, -31, -104, -86, 80, -82, -50, 56, -8, 74, -4, 45, 63, 80, -55, 1, -92, 30, 80, -54, -71, 81, -10, 9, 98, 7, -47, -97, -27, -9, -29, -87, 54, -83, -72, 21, 86, -43, 37, 102, 31, -45, 54, -25, -49, 85, -55, -89, 89, -100, -30, 37, -17, 14, -57, 55, -70, -68, -27, -44, -10, -30, -23, 25, -93, -59, -19, -59, -58, 45, 90, -30, 48, 32, 11, -7, 24, -73, -4, -96, -79, 21, -84, -76, -10, -105, 26, -7, -28, -100, -86, 37, -12, -50, 74, -80, -71, -102, -28, 77, -88, -70, 1, -66, -45, 35, -71, -40, -5, -90, -55, -20, -29, -18, 8, 37, 100, 99, -8, 51, 29, -4, 72, -12, 88, 83, -37, 57, -8, 66, 1, 36, 38, 28, -71, 42, -6, 35, 91, -49, -50, 50, 36, 73, -70, 85, 68, 33, 35, 34, -60}

#define TENSOR_CONV1D_KERNEL_0_DEC_BITS {8}

#define TENSOR_CONV1D_BIAS_0 {53, -39, 70, 80, -25, 23, 57, 27, 62, 25, 84, 23, 90, -16, 74, 57, 85, 75, 75, -38, 33, 36, 43, 10, 25, 35, 87, 102, 13, 92}

#define TENSOR_CONV1D_BIAS_0_DEC_BITS {9}

#define CONV1D_BIAS_LSHIFT {4}

#define CONV1D_OUTPUT_RSHIFT {9}

#define TENSOR_CONV1D_1_KERNEL_0 {47, 10, 0, -29, 35, -22, -10, -20, 71, -6, 54, -19, 36, 34, 35, 32, 40, -20, -62, 31, 24, 45, 16, 43, -42, -6, 31, 12, -56, 71, -39, -52, -40, -27, -1, -34, 16, -11, 35, -15, 13, -54, -25, -51, -36, -6, 56, 34, -40, 11, 19, -46, -24, 30, -37, -13, -14, -9, -24, 26, 43, 34, 4, 34, -52, 29, -44, 38, 85, 79, 10, -55, 38, 32, -91, -26, 64, -5, 44, 26, 49, -62, 69, -18, 1, 14, 15, -6, -24, -23, 55, -19, 22, 26, -18, 5, -23, 77, 72, -44, -7, 39, 77, -53, 20, 79, 13, 39, 43, -17, -3, 9, 11, 22, -59, 3, 30, 89, -7, 72, 37, 13, 61, -64, -10, -9, -30, 37, 65, -7, 55, 14, 84, -31, 88, 65, -74, -2, 15, 36, -46, -35, 27, 9, -16, -26, 61, 5, 61, 24, -22, 38, 30, -2, -23, 9, 31, 52, -11, 13, 17, 62, -6, 13, 106, 48, -33, 49, -13, 25, -51, -6, -38, 46, -12, -60, 13, 36, 34, 2, 90, 26, 22, 42, -75, -70, -19, 25, 21, -20, 68, 32, 1, -44, 49, -3, -21, 34, 52, -4, -36, -5, -50, -18, 8, -7, 72, 25, 38, 52, 74, -25, 71, 6, -78, 12, 46, 88, 61, -18, 62, 6, 24, 13, -7, 41, 42, 60, 1, -62, -23, -38, 29, -76, -31, -54, 6, 100, 57, 55, 90, 5, 87, 55, -92, -62, -1, 22, 61, -8, 69, 48, 64, -27, 35, 37, 57, -1, -22, 12, 46, 10, -18, -69, -18, 60, 49, 97, 54, -23, -81, 74, -96, -40, 83, 83, -32, -91, -42, 20, -10, -14, 2, 80, -57, -57, 45, -67, -75, 7, -33, 6, -48, 70, 5, -26, -50, -54, -72, 37, 6, 46, -91, -64, -11, 2, 22, -6, -62, 51, -60, 23, -51, 71, -41, 6, -2, -35, -71, -3, -61, -9, -37, 80, -66, 17, -25, -1, 8, 8, 13, 59, -35, -56, -9, -12, 42, -59, -27, -13, -39, 71, 53, 65, 43, -36, -59, 16, -35, 63, 7, 50, -14, -7, -28, -81, -48, 64, -25, 70, -34, -43, 86, 70, -79, -73, -70, -31, 16, -39, 78, 49, -15, 32, 13, 86, 14, 70, 85, -3, 68, 28, 48, -68, 47, 36, 70, 56, 85, 25, 70, -4, 92, -12, -54, -44, -17, 6, -13, -19, 21, 64, 66, -48, 92, -16, 54, 72, 49, -74, 22, 49, -31, -64, 20, -22, 12, -28, 27, 18, 37, 31, -15, 19, -31, -42, 64, 69, -17, -28, -25, 72, 1, 4, 75, 48, -41, 64, -12, 8, 10, 49, 16, -18, 42, 16, 75, 14, 19, 46, 28, -17, 42, 77, -8, -54, -58, -7, -34, 56, 35, 14, 29, -3, -49, -3, 41, 53, 57, -17, 41, 21, 29, 12, 24, 47, -24, 8, 15, -9, 44, 16, 3, 61, -13, -22, -83, -43, -12, 67, -22, 49, -63, 36, -54, 78, 41, 34, 69, 49, 94, -19, 2, 51, 71, 68, -24, -76, -13, -10, -52, 15, 38, 17, -22, 11, -47, -52, -49, 62, 40, -5, -70, -11, -52, 43, -18, -6, 52, -49, 30, -71, 78, 12, 25, 15, -32, -29, 16, -15, -8, -55, -8, -91, -29, 24, 89, 1, 88, 36, -27, 22, 76, -67, 105, -22, 42, -42, -77, 9, -49, 41, -23, -36, -76, -54, 77, 43, -36, 60, 38, -13, -57, -14, 14, 42, -11, 26, 4, 12, 31, -43, 6, -1, 63, -50, 7, -25, -67, -19, -27, 28, -2, 2, -71, -40, 79, 103, -58, 25, 26, -64, 16, -40, -13, 23, 42, -23, -13, 4, -31, -31, 39, 23, 34, -85, -27, 44, 6, -56, -93, -11, -77, 65, 2, -19, -25, 115, -73, 31, -11, -11, -40, 19, -35, -3, -80, 19, -68, 68, -25, -33, -36, -23, -18, 23, -60, -10, 39, -37, 27, 23, -8, 41, 72, -17, -65, -54, 3, 5, -36, 24, 12, -2, 1, -10, -17, -41, -55, 42, -62, 9, -10, 77, -51, 40, 29, 23, 38, 0, 12, -32, -35, 76, 39, -37, 8, -53, -42, -42, -9, 41, -66, -15, -19, 38, -21, 12, -40, -28, -13, 14, -62, 72, 29, 8, -44, -8, -77, 72, -2, 29, -81, 63, -54, -68, -18, -82, -65, 4, -57, -45, 19, -5, -4, 42, -20, 20, -43, 51, 22, 31, 25, -16, 91, 6, -18, -30, 60, 37, -16, -53, 18, -26, 51, 30, 17, -17, 6, -61, -47, 58, -75, -12, -20, 59, 17, -19, -30, 18, -61, -12, 41, 16, 4, -20, 11, -11, -26, 8, 36, -1, 48, 35, -42, -21, -37, -30, 42, 15, 11, 62, -56, -70, 27, 54, -16, 20, 31, -6, 6, -45, -10, 26, 5, -61, 14, -68, -3, 23, 12, 12, 6, 0, -52, 33, -43, 25, -28, 42, -47, 71, -59, -1, 5, 59, 8, -18, -7, -80, -78, 2, -3, 96, 68, -20, -63, -24, 33, 67, 9, 93, -79, 81, -21, -43, -86, 24, 81, -35, -55, 18, -81, 2, 25, 88, -54, -77, -9, 4, -43, 61, -70, 91, 21, 0, -71, -33, 16, -8, 41, 35, 8, 39, -43, 27, 2, -90, 45, -95, -32, -5, 21, 1, -12, 99, -63, 19, 3, -43, -13, 8, -50, 52, 69, -21, 25, 31, 3, 9, 15, 19, 35, 94, 12, 27, -75, -16, -8, -10, 0, -56, 1, -17, 41, 54, 50, -26, -2, 47, -21, -57, -15, 44, 55, -37, 4, 51, 25, -16, -22, -3, -34, -11, -9, -12, 42, 48, -9, 74, 57, 31, -13, -64, 51, 29, 64, -12, 79, 45, -34, 20, 38, 28, 2, -37, -41, -27, -32, -55, 1, 41, -44, -36, -44, 9, 47, 97, -35, 57, 12, -50, 9, -77, -24, -33, 58, 54, 57, -46, 52, -4, 1, -13, 17, 28, -9, 8, 6, -20, -77, -31, -9, -36, 13, -77, -2, 97, 54, 50, -14, -26, -17, -54, 74, 20, 16, 24, -46, -2, 3, 23, 18, -7, 101, -5, -16, -54, -5, -30, 14, 32, 19, 26, -64, 8, -41, -7, -30, 3, 31, 13, 14, -19, 37, 49, 71, -40, 41, 37, -85, -82, -24, -20, 1, 2, 64, -1, -20, 7, -58, 2, -80, 55, -52, -70, -57, 42, -50, 97, 38, 12, -28, -83, -21, 4, 70, -57, 8, -28, 31, -96, 11, -50, 2, -82, -1, -43, -47, 1, -66, -28, 11, 55, -76, -53, -14, 95, -89, 52, 11, -19, 54, 67, -2, 43, -45, 67, -63, -13, 33, 69, 2, 61, 81, -12, -21, 30, 44, -25, 50, 3, 37, 6, -5, -36, -21, 32, 64, 9, 24, 9, 27, -28, 60, 23, -66, -31, -78, 53, 21, -17, -11, 67, -5, 58, 55, 70, 67, 62, -17, -17, 51, 85, 45, -23, -68, -35, 57, -29, -9, 14, -38, -11, 95, 71, -8, 9, -78, -26, -25, 23, -62, 85, -5, -17, 15, 32, -34, -1, 33, -27, -15, 93, 9, 55, -50, -11, -1, -40, 38, -65, 76, 20, -89, -56, -43, 33, 2, -10, 85, 32, 66, -78, 20, 92, -54, -6, 47, -74, -3, -41, 12, -21, 63, -22, 84, 18, 17, -20, -12, -82, 68, -8, -63, 0, -21, 15, 62, 31, 29, 39, 58, -87, 104, 19, -38, 76, 55, -14, -16, -1, -62, -38, -25, -69, 89, 31, 20, 14, 16, -39, 62, 6, -9, 17, 44, 57, 13, 2, 49, 77, 74, -3, 69, 28, -40, 52, 2, -77, -47, 43, -79, -44, -19, -89, 60, 62, 45, 61, 38, 31, 21, 47, 36, -39, -27, -43, -23, 55, 68, -1, 8, 11, -16, -7, 0, 43, -7, 5, 39, -30, 46, -44, -8, 24, -7, -58, -24, -48, -44, 32, 42, 79, 8, -53, 30, -7, -39, 31, 42, -33, -16, 39, -61, 56, -2, 62, 54, -54, 62, -52, 31, -3, 81, 59, -8, 7, 19, 22, 51, 17, 6, 14, -29, 1, -65, -31, 9, -8, 24, -42, -50, -10, -68, 47, -12, -8, 20, -7, 22, 7, -9, -26, 24, 71, 56, -67, -12, 4}

#define TENSOR_CONV1D_1_KERNEL_0_DEC_BITS {8}

#define TENSOR_CONV1D_1_BIAS_0 {98, 0, 14, 12, 70, 1, 92, -38, -54, 19, 69, 53, -55, 108, -18}

#define TENSOR_CONV1D_1_BIAS_0_DEC_BITS {10}

#define CONV1D_1_BIAS_LSHIFT {2}

#define CONV1D_1_OUTPUT_RSHIFT {9}

#define TENSOR_DENSE_KERNEL_0 {34, 87, -73, 34, 6, -62, 37, -13, -118, 4, 98, 1, 45, 20, 36, -55, -52, -46, 45, 43, -49, 27, 8, -63, 10, -16, 31, 30, -91, 23, -55, -7, 11, 7, -45, 41, -36, 42, -44, 14, -32, 23, -126, -17, 67, -1, -14, -33, -31, -14, -61, -57, -4, 53, 30, -97, -75, 19, 48, 28, -23, 44, 83, 9, -6, 92, 7, -50, 3, -35, 40, -26, 95, 90, -21, 56, 4, 32, -27, -24, 65, -112, 59, -65, 88, -54, 77, -80, -18, -22, 24, -82, -108, 50, 73, 18, -112, 78, 82, 16, 37, 36, -36, 30, -24, 93, 42, 52, -67, -9, 90, 36, 55, 87, -19, 64, -71, -31, 22, -65, 30, -32, 64, -86, -35, 7, -109, 104, -14, 27, -22, -34, 33, 109, -114, 24, -114, -54, -11, -109, 34, -17, -62, -103, 55, 14, 3, 22, -22, -81, 65, 3, -78, -41, 74, -38, -21, 83, 47, 52, 80, 9, -17, 17, 0, -86, -96, 66, -94, -33, -27, -40, 82, -14, -5, 84, 100, -87, 82, 51, 45, 8, -32, 41, 17, -3, 10, 79, -51, -54, -68, -14, -75, -56, -43, -34, -114, 19, 14, -99, 32, 52, 63, -91, 38, -111, 16, -21, -4, 13, -28, -32, -58, 0, -79, 60, -44, -90, 2, -18, -65, 84, -89, 11, -60, -112, 91, 45, -102, 1, -100, -33, 28, -90, 57, -109, 43, -61, 33, -49, -44, 54, 48, -10, 19, 7, 74, -17, -49, 2, 8, 1, 91, 24, 79, -53, 80, -58, -77, 0, 8, -17, 90, -76, -35, -58, 54, -49, -122, -52, -3, 63, -17, 60, -78, -28, -4, -56, -29, -91, -113, 73, -52, 27, -46, -20, 15, -10, 95, -106, 75, -88, -102, 25, -111, 35, -28, 52, -76, 38, 17, 5, 73, 6, -30, -8, 21, 26, 19, -57, -73, 67, 16, -35, 16, 33, -88, -23, 49, -67, -56, 7, 94, 91, 61, 6, -103, -1, -37, 11, -1, -40, -88, 47, -57, 10, 5, -68, 50, -48, 69, 58, -101, 22, 61, 44, 43, -3, 28, 20, -62, 18, -28, -75, -11, -41, -71, -95, 15, 49, -47, 72, -73, -24, 84, -19, 47, -16, -7, -54, 38, -89, 52, -66, -3, 66, 53, -20, -7, -25, -88, -66, 33, 59, -53, -17, -69, 45, 85, 73, 47, -52, 34, -46, 20, 21, -66, 20, -94, -77, -16, -21, -42, 16, 9, 49, 8, -28, -3, -6, 106, 32, 16, 92, 51, 9, 36, -60, 80, 66, 28, 85, -23, -71, -5, 13, 72, -45, 86, -32, 50, -3, -34, 73, 10, -11, 22, -78, 9, -4, -8, -73, 79, 26, -32, -64, 87, 53, 4, 85, -71, 72, 12, 51, 30, 24, -3, 29, 47, 1, -35, 67, 63, 59, 87, 43, 117, -59, -7, 52, 70, -87, -100, 77, -70, -124, -27, 16, 8, -7, 84, -46, 57, -90, 41, 75, -72, -39, -67, -46, -45, -84, 20, -68, 96, -12, -39, -37, 52, 30, -47, 40, -41, 67, -28, 61, 78, 37, 64, -93, 87, -80, -3, 37, -98, -64, -60, 37, -23, -74, -2, 4, -42, -42, -85, -87, -28, -75, -35, 8, 74, -118, -24, -5, 104, -9, -73, 50, -34, -88, -38, 8, 16, 11, 1, 43, 9, -6, 38, 6, 34, 61, -6, 23, -11, -109, -57, 26, 34, -37, -13, -46, -98, -73, -72, 81, 23, -6, -67, 55, -65, -38, 52, 61, -20, -10, 64, 49, 71, -103, 42, 82, 59, -36, -23, -44, 16, 84, -41, 60, 45, -62, -22, 82, -116, 100, -37, 37, -24, 17}

#define TENSOR_DENSE_KERNEL_0_DEC_BITS {8}

#define TENSOR_DENSE_BIAS_0 {-44, 81, -31, -89, -63, -3, 64, 24, 40, 24}

#define TENSOR_DENSE_BIAS_0_DEC_BITS {10}

#define DENSE_BIAS_LSHIFT {1}

#define DENSE_OUTPUT_RSHIFT {9}


/* output q format for each layer */
#define INPUT_1_OUTPUT_DEC 5
#define INPUT_1_OUTPUT_OFFSET 0
#define CONV1D_OUTPUT_DEC 4
#define CONV1D_OUTPUT_OFFSET 0
#define LEAKY_RE_LU_OUTPUT_DEC 4
#define LEAKY_RE_LU_OUTPUT_OFFSET 0
#define CONV1D_1_OUTPUT_DEC 3
#define CONV1D_1_OUTPUT_OFFSET 0
#define LEAKY_RE_LU_1_OUTPUT_DEC 3
#define LEAKY_RE_LU_1_OUTPUT_OFFSET 0
#define MAX_POOLING1D_OUTPUT_DEC 3
#define MAX_POOLING1D_OUTPUT_OFFSET 0
#define FLATTEN_OUTPUT_DEC 3
#define FLATTEN_OUTPUT_OFFSET 0
#define DENSE_OUTPUT_DEC 2
#define DENSE_OUTPUT_OFFSET 0
#define SOFTMAX_OUTPUT_DEC 7
#define SOFTMAX_OUTPUT_OFFSET 0

/* bias shift and output shift for none-weighted layer */

/* tensors and configurations for each layer */
static int8_t nnom_input_data[300] = {0};

const nnom_shape_data_t tensor_input_1_dim[] = {100, 3};
const nnom_qformat_param_t tensor_input_1_dec[] = {5};
const nnom_qformat_param_t tensor_input_1_offset[] = {0};
const nnom_tensor_t tensor_input_1 = {
    .p_data = (void*)nnom_input_data,
    .dim = (nnom_shape_data_t*)tensor_input_1_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_input_1_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_input_1_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 2,
    .bitwidth = 8
};

const nnom_io_config_t input_1_config = {
    .super = {.name = "input_1"},
    .tensor = (nnom_tensor_t*)&tensor_input_1
};
const int8_t tensor_conv1d_kernel_0_data[] = TENSOR_CONV1D_KERNEL_0;

const nnom_shape_data_t tensor_conv1d_kernel_0_dim[] = {3, 3, 30};
const nnom_qformat_param_t tensor_conv1d_kernel_0_dec[] = TENSOR_CONV1D_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_kernel_0 = {
    .p_data = (void*)tensor_conv1d_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 3,
    .bitwidth = 8
};
const int8_t tensor_conv1d_bias_0_data[] = TENSOR_CONV1D_BIAS_0;

const nnom_shape_data_t tensor_conv1d_bias_0_dim[] = {30};
const nnom_qformat_param_t tensor_conv1d_bias_0_dec[] = TENSOR_CONV1D_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_bias_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_bias_0 = {
    .p_data = (void*)tensor_conv1d_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t conv1d_output_shift[] = CONV1D_OUTPUT_RSHIFT;
const nnom_qformat_param_t conv1d_bias_shift[] = CONV1D_BIAS_LSHIFT;
const nnom_conv2d_config_t conv1d_config = {
    .super = {.name = "conv1d"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_conv1d_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_conv1d_bias_0,
    .output_shift = (nnom_qformat_param_t *)&conv1d_output_shift, 
    .bias_shift = (nnom_qformat_param_t *)&conv1d_bias_shift, 
    .filter_size = 30,
    .kernel_size = {3},
    .stride_size = {3},
    .padding_size = {0, 0},
    .dilation_size = {1},
    .padding_type = PADDING_SAME
};
const int8_t tensor_conv1d_1_kernel_0_data[] = TENSOR_CONV1D_1_KERNEL_0;

const nnom_shape_data_t tensor_conv1d_1_kernel_0_dim[] = {3, 30, 15};
const nnom_qformat_param_t tensor_conv1d_1_kernel_0_dec[] = TENSOR_CONV1D_1_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_1_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_1_kernel_0 = {
    .p_data = (void*)tensor_conv1d_1_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_1_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_1_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_1_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 3,
    .bitwidth = 8
};
const int8_t tensor_conv1d_1_bias_0_data[] = TENSOR_CONV1D_1_BIAS_0;

const nnom_shape_data_t tensor_conv1d_1_bias_0_dim[] = {15};
const nnom_qformat_param_t tensor_conv1d_1_bias_0_dec[] = TENSOR_CONV1D_1_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_1_bias_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_1_bias_0 = {
    .p_data = (void*)tensor_conv1d_1_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_1_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_1_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_1_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t conv1d_1_output_shift[] = CONV1D_1_OUTPUT_RSHIFT;
const nnom_qformat_param_t conv1d_1_bias_shift[] = CONV1D_1_BIAS_LSHIFT;
const nnom_conv2d_config_t conv1d_1_config = {
    .super = {.name = "conv1d_1"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_conv1d_1_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_conv1d_1_bias_0,
    .output_shift = (nnom_qformat_param_t *)&conv1d_1_output_shift, 
    .bias_shift = (nnom_qformat_param_t *)&conv1d_1_bias_shift, 
    .filter_size = 15,
    .kernel_size = {3},
    .stride_size = {3},
    .padding_size = {0, 0},
    .dilation_size = {1},
    .padding_type = PADDING_SAME
};

const nnom_pool_config_t max_pooling1d_config = {
    .super = {.name = "max_pooling1d"},
    .padding_type = PADDING_VALID,
    .output_shift = 0,
    .kernel_size = {3},
    .stride_size = {3},
    .num_dim = 1
};

const nnom_flatten_config_t flatten_config = {
    .super = {.name = "flatten"}
};
const int8_t tensor_dense_kernel_0_data[] = TENSOR_DENSE_KERNEL_0;

const nnom_shape_data_t tensor_dense_kernel_0_dim[] = {60, 10};
const nnom_qformat_param_t tensor_dense_kernel_0_dec[] = TENSOR_DENSE_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_dense_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_dense_kernel_0 = {
    .p_data = (void*)tensor_dense_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_dense_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_dense_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_dense_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 2,
    .bitwidth = 8
};
const int8_t tensor_dense_bias_0_data[] = TENSOR_DENSE_BIAS_0;

const nnom_shape_data_t tensor_dense_bias_0_dim[] = {10};
const nnom_qformat_param_t tensor_dense_bias_0_dec[] = TENSOR_DENSE_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_dense_bias_0_offset[] = {0};
const nnom_tensor_t tensor_dense_bias_0 = {
    .p_data = (void*)tensor_dense_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_dense_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_dense_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_dense_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t dense_output_shift[] = DENSE_OUTPUT_RSHIFT;
const nnom_qformat_param_t dense_bias_shift[] = DENSE_BIAS_LSHIFT;
const nnom_dense_config_t dense_config = {
    .super = {.name = "dense"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_dense_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_dense_bias_0,
    .output_shift = (nnom_qformat_param_t *)&dense_output_shift,
    .bias_shift = (nnom_qformat_param_t *)&dense_bias_shift
};

const nnom_softmax_config_t softmax_config = {
    .super = {.name = "softmax"}
};
static int8_t nnom_output_data[10] = {0};

const nnom_shape_data_t tensor_output0_dim[] = {10};
const nnom_qformat_param_t tensor_output0_dec[] = {SOFTMAX_OUTPUT_DEC};
const nnom_qformat_param_t tensor_output0_offset[] = {0};
const nnom_tensor_t tensor_output0 = {
    .p_data = (void*)nnom_output_data,
    .dim = (nnom_shape_data_t*)tensor_output0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_output0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_output0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_io_config_t output0_config = {
    .super = {.name = "output0"},
    .tensor = (nnom_tensor_t*)&tensor_output0
};
/* model version */
#define NNOM_MODEL_VERSION (10000*0 + 100*4 + 3)

/* nnom model */
static nnom_model_t* nnom_model_create(void)
{
	static nnom_model_t model;
	nnom_layer_t* layer[10];

	check_model_version(NNOM_MODEL_VERSION);
	new_model(&model);

	layer[0] = input_s(&input_1_config);
	layer[1] = model.hook(conv2d_s(&conv1d_config), layer[0]);
	layer[2] = model.active(act_leaky_relu(0.300000f), layer[1]);
	layer[3] = model.hook(conv2d_s(&conv1d_1_config), layer[2]);
	layer[4] = model.active(act_leaky_relu(0.300000f), layer[3]);
	layer[5] = model.hook(maxpool_s(&max_pooling1d_config), layer[4]);
	layer[6] = model.hook(flatten_s(&flatten_config), layer[5]);
	layer[7] = model.hook(dense_s(&dense_config), layer[6]);
	layer[8] = model.hook(softmax_s(&softmax_config), layer[7]);
	layer[9] = model.hook(output_s(&output0_config), layer[8]);
	model_compile(&model, layer[0], layer[9]);
	return &model;
}
