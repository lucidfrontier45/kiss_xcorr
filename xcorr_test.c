/*
 * xcorr_test.c
 *
 *  Created on: Nov 20, 2013
 *      Author: du
 */

#include <stdio.h>
#include <stdlib.h>
#include "kiss_xcorr.h"

int find_max(const kiss_fft_scalar *dat, size_t N) {
	kiss_fft_scalar max_v = -100000.0;
	int max_i = -1;
	int i;

	for (i = 0; i < N; i++) {
		if (dat[i] > max_v) {
			max_i = i;
			max_v = dat[i];
		}
	}

	return max_i;

}

static void read_raw_image(const char *fname, size_t N, kiss_fft_scalar *dst) {
	FILE *fp = fopen(fname, "rb");
	fread(dst, sizeof(kiss_fft_scalar), N, fp);
	fclose(fp);
}


#define N 128
int main(int argc, char **argv) {
	int i, j, max_i;
	kiss_fft_scalar x[N * N], y[N * N], z[N * N];
	const char *image_file = argv[1];
	const char *header_file = argv[2];
	read_raw_image(image_file, N * N, x);
	read_raw_image(header_file, N * N, y);


	rfft_xcorr2d2(N, N, x, y, z, KISS_XCORR);
	max_i = find_max(z, N * N);
	printf("max : %d, %d, %f\n", max_i / N, max_i % N, z[max_i] / (N * N));

	return 0;
}
