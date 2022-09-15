#include "dsp_filters.h"

/*
    FIR Filter
*/

void fir_init(FIR *fir, int M, float *B)
{
    unsigned long numbytes = M * sizeof(float);

    // Filter size
    fir->M = M;

    // Allocate memory
    fir->B = (float *)malloc(numbytes);
    fir->x = (float *)malloc(numbytes);

    // Initialize buffer
    memset(fir->x, 0, numbytes);

    // Copy coefficients
    memcpy(fir->B, B, numbytes);
}

float fir_filt(FIR *fir, float input)
{
    float output = 0.0;

    fir->x[0] = input;

    for (int i = 0; i < fir->M; i++)
        output += fir->B[i] * fir->x[i];
    for (int i = fir->M - 1; i > 0; i--)
        fir->x[i] = fir->x[i - 1];

    return output;
}

/*
    IIR Filter
*/

void iir_init(IIR *iir, int M, float *B, int N, float *A)
{
    unsigned long numbytesB = M * sizeof(float);
    unsigned long numbytesA = N * sizeof(float);

    // Filter sizes
    iir->M = M;
    iir->N = N;

    // Allocate memory
    iir->B = (float *)malloc(numbytesB);
    iir->A = (float *)malloc(numbytesA);
    iir->x = (float *)malloc(numbytesB);
    iir->y = (float *)malloc(numbytesA);

    // Initialize buffers
    memset(iir->x, 0, numbytesB);
    memset(iir->y, 0, numbytesA);

    // Copy coefficients
    memcpy(iir->B, B, numbytesB);
    memcpy(iir->A, A, numbytesA);
}

float iir_filt(IIR *iir, float input)
{
    float output = 0.0f;

    iir->x[0] = input;

    for (int i = 0; i < iir->M; i++)
        output += iir->B[i] * iir->x[i];
    for (int i = iir->M - 1; i > 0; i--)
        iir->x[i] = iir->x[i - 1];

    for (int i = 1; i < iir->N; i++)
        output -= iir->A[i] * iir->y[i - 1];
    for (int i = iir->N - 1; i > 0; i--)
        iir->y[i] = iir->y[i - 1];

    iir->y[0] = output;

    return output;
}
