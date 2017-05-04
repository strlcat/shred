#include <stdint.h>
#include <string.h>
#include "tf1024.h"

#ifndef TF_FAST
#define k0 ctx->K[0]
#define k1 ctx->K[1]
#define k2 ctx->K[2]
#define k3 ctx->K[3]
#define k4 ctx->K[4]
#define k5 ctx->K[5]
#define k6 ctx->K[6]
#define k7 ctx->K[7]
#define k8 ctx->K[8]
#define k9 ctx->K[9]
#define k10 ctx->K[10]
#define k11 ctx->K[11]
#define k12 ctx->K[12]
#define k13 ctx->K[13]
#define k14 ctx->K[14]
#define k15 ctx->K[15]
#define k16 ctx->K[16]

#define b0 output[0]
#define b1 output[1]
#define b2 output[2]
#define b3 output[3]
#define b4 output[4]
#define b5 output[5]
#define b6 output[6]
#define b7 output[7]
#define b8 output[8]
#define b9 output[9]
#define b10 output[10]
#define b11 output[11]
#define b12 output[12]
#define b13 output[13]
#define b14 output[14]
#define b15 output[15]

#define t0 ctx->T[0]
#define t1 ctx->T[1]
#define t2 ctx->T[2]
#endif

#define KE_ARX(x, xx, k, kk, s)				\
	do {						\
		x += k;		 			\
		xx += x + kk;				\
		x = ((x << s) | (x >> (64 - s))) ^ xx;	\
	} while (0)

#define BE_ARX(x, xx, s)				\
	do {						\
		x += xx;				\
		xx = ((xx << s) | (xx >> (64 - s))) ^ x;\
	} while (0)

#define KD_ARX(x, xx, k, kk, s)				\
	do {						\
		x ^= xx;				\
		x = (x >> s) | (x << (64 - s));		\
		xx -= x + k;				\
		x -= kk;				\
	} while (0)

#define BD_ARX(x, xx, s)				\
	do {						\
		x ^= xx;				\
		x = (x >> s) | (x << (64 - s));		\
		xx -= x;				\
	} while (0)


