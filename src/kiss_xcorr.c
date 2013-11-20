/*
 * kiss_xcorr.c
 *
 *  Created on: Nov 16, 2013
 *      Author: du
 */

#include <stdlib.h>
#include "kiss_xcorr.h"
#include "_kiss_fft_guts.h"

void rfft_xcorr(size_t n, const kiss_fft_scalar *x, const kiss_fft_scalar *y,
		kiss_fft_scalar *z) {
	int freq_len = n / 2 + 1;
	int i;

	// FFT configs
	kiss_fftr_cfg fft_fwd = kiss_fftr_alloc(n, 0, NULL, NULL );
	kiss_fftr_cfg fft_bwd = kiss_fftr_alloc(n, 1, NULL, NULL );

	// Freq-domain data buffer
	kiss_fft_cpx *X = calloc(freq_len, sizeof(kiss_fft_cpx));
	kiss_fft_cpx *Y = calloc(freq_len, sizeof(kiss_fft_cpx));
	kiss_fft_cpx *Z = calloc(freq_len, sizeof(kiss_fft_cpx));

	// Execute FWD_FFT
	kiss_fftr(fft_fwd, x, X);
	kiss_fftr(fft_fwd, y, Y);

	// Multiply in freq-domain
	for (i = 0; i < freq_len; i++) {
		// take conjugate of Y
		Y[i].i = -Y[i].i;
		C_MUL(Z[i], X[i], Y[i]);
	}

	// Execute BWD_FFT
	kiss_fftri(fft_bwd, Z, z);

	free(fft_fwd);
	free(fft_bwd);

	free(X);
	free(Y);
	free(Z);
}

/*
 * compute 2D cross-correlation function with pre-allocated buffer
 */
void rfft_xcorr2d(size_t h, size_t w, const kiss_fft_scalar *x,
		const kiss_fft_scalar *y, kiss_fft_scalar *z, kiss_fftndr_cfg fft_fwd,
		kiss_fftndr_cfg fft_bwd, kiss_fft_cpx *X, kiss_fft_cpx *Y,
		kiss_fft_cpx *Z) {
	int freq_len = (h / 2 + 1) * w;
	int i;

	// Execute FWD_FFT
	kiss_fftndr(fft_fwd, x, X);
	kiss_fftndr(fft_fwd, y, Y);

	// Multiply in freq-domain
	for (i = 0; i < freq_len; i++) {
		// take conjugate of Y
		Y[i].i = -Y[i].i;
		C_MUL(Z[i], X[i], Y[i]);
	}

	// Execute BWD_FFT
	kiss_fftndri(fft_bwd, Z, z);

}

/*
 * compute 2D cross-correlation function with automatic buffer allocation
 */
void rfft_xcorr2d2(size_t h, size_t w, const kiss_fft_scalar *x,
		const kiss_fft_scalar *y, kiss_fft_scalar *z) {
	int ndim = 2;
	int dims[2] = { h, w };
	int freq_len = (h / 2 + 1) * w;
	int i;

	// FFT configs
	kiss_fftndr_cfg fft_fwd = kiss_fftndr_alloc(dims, ndim, 0, 0, 0);
	kiss_fftndr_cfg fft_bwd = kiss_fftndr_alloc(dims, ndim, 1, 0, 0);

	// Freq-domain data buffer
	kiss_fft_cpx *X = calloc(freq_len, sizeof(kiss_fft_cpx));
	kiss_fft_cpx *Y = calloc(freq_len, sizeof(kiss_fft_cpx));
	kiss_fft_cpx *Z = calloc(freq_len, sizeof(kiss_fft_cpx));

	// Execute cross-correlation calculation
	rfft_xcorr2d(h, w, x, y, z, fft_fwd, fft_bwd, X, Y, Z);

	// free memory
	free(fft_fwd);
	free(fft_bwd);
	free(X);
	free(Y);
	free(Z);
}
