/*
 * kiss_xcorr.h
 *
 *  Created on: Nov 16, 2013
 *      Author: du
 */

#include <stdlib.h>
#include "kiss_fftndr.h"

void rfft_xcorr(size_t n, const kiss_fft_scalar *x, const kiss_fft_scalar *y,
		kiss_fft_scalar *z);

/*
 * compute 2D cross-correlation function with pre-allocated buffer
 */
void rfft_xcorr2d(size_t h, size_t w, const kiss_fft_scalar *x,
		const kiss_fft_scalar *y, kiss_fft_scalar *z, kiss_fftndr_cfg fft_fwd,
		kiss_fftndr_cfg fft_bwd, kiss_fft_cpx *X, kiss_fft_cpx *Y,
		kiss_fft_cpx *Z);

/*
 * compute 2D cross-correlation function with automatic buffer allocation
 */
void rfft_xcorr2d2(size_t h, size_t w, const kiss_fft_scalar *x,
		const kiss_fft_scalar *y, kiss_fft_scalar *z);
