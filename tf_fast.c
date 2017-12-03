#include <stdint.h>
#include <string.h>
#include "tf1024.h"

/* switchboards */
enum tf_esched {
	TFS_KE01 = 24, TFS_KE02 = 13, TFS_KE03 = 8,  TFS_KE04 = 47,
	TFS_KE05 = 8,  TFS_KE06 = 17, TFS_KE07 = 22, TFS_KE08 = 37,
	TFS_KE09 = 41, TFS_KE10 = 9,  TFS_KE11 = 37, TFS_KE12 = 31,
	TFS_KE13 = 12, TFS_KE14 = 47, TFS_KE15 = 44, TFS_KE16 = 30,

	TFS_BE01 = 38, TFS_BE02 = 19, TFS_BE03 = 10, TFS_BE04 = 55,
	TFS_BE05 = 49, TFS_BE06 = 18, TFS_BE07 = 23, TFS_BE08 = 52,
	TFS_BE09 = 33, TFS_BE10 = 4,  TFS_BE11 = 51, TFS_BE12 = 13,
	TFS_BE13 = 34, TFS_BE14 = 41, TFS_BE15 = 59, TFS_BE16 = 17,
	TFS_BE17 = 5,  TFS_BE18 = 20, TFS_BE19 = 48, TFS_BE20 = 41,
	TFS_BE21 = 47, TFS_BE22 = 28, TFS_BE23 = 16, TFS_BE24 = 25,
	TFS_BE25 = 16, TFS_BE26 = 34, TFS_BE27 = 56, TFS_BE28 = 51,
	TFS_BE29 = 4,  TFS_BE30 = 53, TFS_BE31 = 42, TFS_BE32 = 41,
	TFS_BE33 = 31, TFS_BE34 = 44, TFS_BE35 = 47, TFS_BE36 = 46,
	TFS_BE37 = 19, TFS_BE38 = 42, TFS_BE39 = 44, TFS_BE40 = 25,
	TFS_BE41 = 9,  TFS_BE42 = 48, TFS_BE43 = 35, TFS_BE44 = 52,
	TFS_BE45 = 23, TFS_BE46 = 31, TFS_BE47 = 37, TFS_BE48 = 20,
};

enum tf_dsched {
	TFS_KD01 = TFS_KE08, TFS_KD02 = TFS_KE07,
	TFS_KD03 = TFS_KE06, TFS_KD04 = TFS_KE05,
	TFS_KD05 = TFS_KE04, TFS_KD06 = TFS_KE03,
	TFS_KD07 = TFS_KE02, TFS_KD08 = TFS_KE01,
	TFS_KD09 = TFS_KE16, TFS_KD10 = TFS_KE15,
	TFS_KD11 = TFS_KE14, TFS_KD12 = TFS_KE13,
	TFS_KD13 = TFS_KE12, TFS_KD14 = TFS_KE11,
	TFS_KD15 = TFS_KE10, TFS_KD16 = TFS_KE09,

	TFS_BD01 = TFS_BE24, TFS_BD02 = TFS_BE23,
	TFS_BD03 = TFS_BE22, TFS_BD04 = TFS_BE21,
	TFS_BD05 = TFS_BE20, TFS_BD06 = TFS_BE19,
	TFS_BD07 = TFS_BE18, TFS_BD08 = TFS_BE17,
	TFS_BD09 = TFS_BE16, TFS_BD10 = TFS_BE15,
	TFS_BD11 = TFS_BE14, TFS_BD12 = TFS_BE13,
	TFS_BD13 = TFS_BE12, TFS_BD14 = TFS_BE11,
	TFS_BD15 = TFS_BE10, TFS_BD16 = TFS_BE09,
	TFS_BD17 = TFS_BE08, TFS_BD18 = TFS_BE07,
	TFS_BD19 = TFS_BE06, TFS_BD20 = TFS_BE05,
	TFS_BD21 = TFS_BE04, TFS_BD22 = TFS_BE03,
	TFS_BD23 = TFS_BE02, TFS_BD24 = TFS_BE01,
	TFS_BD25 = TFS_BE48, TFS_BD26 = TFS_BE47,
	TFS_BD27 = TFS_BE46, TFS_BD28 = TFS_BE45,
	TFS_BD29 = TFS_BE44, TFS_BD30 = TFS_BE43,
	TFS_BD31 = TFS_BE42, TFS_BD32 = TFS_BE41,
	TFS_BD33 = TFS_BE40, TFS_BD34 = TFS_BE39,
	TFS_BD35 = TFS_BE38, TFS_BD36 = TFS_BE37,
	TFS_BD37 = TFS_BE36, TFS_BD38 = TFS_BE35,
	TFS_BD39 = TFS_BE34, TFS_BD40 = TFS_BE33,
	TFS_BD41 = TFS_BE32, TFS_BD42 = TFS_BE31,
	TFS_BD43 = TFS_BE30, TFS_BD44 = TFS_BE29,
	TFS_BD45 = TFS_BE28, TFS_BD46 = TFS_BE27,
	TFS_BD47 = TFS_BE26, TFS_BD48 = TFS_BE25,
};

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