void tfc1024_encrypt_blk(tfc1024_ctx *ctx, const uint64_t *input, uint64_t *output)
{
#ifdef TF_FAST
	uint64_t b0 = input[0], b1 = input[1],
		b2 = input[2], b3 = input[3],
		b4 = input[4], b5 = input[5],
		b6 = input[6], b7 = input[7],
		b8 = input[8], b9 = input[9],
		b10 = input[10], b11 = input[11],
		b12 = input[12], b13 = input[13],
		b14 = input[14], b15 = input[15];
	uint64_t k0 = ctx->K[0], k1 = ctx->K[1],
		k2 = ctx->K[2], k3 = ctx->K[3],
		k4 = ctx->K[4], k5 = ctx->K[5],
		k6 = ctx->K[6], k7 = ctx->K[7],
		k8 = ctx->K[8], k9 = ctx->K[9],
		k10 = ctx->K[10], k11 = ctx->K[11],
		k12 = ctx->K[12], k13 = ctx->K[13],
		k14 = ctx->K[14], k15 = ctx->K[15],
		k16 = ctx->K[16];
	uint64_t t0 = ctx->T[0], t1 = ctx->T[1],
		t2 = ctx->T[2];
#else
		memcpy(output, input, TF_BLOCK_SIZE);
#endif

		KE_ARX(b1, b0, k1, k0, 24);
		KE_ARX(b3, b2, k3, k2, 13);
		KE_ARX(b5, b4, k5, k4, 8);
		KE_ARX(b7, b6, k7, k6, 47);
		KE_ARX(b9, b8, k9, k8, 8);
		KE_ARX(b11, b10, k11, k10, 17);
		KE_ARX(b13, b12, k13 + t0, k12, 22);
		KE_ARX(b15, b14, k15, k14 + t1, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k2, k1, 41);
		KE_ARX(b3, b2, k4, k3, 9);
		KE_ARX(b5, b4, k6, k5, 37);
		KE_ARX(b7, b6, k8, k7, 31);
		KE_ARX(b9, b8, k10, k9, 12);
		KE_ARX(b11, b10, k12, k11, 47);
		KE_ARX(b13, b12, k14 + t1, k13, 44);
		KE_ARX(b15, b14, k16 + 1, k15 + t2, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k3, k2, 24);
		KE_ARX(b3, b2, k5, k4, 13);
		KE_ARX(b5, b4, k7, k6, 8);
		KE_ARX(b7, b6, k9, k8, 47);
		KE_ARX(b9, b8, k11, k10, 8);
		KE_ARX(b11, b10, k13, k12, 17);
		KE_ARX(b13, b12, k15 + t2, k14, 22);
		KE_ARX(b15, b14, k0 + 2, k16 + t0, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k4, k3, 41);
		KE_ARX(b3, b2, k6, k5, 9);
		KE_ARX(b5, b4, k8, k7, 37);
		KE_ARX(b7, b6, k10, k9, 31);
		KE_ARX(b9, b8, k12, k11, 12);
		KE_ARX(b11, b10, k14, k13, 47);
		KE_ARX(b13, b12, k16 + t0, k15, 44);
		KE_ARX(b15, b14, k1 + 3, k0 + t1, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k5, k4, 24);
		KE_ARX(b3, b2, k7, k6, 13);
		KE_ARX(b5, b4, k9, k8, 8);
		KE_ARX(b7, b6, k11, k10, 47);
		KE_ARX(b9, b8, k13, k12, 8);
		KE_ARX(b11, b10, k15, k14, 17);
		KE_ARX(b13, b12, k0 + t1, k16, 22);
		KE_ARX(b15, b14, k2 + 4, k1 + t2, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k6, k5, 41);
		KE_ARX(b3, b2, k8, k7, 9);
		KE_ARX(b5, b4, k10, k9, 37);
		KE_ARX(b7, b6, k12, k11, 31);
		KE_ARX(b9, b8, k14, k13, 12);
		KE_ARX(b11, b10, k16, k15, 47);
		KE_ARX(b13, b12, k1 + t2, k0, 44);
		KE_ARX(b15, b14, k3 + 5, k2 + t0, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k7, k6, 24);
		KE_ARX(b3, b2, k9, k8, 13);
		KE_ARX(b5, b4, k11, k10, 8);
		KE_ARX(b7, b6, k13, k12, 47);
		KE_ARX(b9, b8, k15, k14, 8);
		KE_ARX(b11, b10, k0, k16, 17);
		KE_ARX(b13, b12, k2 + t0, k1, 22);
		KE_ARX(b15, b14, k4 + 6, k3 + t1, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k8, k7, 41);
		KE_ARX(b3, b2, k10, k9, 9);
		KE_ARX(b5, b4, k12, k11, 37);
		KE_ARX(b7, b6, k14, k13, 31);
		KE_ARX(b9, b8, k16, k15, 12);
		KE_ARX(b11, b10, k1, k0, 47);
		KE_ARX(b13, b12, k3 + t1, k2, 44);
		KE_ARX(b15, b14, k5 + 7, k4 + t2, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k9, k8, 24);
		KE_ARX(b3, b2, k11, k10, 13);
		KE_ARX(b5, b4, k13, k12, 8);
		KE_ARX(b7, b6, k15, k14, 47);
		KE_ARX(b9, b8, k0, k16, 8);
		KE_ARX(b11, b10, k2, k1, 17);
		KE_ARX(b13, b12, k4 + t2, k3, 22);
		KE_ARX(b15, b14, k6 + 8, k5 + t0, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k10, k9, 41);
		KE_ARX(b3, b2, k12, k11, 9);
		KE_ARX(b5, b4, k14, k13, 37);
		KE_ARX(b7, b6, k16, k15, 31);
		KE_ARX(b9, b8, k1, k0, 12);
		KE_ARX(b11, b10, k3, k2, 47);
		KE_ARX(b13, b12, k5 + t0, k4, 44);
		KE_ARX(b15, b14, k7 + 9, k6 + t1, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k11, k10, 24);
		KE_ARX(b3, b2, k13, k12, 13);
		KE_ARX(b5, b4, k15, k14, 8);
		KE_ARX(b7, b6, k0, k16, 47);
		KE_ARX(b9, b8, k2, k1, 8);
		KE_ARX(b11, b10, k4, k3, 17);
		KE_ARX(b13, b12, k6 + t1, k5, 22);
		KE_ARX(b15, b14, k8 + 10, k7 + t2, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k12, k11, 41);
		KE_ARX(b3, b2, k14, k13, 9);
		KE_ARX(b5, b4, k16, k15, 37);
		KE_ARX(b7, b6, k1, k0, 31);
		KE_ARX(b9, b8, k3, k2, 12);
		KE_ARX(b11, b10, k5, k4, 47);
		KE_ARX(b13, b12, k7 + t2, k6, 44);
		KE_ARX(b15, b14, k9 + 11, k8 + t0, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k13, k12, 24);
		KE_ARX(b3, b2, k15, k14, 13);
		KE_ARX(b5, b4, k0, k16, 8);
		KE_ARX(b7, b6, k2, k1, 47);
		KE_ARX(b9, b8, k4, k3, 8);
		KE_ARX(b11, b10, k6, k5, 17);
		KE_ARX(b13, b12, k8 + t0, k7, 22);
		KE_ARX(b15, b14, k10 + 12, k9 + t1, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k14, k13, 41);
		KE_ARX(b3, b2, k16, k15, 9);
		KE_ARX(b5, b4, k1, k0, 37);
		KE_ARX(b7, b6, k3, k2, 31);
		KE_ARX(b9, b8, k5, k4, 12);
		KE_ARX(b11, b10, k7, k6, 47);
		KE_ARX(b13, b12, k9 + t1, k8, 44);
		KE_ARX(b15, b14, k11 + 13, k10 + t2, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k15, k14, 24);
		KE_ARX(b3, b2, k0, k16, 13);
		KE_ARX(b5, b4, k2, k1, 8);
		KE_ARX(b7, b6, k4, k3, 47);
		KE_ARX(b9, b8, k6, k5, 8);
		KE_ARX(b11, b10, k8, k7, 17);
		KE_ARX(b13, b12, k10 + t2, k9, 22);
		KE_ARX(b15, b14, k12 + 14, k11 + t0, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k16, k15, 41);
		KE_ARX(b3, b2, k1, k0, 9);
		KE_ARX(b5, b4, k3, k2, 37);
		KE_ARX(b7, b6, k5, k4, 31);
		KE_ARX(b9, b8, k7, k6, 12);
		KE_ARX(b11, b10, k9, k8, 47);
		KE_ARX(b13, b12, k11 + t0, k10, 44);
		KE_ARX(b15, b14, k13 + 15, k12 + t1, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k0, k16, 24);
		KE_ARX(b3, b2, k2, k1, 13);
		KE_ARX(b5, b4, k4, k3, 8);
		KE_ARX(b7, b6, k6, k5, 47);
		KE_ARX(b9, b8, k8, k7, 8);
		KE_ARX(b11, b10, k10, k9, 17);
		KE_ARX(b13, b12, k12 + t1, k11, 22);
		KE_ARX(b15, b14, k14 + 16, k13 + t2, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k1, k0, 41);
		KE_ARX(b3, b2, k3, k2, 9);
		KE_ARX(b5, b4, k5, k4, 37);
		KE_ARX(b7, b6, k7, k6, 31);
		KE_ARX(b9, b8, k9, k8, 12);
		KE_ARX(b11, b10, k11, k10, 47);
		KE_ARX(b13, b12, k13 + t2, k12, 44);
		KE_ARX(b15, b14, k15 + 17, k14 + t0, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);


		KE_ARX(b1, b0, k2, k1, 24);
		KE_ARX(b3, b2, k4, k3, 13);
		KE_ARX(b5, b4, k6, k5, 8);
		KE_ARX(b7, b6, k8, k7, 47);
		KE_ARX(b9, b8, k10, k9, 8);
		KE_ARX(b11, b10, k12, k11, 17);
		KE_ARX(b13, b12, k14 + t0, k13, 22);
		KE_ARX(b15, b14, k16 + 18, k15 + t1, 37);
		BE_ARX(b0, b9, 38);
		BE_ARX(b2, b13, 19);
		BE_ARX(b6, b11, 10);
		BE_ARX(b4, b15, 55);
		BE_ARX(b10, b7, 49);
		BE_ARX(b12, b3, 18);
		BE_ARX(b14, b5, 23);
		BE_ARX(b8, b1, 52);
		BE_ARX(b0, b7, 33);
		BE_ARX(b2, b5, 4);
		BE_ARX(b4, b3, 51);
		BE_ARX(b6, b1, 13);
		BE_ARX(b12, b15, 34);
		BE_ARX(b14, b13, 41);
		BE_ARX(b8, b11, 59);
		BE_ARX(b10, b9, 17);
		BE_ARX(b0, b15, 5);
		BE_ARX(b2, b11, 20);
		BE_ARX(b6, b13, 48);
		BE_ARX(b4, b9, 41);
		BE_ARX(b14, b1, 47);
		BE_ARX(b8, b5, 28);
		BE_ARX(b10, b3, 16);
		BE_ARX(b12, b7, 25);


		KE_ARX(b1, b0, k3, k2, 41);
		KE_ARX(b3, b2, k5, k4, 9);
		KE_ARX(b5, b4, k7, k6, 37);
		KE_ARX(b7, b6, k9, k8, 31);
		KE_ARX(b9, b8, k11, k10, 12);
		KE_ARX(b11, b10, k13, k12, 47);
		KE_ARX(b13, b12, k15 + t1, k14, 44);
		KE_ARX(b15, b14, k0 + 19, k16 + t2, 30);
		BE_ARX(b0, b9, 16);
		BE_ARX(b2, b13, 34);
		BE_ARX(b6, b11, 56);
		BE_ARX(b4, b15, 51);
		BE_ARX(b10, b7, 4);
		BE_ARX(b12, b3, 53);
		BE_ARX(b14, b5, 42);
		BE_ARX(b8, b1, 41);
		BE_ARX(b0, b7, 31);
		BE_ARX(b2, b5, 44);
		BE_ARX(b4, b3, 47);
		BE_ARX(b6, b1, 46);
		BE_ARX(b12, b15, 19);
		BE_ARX(b14, b13, 42);
		BE_ARX(b8, b11, 44);
		BE_ARX(b10, b9, 25);
		BE_ARX(b0, b15, 9);
		BE_ARX(b2, b11, 48);
		BE_ARX(b6, b13, 35);
		BE_ARX(b4, b9, 52);
		BE_ARX(b14, b1, 23);
		BE_ARX(b8, b5, 31);
		BE_ARX(b10, b3, 37);
		BE_ARX(b12, b7, 20);
#ifdef TF_FAST
		output[0] = b0 + k3;
		output[1] = b1 + k4;
		output[2] = b2 + k5;
		output[3] = b3 + k6;
		output[4] = b4 + k7;
		output[5] = b5 + k8;
		output[6] = b6 + k9;
		output[7] = b7 + k10;
		output[8] = b8 + k11;
		output[9] = b9 + k12;
		output[10] = b10 + k13;
		output[11] = b11 + k14;
		output[12] = b12 + k15;
		output[13] = b13 + k16 + t2;
		output[14] = b14 + k0 + t0;
		output[15] = b15 + k1 + 20;
#else
		b0 += k3;
		b1 += k4;
		b2 += k5;
		b3 += k6;
		b4 += k7;
		b5 += k8;
		b6 += k9;
		b7 += k10;
		b8 += k11;
		b9 += k12;
		b10 += k13;
		b11 += k14;
		b12 += k15;
		b13 += k16 + t2;
		b14 += k0 + t0;
		b15 += k1 + 20;
#endif
}

