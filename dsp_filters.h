#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

typedef struct
{
    int M;
    float *B;
    float *x;
} FIR;

void fir_init(FIR *fir, int M, float *B);
float fir_filt(FIR *fir, float input);

typedef struct
{
    int M, N;
    float *B, *A;
    float *x, *y;
} IIR;

void iir_init(IIR *iir, int M, float *B, int N, float *A);
float iir_filt(IIR *iir, float input);

#ifdef __cplusplus
}
#endif