#define KE_ARX(x, xx, k, kk, s)						\
	do {								\
		x += k;		 					\
		xx += x + kk;						\
		x = ((x << s) | (x >> (TF_UNIT_BITS - s))) ^ xx;	\
	} while (0)

#define BE_ARX(x, xx, s)						\
	do {								\
		x += xx;						\
		xx = ((xx << s) | (xx >> (TF_UNIT_BITS - s))) ^ x;	\
	} while (0)

#define KD_ARX(x, xx, k, kk, s)						\
	do {								\
		x ^= xx;						\
		x = (x >> s) | (x << (TF_UNIT_BITS - s));		\
		xx -= x + k;						\
		x -= kk;						\
	} while (0)

#define BD_ARX(x, xx, s)						\
	do {								\
		x ^= xx;						\
		x = (x >> s) | (x << (TF_UNIT_BITS - s));		\
		xx -= x;						\
	} while (0)

void tfc1024_encrypt_blk(tfc1024_ctx *ctx, const TF_UNIT_TYPE *input, TF_UNIT_TYPE *output)
{
#ifdef TF_FAST
	TF_UNIT_TYPE b0 = input[0], b1 = input[1],
		b2 = input[2], b3 = input[3],
		b4 = input[4], b5 = input[5],
		b6 = input[6], b7 = input[7],
		b8 = input[8], b9 = input[9],
		b10 = input[10], b11 = input[11],
		b12 = input[12], b13 = input[13],
		b14 = input[14], b15 = input[15];
	TF_UNIT_TYPE k0 = ctx->K[0], k1 = ctx->K[1],
		k2 = ctx->K[2], k3 = ctx->K[3],
		k4 = ctx->K[4], k5 = ctx->K[5],
		k6 = ctx->K[6], k7 = ctx->K[7],
		k8 = ctx->K[8], k9 = ctx->K[9],
		k10 = ctx->K[10], k11 = ctx->K[11],
		k12 = ctx->K[12], k13 = ctx->K[13],
		k14 = ctx->K[14], k15 = ctx->K[15],
		k16 = ctx->K[16];
	TF_UNIT_TYPE t0 = ctx->T[0], t1 = ctx->T[1],
		t2 = ctx->T[2];
#else
		memcpy(output, input, TF_BLOCK_SIZE);
#endif

		KE_ARX(b1, b0, k1, k0, TFS_KE01);
		KE_ARX(b3, b2, k3, k2, TFS_KE02);
		KE_ARX(b5, b4, k5, k4, TFS_KE03);
		KE_ARX(b7, b6, k7, k6, TFS_KE04);
		KE_ARX(b9, b8, k9, k8, TFS_KE05);
		KE_ARX(b11, b10, k11, k10, TFS_KE06);
		KE_ARX(b13, b12, k13 + t0, k12, TFS_KE07);
		KE_ARX(b15, b14, k15, k14 + t1, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k2, k1, TFS_KE09);
		KE_ARX(b3, b2, k4, k3, TFS_KE10);
		KE_ARX(b5, b4, k6, k5, TFS_KE11);
		KE_ARX(b7, b6, k8, k7, TFS_KE12);
		KE_ARX(b9, b8, k10, k9, TFS_KE13);
		KE_ARX(b11, b10, k12, k11, TFS_KE14);
		KE_ARX(b13, b12, k14 + t1, k13, TFS_KE15);
		KE_ARX(b15, b14, k16 + 1, k15 + t2, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k3, k2, TFS_KE01);
		KE_ARX(b3, b2, k5, k4, TFS_KE02);
		KE_ARX(b5, b4, k7, k6, TFS_KE03);
		KE_ARX(b7, b6, k9, k8, TFS_KE04);
		KE_ARX(b9, b8, k11, k10, TFS_KE05);
		KE_ARX(b11, b10, k13, k12, TFS_KE06);
		KE_ARX(b13, b12, k15 + t2, k14, TFS_KE07);
		KE_ARX(b15, b14, k0 + 2, k16 + t0, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k4, k3, TFS_KE09);
		KE_ARX(b3, b2, k6, k5, TFS_KE10);
		KE_ARX(b5, b4, k8, k7, TFS_KE11);
		KE_ARX(b7, b6, k10, k9, TFS_KE12);
		KE_ARX(b9, b8, k12, k11, TFS_KE13);
		KE_ARX(b11, b10, k14, k13, TFS_KE14);
		KE_ARX(b13, b12, k16 + t0, k15, TFS_KE15);
		KE_ARX(b15, b14, k1 + 3, k0 + t1, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k5, k4, TFS_KE01);
		KE_ARX(b3, b2, k7, k6, TFS_KE02);
		KE_ARX(b5, b4, k9, k8, TFS_KE03);
		KE_ARX(b7, b6, k11, k10, TFS_KE04);
		KE_ARX(b9, b8, k13, k12, TFS_KE05);
		KE_ARX(b11, b10, k15, k14, TFS_KE06);
		KE_ARX(b13, b12, k0 + t1, k16, TFS_KE07);
		KE_ARX(b15, b14, k2 + 4, k1 + t2, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k6, k5, TFS_KE09);
		KE_ARX(b3, b2, k8, k7, TFS_KE10);
		KE_ARX(b5, b4, k10, k9, TFS_KE11);
		KE_ARX(b7, b6, k12, k11, TFS_KE12);
		KE_ARX(b9, b8, k14, k13, TFS_KE13);
		KE_ARX(b11, b10, k16, k15, TFS_KE14);
		KE_ARX(b13, b12, k1 + t2, k0, TFS_KE15);
		KE_ARX(b15, b14, k3 + 5, k2 + t0, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k7, k6, TFS_KE01);
		KE_ARX(b3, b2, k9, k8, TFS_KE02);
		KE_ARX(b5, b4, k11, k10, TFS_KE03);
		KE_ARX(b7, b6, k13, k12, TFS_KE04);
		KE_ARX(b9, b8, k15, k14, TFS_KE05);
		KE_ARX(b11, b10, k0, k16, TFS_KE06);
		KE_ARX(b13, b12, k2 + t0, k1, TFS_KE07);
		KE_ARX(b15, b14, k4 + 6, k3 + t1, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k8, k7, TFS_KE09);
		KE_ARX(b3, b2, k10, k9, TFS_KE10);
		KE_ARX(b5, b4, k12, k11, TFS_KE11);
		KE_ARX(b7, b6, k14, k13, TFS_KE12);
		KE_ARX(b9, b8, k16, k15, TFS_KE13);
		KE_ARX(b11, b10, k1, k0, TFS_KE14);
		KE_ARX(b13, b12, k3 + t1, k2, TFS_KE15);
		KE_ARX(b15, b14, k5 + 7, k4 + t2, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k9, k8, TFS_KE01);
		KE_ARX(b3, b2, k11, k10, TFS_KE02);
		KE_ARX(b5, b4, k13, k12, TFS_KE03);
		KE_ARX(b7, b6, k15, k14, TFS_KE04);
		KE_ARX(b9, b8, k0, k16, TFS_KE05);
		KE_ARX(b11, b10, k2, k1, TFS_KE06);
		KE_ARX(b13, b12, k4 + t2, k3, TFS_KE07);
		KE_ARX(b15, b14, k6 + 8, k5 + t0, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k10, k9, TFS_KE09);
		KE_ARX(b3, b2, k12, k11, TFS_KE10);
		KE_ARX(b5, b4, k14, k13, TFS_KE11);
		KE_ARX(b7, b6, k16, k15, TFS_KE12);
		KE_ARX(b9, b8, k1, k0, TFS_KE13);
		KE_ARX(b11, b10, k3, k2, TFS_KE14);
		KE_ARX(b13, b12, k5 + t0, k4, TFS_KE15);
		KE_ARX(b15, b14, k7 + 9, k6 + t1, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k11, k10, TFS_KE01);
		KE_ARX(b3, b2, k13, k12, TFS_KE02);
		KE_ARX(b5, b4, k15, k14, TFS_KE03);
		KE_ARX(b7, b6, k0, k16, TFS_KE04);
		KE_ARX(b9, b8, k2, k1, TFS_KE05);
		KE_ARX(b11, b10, k4, k3, TFS_KE06);
		KE_ARX(b13, b12, k6 + t1, k5, TFS_KE07);
		KE_ARX(b15, b14, k8 + 10, k7 + t2, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k12, k11, TFS_KE09);
		KE_ARX(b3, b2, k14, k13, TFS_KE10);
		KE_ARX(b5, b4, k16, k15, TFS_KE11);
		KE_ARX(b7, b6, k1, k0, TFS_KE12);
		KE_ARX(b9, b8, k3, k2, TFS_KE13);
		KE_ARX(b11, b10, k5, k4, TFS_KE14);
		KE_ARX(b13, b12, k7 + t2, k6, TFS_KE15);
		KE_ARX(b15, b14, k9 + 11, k8 + t0, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k13, k12, TFS_KE01);
		KE_ARX(b3, b2, k15, k14, TFS_KE02);
		KE_ARX(b5, b4, k0, k16, TFS_KE03);
		KE_ARX(b7, b6, k2, k1, TFS_KE04);
		KE_ARX(b9, b8, k4, k3, TFS_KE05);
		KE_ARX(b11, b10, k6, k5, TFS_KE06);
		KE_ARX(b13, b12, k8 + t0, k7, TFS_KE07);
		KE_ARX(b15, b14, k10 + 12, k9 + t1, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k14, k13, TFS_KE09);
		KE_ARX(b3, b2, k16, k15, TFS_KE10);
		KE_ARX(b5, b4, k1, k0, TFS_KE11);
		KE_ARX(b7, b6, k3, k2, TFS_KE12);
		KE_ARX(b9, b8, k5, k4, TFS_KE13);
		KE_ARX(b11, b10, k7, k6, TFS_KE14);
		KE_ARX(b13, b12, k9 + t1, k8, TFS_KE15);
		KE_ARX(b15, b14, k11 + 13, k10 + t2, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k15, k14, TFS_KE01);
		KE_ARX(b3, b2, k0, k16, TFS_KE02);
		KE_ARX(b5, b4, k2, k1, TFS_KE03);
		KE_ARX(b7, b6, k4, k3, TFS_KE04);
		KE_ARX(b9, b8, k6, k5, TFS_KE05);
		KE_ARX(b11, b10, k8, k7, TFS_KE06);
		KE_ARX(b13, b12, k10 + t2, k9, TFS_KE07);
		KE_ARX(b15, b14, k12 + 14, k11 + t0, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k16, k15, TFS_KE09);
		KE_ARX(b3, b2, k1, k0, TFS_KE10);
		KE_ARX(b5, b4, k3, k2, TFS_KE11);
		KE_ARX(b7, b6, k5, k4, TFS_KE12);
		KE_ARX(b9, b8, k7, k6, TFS_KE13);
		KE_ARX(b11, b10, k9, k8, TFS_KE14);
		KE_ARX(b13, b12, k11 + t0, k10, TFS_KE15);
		KE_ARX(b15, b14, k13 + 15, k12 + t1, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k0, k16, TFS_KE01);
		KE_ARX(b3, b2, k2, k1, TFS_KE02);
		KE_ARX(b5, b4, k4, k3, TFS_KE03);
		KE_ARX(b7, b6, k6, k5, TFS_KE04);
		KE_ARX(b9, b8, k8, k7, TFS_KE05);
		KE_ARX(b11, b10, k10, k9, TFS_KE06);
		KE_ARX(b13, b12, k12 + t1, k11, TFS_KE07);
		KE_ARX(b15, b14, k14 + 16, k13 + t2, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k1, k0, TFS_KE09);
		KE_ARX(b3, b2, k3, k2, TFS_KE10);
		KE_ARX(b5, b4, k5, k4, TFS_KE11);
		KE_ARX(b7, b6, k7, k6, TFS_KE12);
		KE_ARX(b9, b8, k9, k8, TFS_KE13);
		KE_ARX(b11, b10, k11, k10, TFS_KE14);
		KE_ARX(b13, b12, k13 + t2, k12, TFS_KE15);
		KE_ARX(b15, b14, k15 + 17, k14 + t0, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);


		KE_ARX(b1, b0, k2, k1, TFS_KE01);
		KE_ARX(b3, b2, k4, k3, TFS_KE02);
		KE_ARX(b5, b4, k6, k5, TFS_KE03);
		KE_ARX(b7, b6, k8, k7, TFS_KE04);
		KE_ARX(b9, b8, k10, k9, TFS_KE05);
		KE_ARX(b11, b10, k12, k11, TFS_KE06);
		KE_ARX(b13, b12, k14 + t0, k13, TFS_KE07);
		KE_ARX(b15, b14, k16 + 18, k15 + t1, TFS_KE08);
		BE_ARX(b0, b9, TFS_BE01);
		BE_ARX(b2, b13, TFS_BE02);
		BE_ARX(b6, b11, TFS_BE03);
		BE_ARX(b4, b15, TFS_BE04);
		BE_ARX(b10, b7, TFS_BE05);
		BE_ARX(b12, b3, TFS_BE06);
		BE_ARX(b14, b5, TFS_BE07);
		BE_ARX(b8, b1, TFS_BE08);
		BE_ARX(b0, b7, TFS_BE09);
		BE_ARX(b2, b5, TFS_BE10);
		BE_ARX(b4, b3, TFS_BE11);
		BE_ARX(b6, b1, TFS_BE12);
		BE_ARX(b12, b15, TFS_BE13);
		BE_ARX(b14, b13, TFS_BE14);
		BE_ARX(b8, b11, TFS_BE15);
		BE_ARX(b10, b9, TFS_BE16);
		BE_ARX(b0, b15, TFS_BE17);
		BE_ARX(b2, b11, TFS_BE18);
		BE_ARX(b6, b13, TFS_BE19);
		BE_ARX(b4, b9, TFS_BE20);
		BE_ARX(b14, b1, TFS_BE21);
		BE_ARX(b8, b5, TFS_BE22);
		BE_ARX(b10, b3, TFS_BE23);
		BE_ARX(b12, b7, TFS_BE24);


		KE_ARX(b1, b0, k3, k2, TFS_KE09);
		KE_ARX(b3, b2, k5, k4, TFS_KE10);
		KE_ARX(b5, b4, k7, k6, TFS_KE11);
		KE_ARX(b7, b6, k9, k8, TFS_KE12);
		KE_ARX(b9, b8, k11, k10, TFS_KE13);
		KE_ARX(b11, b10, k13, k12, TFS_KE14);
		KE_ARX(b13, b12, k15 + t1, k14, TFS_KE15);
		KE_ARX(b15, b14, k0 + 19, k16 + t2, TFS_KE16);
		BE_ARX(b0, b9, TFS_BE25);
		BE_ARX(b2, b13, TFS_BE26);
		BE_ARX(b6, b11, TFS_BE27);
		BE_ARX(b4, b15, TFS_BE28);
		BE_ARX(b10, b7, TFS_BE29);
		BE_ARX(b12, b3, TFS_BE30);
		BE_ARX(b14, b5, TFS_BE31);
		BE_ARX(b8, b1, TFS_BE32);
		BE_ARX(b0, b7, TFS_BE33);
		BE_ARX(b2, b5, TFS_BE34);
		BE_ARX(b4, b3, TFS_BE35);
		BE_ARX(b6, b1, TFS_BE36);
		BE_ARX(b12, b15, TFS_BE37);
		BE_ARX(b14, b13, TFS_BE38);
		BE_ARX(b8, b11, TFS_BE39);
		BE_ARX(b10, b9, TFS_BE40);
		BE_ARX(b0, b15, TFS_BE41);
		BE_ARX(b2, b11, TFS_BE42);
		BE_ARX(b6, b13, TFS_BE43);
		BE_ARX(b4, b9, TFS_BE44);
		BE_ARX(b14, b1, TFS_BE45);
		BE_ARX(b8, b5, TFS_BE46);
		BE_ARX(b10, b3, TFS_BE47);
		BE_ARX(b12, b7, TFS_BE48);
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
void tfc1024_decrypt_blk(tfc1024_ctx *ctx, const TF_UNIT_TYPE *input, TF_UNIT_TYPE *output)
{
#ifdef TF_FAST
	TF_UNIT_TYPE b0 = input[0], b1 = input[1],
		b2 = input[2], b3 = input[3],
		b4 = input[4], b5 = input[5],
		b6 = input[6], b7 = input[7],
		b8 = input[8], b9 = input[9],
		b10 = input[10], b11 = input[11],
		b12 = input[12], b13 = input[13],
		b14 = input[14], b15 = input[15];
	TF_UNIT_TYPE k0 = ctx->K[0], k1 = ctx->K[1],
		k2 = ctx->K[2], k3 = ctx->K[3],
		k4 = ctx->K[4], k5 = ctx->K[5],
		k6 = ctx->K[6], k7 = ctx->K[7],
		k8 = ctx->K[8], k9 = ctx->K[9],
		k10 = ctx->K[10], k11 = ctx->K[11],
		k12 = ctx->K[12], k13 = ctx->K[13],
		k14 = ctx->K[14], k15 = ctx->K[15],
		k16 = ctx->K[16];
	TF_UNIT_TYPE t0 = ctx->T[0], t1 = ctx->T[1],
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


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k16 + t2, k0 + 19, TFS_KD09);
		KD_ARX(b13, b12, k14, k15 + t1, TFS_KD10);
		KD_ARX(b11, b10, k12, k13, TFS_KD11);
		KD_ARX(b9, b8, k10, k11, TFS_KD12);
		KD_ARX(b7, b6, k8, k9, TFS_KD13);
		KD_ARX(b5, b4, k6, k7, TFS_KD14);
		KD_ARX(b3, b2, k4, k5, TFS_KD15);
		KD_ARX(b1, b0, k2, k3, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k15 + t1, k16 + 18, TFS_KD01);
		KD_ARX(b13, b12, k13, k14 + t0, TFS_KD02);
		KD_ARX(b11, b10, k11, k12, TFS_KD03);
		KD_ARX(b9, b8, k9, k10, TFS_KD04);
		KD_ARX(b7, b6, k7, k8, TFS_KD05);
		KD_ARX(b5, b4, k5, k6, TFS_KD06);
		KD_ARX(b3, b2, k3, k4, TFS_KD07);
		KD_ARX(b1, b0, k1, k2, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k14 + t0, k15 + 17, TFS_KD09);
		KD_ARX(b13, b12, k12, k13 + t2, TFS_KD10);
		KD_ARX(b11, b10, k10, k11, TFS_KD11);
		KD_ARX(b9, b8, k8, k9, TFS_KD12);
		KD_ARX(b7, b6, k6, k7, TFS_KD13);
		KD_ARX(b5, b4, k4, k5, TFS_KD14);
		KD_ARX(b3, b2, k2, k3, TFS_KD15);
		KD_ARX(b1, b0, k0, k1, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k13 + t2, k14 + 16, TFS_KD01);
		KD_ARX(b13, b12, k11, k12 + t1, TFS_KD02);
		KD_ARX(b11, b10, k9, k10, TFS_KD03);
		KD_ARX(b9, b8, k7, k8, TFS_KD04);
		KD_ARX(b7, b6, k5, k6, TFS_KD05);
		KD_ARX(b5, b4, k3, k4, TFS_KD06);
		KD_ARX(b3, b2, k1, k2, TFS_KD07);
		KD_ARX(b1, b0, k16, k0, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k12 + t1, k13 + 15, TFS_KD09);
		KD_ARX(b13, b12, k10, k11 + t0, TFS_KD10);
		KD_ARX(b11, b10, k8, k9, TFS_KD11);
		KD_ARX(b9, b8, k6, k7, TFS_KD12);
		KD_ARX(b7, b6, k4, k5, TFS_KD13);
		KD_ARX(b5, b4, k2, k3, TFS_KD14);
		KD_ARX(b3, b2, k0, k1, TFS_KD15);
		KD_ARX(b1, b0, k15, k16, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k11 + t0, k12 + 14, TFS_KD01);
		KD_ARX(b13, b12, k9, k10 + t2, TFS_KD02);
		KD_ARX(b11, b10, k7, k8, TFS_KD03);
		KD_ARX(b9, b8, k5, k6, TFS_KD04);
		KD_ARX(b7, b6, k3, k4, TFS_KD05);
		KD_ARX(b5, b4, k1, k2, TFS_KD06);
		KD_ARX(b3, b2, k16, k0, TFS_KD07);
		KD_ARX(b1, b0, k14, k15, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k10 + t2, k11 + 13, TFS_KD09);
		KD_ARX(b13, b12, k8, k9 + t1, TFS_KD10);
		KD_ARX(b11, b10, k6, k7, TFS_KD11);
		KD_ARX(b9, b8, k4, k5, TFS_KD12);
		KD_ARX(b7, b6, k2, k3, TFS_KD13);
		KD_ARX(b5, b4, k0, k1, TFS_KD14);
		KD_ARX(b3, b2, k15, k16, TFS_KD15);
		KD_ARX(b1, b0, k13, k14, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k9 + t1, k10 + 12, TFS_KD01);
		KD_ARX(b13, b12, k7, k8 + t0, TFS_KD02);
		KD_ARX(b11, b10, k5, k6, TFS_KD03);
		KD_ARX(b9, b8, k3, k4, TFS_KD04);
		KD_ARX(b7, b6, k1, k2, TFS_KD05);
		KD_ARX(b5, b4, k16, k0, TFS_KD06);
		KD_ARX(b3, b2, k14, k15, TFS_KD07);
		KD_ARX(b1, b0, k12, k13, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k8 + t0, k9 + 11, TFS_KD09);
		KD_ARX(b13, b12, k6, k7 + t2, TFS_KD10);
		KD_ARX(b11, b10, k4, k5, TFS_KD11);
		KD_ARX(b9, b8, k2, k3, TFS_KD12);
		KD_ARX(b7, b6, k0, k1, TFS_KD13);
		KD_ARX(b5, b4, k15, k16, TFS_KD14);
		KD_ARX(b3, b2, k13, k14, TFS_KD15);
		KD_ARX(b1, b0, k11, k12, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k7 + t2, k8 + 10, TFS_KD01);
		KD_ARX(b13, b12, k5, k6 + t1, TFS_KD02);
		KD_ARX(b11, b10, k3, k4, TFS_KD03);
		KD_ARX(b9, b8, k1, k2, TFS_KD04);
		KD_ARX(b7, b6, k16, k0, TFS_KD05);
		KD_ARX(b5, b4, k14, k15, TFS_KD06);
		KD_ARX(b3, b2, k12, k13, TFS_KD07);
		KD_ARX(b1, b0, k10, k11, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k6 + t1, k7 + 9, TFS_KD09);
		KD_ARX(b13, b12, k4, k5 + t0, TFS_KD10);
		KD_ARX(b11, b10, k2, k3, TFS_KD11);
		KD_ARX(b9, b8, k0, k1, TFS_KD12);
		KD_ARX(b7, b6, k15, k16, TFS_KD13);
		KD_ARX(b5, b4, k13, k14, TFS_KD14);
		KD_ARX(b3, b2, k11, k12, TFS_KD15);
		KD_ARX(b1, b0, k9, k10, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k5 + t0, k6 + 8, TFS_KD01);
		KD_ARX(b13, b12, k3, k4 + t2, TFS_KD02);
		KD_ARX(b11, b10, k1, k2, TFS_KD03);
		KD_ARX(b9, b8, k16, k0, TFS_KD04);
		KD_ARX(b7, b6, k14, k15, TFS_KD05);
		KD_ARX(b5, b4, k12, k13, TFS_KD06);
		KD_ARX(b3, b2, k10, k11, TFS_KD07);
		KD_ARX(b1, b0, k8, k9, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k4 + t2, k5 + 7, TFS_KD09);
		KD_ARX(b13, b12, k2, k3 + t1, TFS_KD10);
		KD_ARX(b11, b10, k0, k1, TFS_KD11);
		KD_ARX(b9, b8, k15, k16, TFS_KD12);
		KD_ARX(b7, b6, k13, k14, TFS_KD13);
		KD_ARX(b5, b4, k11, k12, TFS_KD14);
		KD_ARX(b3, b2, k9, k10, TFS_KD15);
		KD_ARX(b1, b0, k7, k8, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k3 + t1, k4 + 6, TFS_KD01);
		KD_ARX(b13, b12, k1, k2 + t0, TFS_KD02);
		KD_ARX(b11, b10, k16, k0, TFS_KD03);
		KD_ARX(b9, b8, k14, k15, TFS_KD04);
		KD_ARX(b7, b6, k12, k13, TFS_KD05);
		KD_ARX(b5, b4, k10, k11, TFS_KD06);
		KD_ARX(b3, b2, k8, k9, TFS_KD07);
		KD_ARX(b1, b0, k6, k7, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k2 + t0, k3 + 5, TFS_KD09);
		KD_ARX(b13, b12, k0, k1 + t2, TFS_KD10);
		KD_ARX(b11, b10, k15, k16, TFS_KD11);
		KD_ARX(b9, b8, k13, k14, TFS_KD12);
		KD_ARX(b7, b6, k11, k12, TFS_KD13);
		KD_ARX(b5, b4, k9, k10, TFS_KD14);
		KD_ARX(b3, b2, k7, k8, TFS_KD15);
		KD_ARX(b1, b0, k5, k6, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k1 + t2, k2 + 4, TFS_KD01);
		KD_ARX(b13, b12, k16, k0 + t1, TFS_KD02);
		KD_ARX(b11, b10, k14, k15, TFS_KD03);
		KD_ARX(b9, b8, k12, k13, TFS_KD04);
		KD_ARX(b7, b6, k10, k11, TFS_KD05);
		KD_ARX(b5, b4, k8, k9, TFS_KD06);
		KD_ARX(b3, b2, k6, k7, TFS_KD07);
		KD_ARX(b1, b0, k4, k5, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k0 + t1, k1 + 3, TFS_KD09);
		KD_ARX(b13, b12, k15, k16 + t0, TFS_KD10);
		KD_ARX(b11, b10, k13, k14, TFS_KD11);
		KD_ARX(b9, b8, k11, k12, TFS_KD12);
		KD_ARX(b7, b6, k9, k10, TFS_KD13);
		KD_ARX(b5, b4, k7, k8, TFS_KD14);
		KD_ARX(b3, b2, k5, k6, TFS_KD15);
		KD_ARX(b1, b0, k3, k4, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k16 + t0, k0 + 2, TFS_KD01);
		KD_ARX(b13, b12, k14, k15 + t2, TFS_KD02);
		KD_ARX(b11, b10, k12, k13, TFS_KD03);
		KD_ARX(b9, b8, k10, k11, TFS_KD04);
		KD_ARX(b7, b6, k8, k9, TFS_KD05);
		KD_ARX(b5, b4, k6, k7, TFS_KD06);
		KD_ARX(b3, b2, k4, k5, TFS_KD07);
		KD_ARX(b1, b0, k2, k3, TFS_KD08);


		BD_ARX(b7, b12, TFS_BD25);
		BD_ARX(b3, b10, TFS_BD26);
		BD_ARX(b5, b8, TFS_BD27);
		BD_ARX(b1, b14, TFS_BD28);
		BD_ARX(b9, b4, TFS_BD29);
		BD_ARX(b13, b6, TFS_BD30);
		BD_ARX(b11, b2, TFS_BD31);
		BD_ARX(b15, b0, TFS_BD32);
		BD_ARX(b9, b10, TFS_BD33);
		BD_ARX(b11, b8, TFS_BD34);
		BD_ARX(b13, b14, TFS_BD35);
		BD_ARX(b15, b12, TFS_BD36);
		BD_ARX(b1, b6, TFS_BD37);
		BD_ARX(b3, b4, TFS_BD38);
		BD_ARX(b5, b2, TFS_BD39);
		BD_ARX(b7, b0, TFS_BD40);
		BD_ARX(b1, b8, TFS_BD41);
		BD_ARX(b5, b14, TFS_BD42);
		BD_ARX(b3, b12, TFS_BD43);
		BD_ARX(b7, b10, TFS_BD44);
		BD_ARX(b15, b4, TFS_BD45);
		BD_ARX(b11, b6, TFS_BD46);
		BD_ARX(b13, b2, TFS_BD47);
		BD_ARX(b9, b0, TFS_BD48);
		KD_ARX(b15, b14, k15 + t2, k16 + 1, TFS_KD09);
		KD_ARX(b13, b12, k13, k14 + t1, TFS_KD10);
		KD_ARX(b11, b10, k11, k12, TFS_KD11);
		KD_ARX(b9, b8, k9, k10, TFS_KD12);
		KD_ARX(b7, b6, k7, k8, TFS_KD13);
		KD_ARX(b5, b4, k5, k6, TFS_KD14);
		KD_ARX(b3, b2, k3, k4, TFS_KD15);
		KD_ARX(b1, b0, k1, k2, TFS_KD16);


		BD_ARX(b7, b12, TFS_BD01);
		BD_ARX(b3, b10, TFS_BD02);
		BD_ARX(b5, b8, TFS_BD03);
		BD_ARX(b1, b14, TFS_BD04);
		BD_ARX(b9, b4, TFS_BD05);
		BD_ARX(b13, b6, TFS_BD06);
		BD_ARX(b11, b2, TFS_BD07);
		BD_ARX(b15, b0, TFS_BD08);
		BD_ARX(b9, b10, TFS_BD09);
		BD_ARX(b11, b8, TFS_BD10);
		BD_ARX(b13, b14, TFS_BD11);
		BD_ARX(b15, b12, TFS_BD12);
		BD_ARX(b1, b6, TFS_BD13);
		BD_ARX(b3, b4, TFS_BD14);
		BD_ARX(b5, b2, TFS_BD15);
		BD_ARX(b7, b0, TFS_BD16);
		BD_ARX(b1, b8, TFS_BD17);
		BD_ARX(b5, b14, TFS_BD18);
		BD_ARX(b3, b12, TFS_BD19);
		BD_ARX(b7, b10, TFS_BD20);
		BD_ARX(b15, b4, TFS_BD21);
		BD_ARX(b11, b6, TFS_BD22);
		BD_ARX(b13, b2, TFS_BD23);
		BD_ARX(b9, b0, TFS_BD24);
		KD_ARX(b15, b14, k14 + t1, k15, TFS_KD01);
		KD_ARX(b13, b12, k12, k13 + t0, TFS_KD02);
		KD_ARX(b11, b10, k10, k11, TFS_KD03);
		KD_ARX(b9, b8, k8, k9, TFS_KD04);
		KD_ARX(b7, b6, k6, k7, TFS_KD05);
		KD_ARX(b5, b4, k4, k5, TFS_KD06);
		KD_ARX(b3, b2, k2, k3, TFS_KD07);
		KD_ARX(b1, b0, k0, k1, TFS_KD08);

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