#ifdef TF_NEED_DECRYPT
void tfc1024_decrypt_blk(tfc1024_ctx *ctx, const uint64_t *input, uint64_t *output)
{
#ifdef TF_FAST
	uint64_t b0 = input[0], b1 = input[1],
		b2 = input[2], b3 = input[3],
		b4 = input[4], b5 = input[5],
		b6 = input[6], b7 = input[7],
		b8 = input[8], b9 = input[9],
		b10 = input[10], b11 = input[11],
		b12 = input[12], b13 = input[13],
		b14 = input[14], b15 = input[15];
	uint64_t k0 = ctx->K[0], k1 = ctx->K[1],
		k2 = ctx->K[2], k3 = ctx->K[3],
		k4 = ctx->K[4], k5 = ctx->K[5],
		k6 = ctx->K[6], k7 = ctx->K[7],
		k8 = ctx->K[8], k9 = ctx->K[9],
		k10 = ctx->K[10], k11 = ctx->K[11],
		k12 = ctx->K[12], k13 = ctx->K[13],
		k14 = ctx->K[14], k15 = ctx->K[15],
		k16 = ctx->K[16];
	uint64_t t0 = ctx->T[0], t1 = ctx->T[1],
		t2 = ctx->T[2];
#else
		memcpy(output, input, TF_BLOCK_SIZE);
#endif
		b0 -= k3;
		b1 -= k4;
		b2 -= k5;
		b3 -= k6;
		b4 -= k7;
		b5 -= k8;
		b6 -= k9;
		b7 -= k10;
		b8 -= k11;
		b9 -= k12;
		b10 -= k13;
		b11 -= k14;
		b12 -= k15;
		b13 -= k16 + t2;
		b14 -= k0 + t0;
		b15 -= k1 + 20;


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k16 + t2, k0 + 19, 30);
		KD_ARX(b13, b12, k14, k15 + t1, 44);
		KD_ARX(b11, b10, k12, k13, 47);
		KD_ARX(b9, b8, k10, k11, 12);
		KD_ARX(b7, b6, k8, k9, 31);
		KD_ARX(b5, b4, k6, k7, 37);
		KD_ARX(b3, b2, k4, k5, 9);
		KD_ARX(b1, b0, k2, k3, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k15 + t1, k16 + 18, 37);
		KD_ARX(b13, b12, k13, k14 + t0, 22);
		KD_ARX(b11, b10, k11, k12, 17);
		KD_ARX(b9, b8, k9, k10, 8);
		KD_ARX(b7, b6, k7, k8, 47);
		KD_ARX(b5, b4, k5, k6, 8);
		KD_ARX(b3, b2, k3, k4, 13);
		KD_ARX(b1, b0, k1, k2, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k14 + t0, k15 + 17, 30);
		KD_ARX(b13, b12, k12, k13 + t2, 44);
		KD_ARX(b11, b10, k10, k11, 47);
		KD_ARX(b9, b8, k8, k9, 12);
		KD_ARX(b7, b6, k6, k7, 31);
		KD_ARX(b5, b4, k4, k5, 37);
		KD_ARX(b3, b2, k2, k3, 9);
		KD_ARX(b1, b0, k0, k1, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k13 + t2, k14 + 16, 37);
		KD_ARX(b13, b12, k11, k12 + t1, 22);
		KD_ARX(b11, b10, k9, k10, 17);
		KD_ARX(b9, b8, k7, k8, 8);
		KD_ARX(b7, b6, k5, k6, 47);
		KD_ARX(b5, b4, k3, k4, 8);
		KD_ARX(b3, b2, k1, k2, 13);
		KD_ARX(b1, b0, k16, k0, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k12 + t1, k13 + 15, 30);
		KD_ARX(b13, b12, k10, k11 + t0, 44);
		KD_ARX(b11, b10, k8, k9, 47);
		KD_ARX(b9, b8, k6, k7, 12);
		KD_ARX(b7, b6, k4, k5, 31);
		KD_ARX(b5, b4, k2, k3, 37);
		KD_ARX(b3, b2, k0, k1, 9);
		KD_ARX(b1, b0, k15, k16, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k11 + t0, k12 + 14, 37);
		KD_ARX(b13, b12, k9, k10 + t2, 22);
		KD_ARX(b11, b10, k7, k8, 17);
		KD_ARX(b9, b8, k5, k6, 8);
		KD_ARX(b7, b6, k3, k4, 47);
		KD_ARX(b5, b4, k1, k2, 8);
		KD_ARX(b3, b2, k16, k0, 13);
		KD_ARX(b1, b0, k14, k15, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k10 + t2, k11 + 13, 30);
		KD_ARX(b13, b12, k8, k9 + t1, 44);
		KD_ARX(b11, b10, k6, k7, 47);
		KD_ARX(b9, b8, k4, k5, 12);
		KD_ARX(b7, b6, k2, k3, 31);
		KD_ARX(b5, b4, k0, k1, 37);
		KD_ARX(b3, b2, k15, k16, 9);
		KD_ARX(b1, b0, k13, k14, 41);
		BD_ARX(b7, b12, 25);


		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k9 + t1, k10 + 12, 37);
		KD_ARX(b13, b12, k7, k8 + t0, 22);
		KD_ARX(b11, b10, k5, k6, 17);
		KD_ARX(b9, b8, k3, k4, 8);
		KD_ARX(b7, b6, k1, k2, 47);
		KD_ARX(b5, b4, k16, k0, 8);
		KD_ARX(b3, b2, k14, k15, 13);
		KD_ARX(b1, b0, k12, k13, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k8 + t0, k9 + 11, 30);
		KD_ARX(b13, b12, k6, k7 + t2, 44);
		KD_ARX(b11, b10, k4, k5, 47);
		KD_ARX(b9, b8, k2, k3, 12);
		KD_ARX(b7, b6, k0, k1, 31);
		KD_ARX(b5, b4, k15, k16, 37);
		KD_ARX(b3, b2, k13, k14, 9);
		KD_ARX(b1, b0, k11, k12, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k7 + t2, k8 + 10, 37);
		KD_ARX(b13, b12, k5, k6 + t1, 22);
		KD_ARX(b11, b10, k3, k4, 17);
		KD_ARX(b9, b8, k1, k2, 8);
		KD_ARX(b7, b6, k16, k0, 47);
		KD_ARX(b5, b4, k14, k15, 8);
		KD_ARX(b3, b2, k12, k13, 13);
		KD_ARX(b1, b0, k10, k11, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k6 + t1, k7 + 9, 30);
		KD_ARX(b13, b12, k4, k5 + t0, 44);
		KD_ARX(b11, b10, k2, k3, 47);
		KD_ARX(b9, b8, k0, k1, 12);
		KD_ARX(b7, b6, k15, k16, 31);
		KD_ARX(b5, b4, k13, k14, 37);
		KD_ARX(b3, b2, k11, k12, 9);
		KD_ARX(b1, b0, k9, k10, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k5 + t0, k6 + 8, 37);
		KD_ARX(b13, b12, k3, k4 + t2, 22);
		KD_ARX(b11, b10, k1, k2, 17);
		KD_ARX(b9, b8, k16, k0, 8);
		KD_ARX(b7, b6, k14, k15, 47);
		KD_ARX(b5, b4, k12, k13, 8);
		KD_ARX(b3, b2, k10, k11, 13);
		KD_ARX(b1, b0, k8, k9, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k4 + t2, k5 + 7, 30);
		KD_ARX(b13, b12, k2, k3 + t1, 44);
		KD_ARX(b11, b10, k0, k1, 47);
		KD_ARX(b9, b8, k15, k16, 12);
		KD_ARX(b7, b6, k13, k14, 31);
		KD_ARX(b5, b4, k11, k12, 37);
		KD_ARX(b3, b2, k9, k10, 9);
		KD_ARX(b1, b0, k7, k8, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k3 + t1, k4 + 6, 37);
		KD_ARX(b13, b12, k1, k2 + t0, 22);
		KD_ARX(b11, b10, k16, k0, 17);
		KD_ARX(b9, b8, k14, k15, 8);
		KD_ARX(b7, b6, k12, k13, 47);
		KD_ARX(b5, b4, k10, k11, 8);
		KD_ARX(b3, b2, k8, k9, 13);
		KD_ARX(b1, b0, k6, k7, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k2 + t0, k3 + 5, 30);
		KD_ARX(b13, b12, k0, k1 + t2, 44);
		KD_ARX(b11, b10, k15, k16, 47);
		KD_ARX(b9, b8, k13, k14, 12);
		KD_ARX(b7, b6, k11, k12, 31);
		KD_ARX(b5, b4, k9, k10, 37);
		KD_ARX(b3, b2, k7, k8, 9);
		KD_ARX(b1, b0, k5, k6, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k1 + t2, k2 + 4, 37);
		KD_ARX(b13, b12, k16, k0 + t1, 22);
		KD_ARX(b11, b10, k14, k15, 17);
		KD_ARX(b9, b8, k12, k13, 8);
		KD_ARX(b7, b6, k10, k11, 47);
		KD_ARX(b5, b4, k8, k9, 8);
		KD_ARX(b3, b2, k6, k7, 13);
		KD_ARX(b1, b0, k4, k5, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k0 + t1, k1 + 3, 30);
		KD_ARX(b13, b12, k15, k16 + t0, 44);
		KD_ARX(b11, b10, k13, k14, 47);
		KD_ARX(b9, b8, k11, k12, 12);
		KD_ARX(b7, b6, k9, k10, 31);
		KD_ARX(b5, b4, k7, k8, 37);
		KD_ARX(b3, b2, k5, k6, 9);
		KD_ARX(b1, b0, k3, k4, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k16 + t0, k0 + 2, 37);
		KD_ARX(b13, b12, k14, k15 + t2, 22);
		KD_ARX(b11, b10, k12, k13, 17);
		KD_ARX(b9, b8, k10, k11, 8);
		KD_ARX(b7, b6, k8, k9, 47);
		KD_ARX(b5, b4, k6, k7, 8);
		KD_ARX(b3, b2, k4, k5, 13);
		KD_ARX(b1, b0, k2, k3, 24);


		BD_ARX(b7, b12, 20);
		BD_ARX(b3, b10, 37);
		BD_ARX(b5, b8, 31);
		BD_ARX(b1, b14, 23);
		BD_ARX(b9, b4, 52);
		BD_ARX(b13, b6, 35);
		BD_ARX(b11, b2, 48);
		BD_ARX(b15, b0, 9);
		BD_ARX(b9, b10, 25);
		BD_ARX(b11, b8, 44);
		BD_ARX(b13, b14, 42);
		BD_ARX(b15, b12, 19);
		BD_ARX(b1, b6, 46);
		BD_ARX(b3, b4, 47);
		BD_ARX(b5, b2, 44);
		BD_ARX(b7, b0, 31);
		BD_ARX(b1, b8, 41);
		BD_ARX(b5, b14, 42);
		BD_ARX(b3, b12, 53);
		BD_ARX(b7, b10, 4);
		BD_ARX(b15, b4, 51);
		BD_ARX(b11, b6, 56);
		BD_ARX(b13, b2, 34);
		BD_ARX(b9, b0, 16);
		KD_ARX(b15, b14, k15 + t2, k16 + 1, 30);
		KD_ARX(b13, b12, k13, k14 + t1, 44);
		KD_ARX(b11, b10, k11, k12, 47);
		KD_ARX(b9, b8, k9, k10, 12);
		KD_ARX(b7, b6, k7, k8, 31);
		KD_ARX(b5, b4, k5, k6, 37);
		KD_ARX(b3, b2, k3, k4, 9);
		KD_ARX(b1, b0, k1, k2, 41);


		BD_ARX(b7, b12, 25);
		BD_ARX(b3, b10, 16);
		BD_ARX(b5, b8, 28);
		BD_ARX(b1, b14, 47);
		BD_ARX(b9, b4, 41);
		BD_ARX(b13, b6, 48);
		BD_ARX(b11, b2, 20);
		BD_ARX(b15, b0, 5);
		BD_ARX(b9, b10, 17);
		BD_ARX(b11, b8, 59);
		BD_ARX(b13, b14, 41);
		BD_ARX(b15, b12, 34);
		BD_ARX(b1, b6, 13);
		BD_ARX(b3, b4, 51);
		BD_ARX(b5, b2, 4);
		BD_ARX(b7, b0, 33);
		BD_ARX(b1, b8, 52);
		BD_ARX(b5, b14, 23);
		BD_ARX(b3, b12, 18);
		BD_ARX(b7, b10, 49);
		BD_ARX(b15, b4, 55);
		BD_ARX(b11, b6, 10);
		BD_ARX(b13, b2, 19);
		BD_ARX(b9, b0, 38);
		KD_ARX(b15, b14, k14 + t1, k15, 37);
		KD_ARX(b13, b12, k12, k13 + t0, 22);
		KD_ARX(b11, b10, k10, k11, 17);
		KD_ARX(b9, b8, k8, k9, 8);
		KD_ARX(b7, b6, k6, k7, 47);
		KD_ARX(b5, b4, k4, k5, 8);
		KD_ARX(b3, b2, k2, k3, 13);
		KD_ARX(b1, b0, k0, k1, 24);

#ifdef TF_FAST
		output[15] = b15;
		output[14] = b14;
		output[13] = b13;
		output[12] = b12;
		output[11] = b11;
		output[10] = b10;
		output[9] = b9;
		output[8] = b8;
		output[7] = b7;
		output[6] = b6;
		output[5] = b5;
		output[4] = b4;
		output[3] = b3;
		output[2] = b2;
		output[1] = b1;
		output[0] = b0;
#endif
}
#endif
