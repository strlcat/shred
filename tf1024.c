/*
 * Embeddable skein and threefish implementation, 1024 bits only
 */

#include <stdint.h>
#include <string.h>
#include <endian.h>
#include "tf1024.h"

static inline void ctr_inc(uint64_t *x, size_t l)
{
	size_t i;

	for (i = 0; i < l; i++) {
		x[i] = ((x[i] + (uint64_t)1) & ((uint64_t)~0));
		if (x[i]) break;
	}
}

static inline void ctr_add(uint64_t *x, const uint64_t *y, size_t l)
{
	size_t i, f = 0;
	uint64_t t;

	for (i = 0; i < l; i++) {
		t = x[i];
		x[i] += y[i]; x[i] &= ((uint64_t)~0);
		if (x[i] < t) {
_again:			f++;
			t = x[f-i];
			x[f-i]++;
			if (x[f-i] < t) goto _again;
			else f = 0;
		}
	}
}

static inline void data_to_le64(void *p, size_t l)
{
	size_t idx;
	uint64_t *P = (uint64_t *)p;
	uint64_t t;

	for (idx = 0; idx < (l/sizeof(uint64_t)); idx++) {
		t = htole64(P[idx]);
		P[idx] = t;
	}
}

#define THREEFISH_PARITY 0x1bd11bdaa9fc1a22ULL

static void tfs1024_init(tfs1024_ctx *ctx)
{
	size_t i;

	ctx->K[tf_units(ctx->K) - 1] = THREEFISH_PARITY;
	for (i = 0; i < tf_units(ctx->K) - 1; i++)
		ctx->K[tf_units(ctx->K)-1] ^= ctx->K[i];

	ctx->T[2] = ctx->T[0] ^ ctx->T[1];
}

#ifdef TF_FAST
#include "fastfish.h"
#else
static const uint8_t sched1024[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	0, 9, 2, 13, 6, 11, 4, 15, 10, 7, 12, 3, 14, 5, 8, 1,
	0, 7, 2, 5, 4, 3, 6, 1, 12, 15, 14, 13, 8, 11, 10, 9,
	0, 15, 2, 11, 6, 13, 4, 9, 14, 1, 8, 5, 10, 3, 12, 7
};

static const uint8_t rot1024[] = {
	24, 13, 8, 47, 8, 17, 22, 37, 38, 19, 10, 55, 49, 18, 23, 52,
	33, 4, 51, 13, 34, 41, 59, 17, 5, 20, 48, 41, 47, 28, 16, 25,
	41, 9, 37, 31, 12, 47, 44, 30, 16, 34, 56, 51, 4, 53, 42, 41,
	31, 44, 47, 46, 19, 42, 44, 25, 9, 48, 35, 52, 23, 31, 37, 20
};

static void tf1024_encrypt_blk(tfs1024_ctx *ctx, const uint64_t *in, uint64_t *out)
{
	size_t i, r, s, a, b;

	for (i = 0; i < TF_NR_UNITS; i++)
		out[i] = ctx->K[i] + in[i];
	out[13] += ctx->T[0];
	out[14] += ctx->T[1];

	for (r = 1, s = 0; r <= 20; r++, s ^= tf_units(rot1024)/2) {
		for (i = 0; i < tf_units(sched1024)/2; i++) {
			a = sched1024[i*2];
			b = sched1024[i*2+1];

			out[a] += out[b];
			out[b] = (out[b] << rot1024[i+s]) | (out[b] >> (64 - rot1024[i+s]));
			out[b] ^= out[a];
		}

		for (i = 0; i < TF_NR_UNITS; i++)
			out[i] += ctx->K[(r+i) % tf_units(ctx->K)];
		out[13] += ctx->T[r % tf_units(ctx->T)];
		out[14] += ctx->T[(r+1) % tf_units(ctx->T)];
		out[15] += r;
	}
}
#endif /* !TF_FAST */

#ifdef TF_NEED_THREEFISH
void tf1024_init(tf1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(tf1024_ctx));
}

void tf1024_done(tf1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(tf1024_ctx));
}

void tf1024_set_key(tf1024_ctx *ctx, const void *key, size_t klen)
{
	uint64_t parity = THREEFISH_PARITY;
	int i;

	if (klen > TF_KEY_SIZE) return;

	memcpy(ctx->tfs.K, key, klen);
	memset((uint8_t *)ctx->tfs.K+klen, 0, TF_KEY_SIZE-klen);
	data_to_le64(ctx->tfs.K, sizeof(ctx->tfs.K));

	for (i = 0; i < TF_NR_UNITS; i++) parity ^= ctx->tfs.K[i];
	ctx->tfs.K[i] = parity;
}

void tf1024_set_tweak(tf1024_ctx *ctx, const void *tweak)
{
	const uint64_t *tw = tweak;

	ctx->tfs.T[0] = tw[0];
	ctx->tfs.T[1] = tw[1];
	data_to_le64(ctx->tfs.T, sizeof(ctx->tfs.T));

	ctx->tfs.T[2] = ctx->tfs.T[0] ^ ctx->tfs.T[1];
}

void tf1024_start_counter(tf1024_ctx *ctx, const void *ctr)
{
#ifdef TF_NEED_CTR_BACKUP
	memcpy(ctx->ictr, ctr, sizeof(ctx->ictr));
#endif
	memcpy(ctx->ctr, ctr, sizeof(ctx->ctr));

#ifdef TF_NEED_CTR_BACKUP
	data_to_le64(ctx->ictr, sizeof(ctx->ictr));
#endif
	data_to_le64(ctx->ctr, sizeof(ctx->ctr));
}

void tf1024_rewind_counter(tf1024_ctx *ctx, const void *newctr, size_t ctrsz)
{
#ifdef TF_NEED_CTR_BACKUP
	memcpy(ctx->ctr, ctx->ictr, sizeof(ctx->ctr));
#endif
	if (newctr && ctrsz) ctr_add(ctx->ctr, newctr, ctrsz);
}

/* CTR mode threefish */
void tf1024_crypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst)
{
	const uint8_t *usrc = src;
	uint8_t *udst = dst;
	uint64_t x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t sl = slen, i;

	if (sl > TF_BLOCK_SIZE) {
		do {
			/* Load src data, convert to LE if necessary */
			memcpy(x, usrc, TF_BLOCK_SIZE);
			usrc += TF_BLOCK_SIZE;
			data_to_le64(x, TF_BLOCK_SIZE);

			/* Adjust counter, process data */
			ctr_inc(ctx->ctr, TF_BLOCK_UNITS);
			tf1024_encrypt_blk(&ctx->tfs, ctx->ctr, y);
			for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

			/* Convert from LE if necessary, store result data */
			data_to_le64(y, sizeof(y));
			memcpy(udst, y, TF_BLOCK_SIZE);
			udst += TF_BLOCK_SIZE;
		} while ((sl -= TF_BLOCK_SIZE) >= TF_BLOCK_SIZE);
	}

	/* If there is remaining, then process it partially */
	if (sl) {
		memset(x, 0, TF_BLOCK_SIZE);
		memcpy(x, usrc, sl);
		data_to_le64(x, TF_BLOCK_SIZE);

		ctr_inc(ctx->ctr, TF_BLOCK_UNITS);
		tf1024_encrypt_blk(&ctx->tfs, ctx->ctr, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

		data_to_le64(y, TF_BLOCK_SIZE);
		memcpy(udst, y, sl);
	}
}
#endif /* TF_NEED_THREEFISH */

#define SKEIN_VERSION 1
#define SKEIN_ID 0x33414853 /* LE: "SHA3" */

#define SKEIN_BLOCK_CFG ((uint64_t)4 << 56)
#define SKEIN_BLOCK_MSG ((uint64_t)48 << 56)
#define SKEIN_BLOCK_OUT ((uint64_t)63 << 56)

#define SKEIN_FLAG_FIRST ((uint64_t)1 << 62)
#define SKEIN_FLAG_LAST ((uint64_t)1 << 63)

static inline void skput64lsb(uint8_t *dst, const uint64_t *src, size_t l)
{
	size_t n;

	for (n = 0; n < l; n++)
		dst[n] = (uint8_t)(src[n>>3] >> (8*(n&7)));
}

static inline void skget64lsb(uint64_t *dst, const uint8_t *src, size_t l)
{
	size_t n;

	for (n = 0; n<8*l; n += 8)
		dst[n/8] = (((uint64_t) src[n])) +
			(((uint64_t)src[n+1]) << 8) +
			(((uint64_t)src[n+2]) << 16) +
			(((uint64_t)src[n+3]) << 24) +
			(((uint64_t)src[n+4]) << 32) +
			(((uint64_t)src[n+5]) << 40) +
			(((uint64_t)src[n+6]) << 48) +
			(((uint64_t)src[n+7]) << 56);
}

static void sk1024_process_blk(sk1024_ctx *ctx, const uint8_t *in, size_t bnum, size_t l)
{
	uint64_t x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t i;

	do {
		ctx->tfs.T[0] += l;

		skget64lsb(x, in, tf_units(x));
		in += sizeof(x);

		tfs1024_init(&ctx->tfs);
		tf1024_encrypt_blk(&ctx->tfs, x, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++)
			ctx->tfs.K[i] = y[i] ^ x[i];

		ctx->tfs.T[1] &= ~SKEIN_FLAG_FIRST;
	} while (--bnum);
}

void sk1024_init(sk1024_ctx *ctx, size_t hbits)
{
	uint64_t cfg[TF_BLOCK_UNITS];

	ctx->hl = hbits;
	ctx->bl = 0;

	memset(cfg, 0, sizeof(cfg));
	cfg[0] = htole64(((uint64_t) SKEIN_VERSION << 32) + SKEIN_ID);
	cfg[1] = htole64(hbits);

	ctx->tfs.T[0] = 0;
	ctx->tfs.T[1] = SKEIN_BLOCK_CFG | SKEIN_FLAG_FIRST | SKEIN_FLAG_LAST;

	memset(ctx->tfs.K, 0, sizeof(ctx->tfs.K));
	sk1024_process_blk(ctx, (uint8_t *)cfg, 1, 32);

	ctx->tfs.T[0] = 0;
	ctx->tfs.T[1] = SKEIN_BLOCK_MSG | SKEIN_FLAG_FIRST;
}

void sk1024_update(sk1024_ctx *ctx, const void *msg, size_t l)
{
	const uint8_t *umsg = msg;
	size_t n;

	if (l + ctx->bl > TF_BLOCK_SIZE) {
		if (ctx->bl) {
			n = TF_BLOCK_SIZE - ctx->bl;
			if (n) {
				memcpy(&ctx->B[ctx->bl], umsg, n);
				l -= n;
				umsg += n;
				ctx->bl += n;
			}
			sk1024_process_blk(ctx, ctx->B, 1, TF_BLOCK_SIZE);
			ctx->bl = 0;
		}

		if (l > TF_BLOCK_SIZE) {
			n = (l-1) / TF_BLOCK_SIZE;
			sk1024_process_blk(ctx, umsg, n, TF_BLOCK_SIZE);
			l -= n * TF_BLOCK_SIZE;
			umsg += n * TF_BLOCK_SIZE;
		}
	}

	if (l) {
		memcpy(&ctx->B[ctx->bl], umsg, l);
		ctx->bl += l;
	}
}

void sk1024_final(sk1024_ctx *ctx, void *outhash)
{
	uint8_t *hash = outhash;
	uint64_t key[TF_BLOCK_UNITS];
	size_t i, b, n;

	if (ctx->bl < TF_BLOCK_SIZE)
		memset(ctx->B + ctx->bl, 0, TF_BLOCK_SIZE - ctx->bl);
	ctx->tfs.T[1] |= SKEIN_FLAG_LAST;
	sk1024_process_blk(ctx, ctx->B, 1, ctx->bl);

	b = (ctx->hl + 7) / 8;

	memset(ctx->B, 0, sizeof(ctx->B));
	memcpy(key, ctx->tfs.K, sizeof(key));

	for (i = 0; i * TF_BLOCK_SIZE < b; i++) {
		((uint64_t *)ctx->B)[0] = htole64((uint64_t)i);
		ctx->tfs.T[0] = 0;
		ctx->tfs.T[1] = SKEIN_BLOCK_OUT | SKEIN_FLAG_FIRST | SKEIN_FLAG_LAST;
		ctx->bl = 0;

		sk1024_process_blk(ctx, ctx->B, 1, sizeof(uint64_t));
		n = b - i*TF_BLOCK_SIZE;
		if (n >= TF_BLOCK_SIZE) n = TF_BLOCK_SIZE;
		skput64lsb(hash+i*TF_BLOCK_SIZE, ctx->tfs.K, n);
		memcpy(ctx->tfs.K, key, sizeof(key));
	}
}

void sk1024(const void *src, size_t slen, void *dst, size_t hbits)
{
	sk1024_ctx ctx;
	memset(&ctx, 0, sizeof(sk1024_ctx));

	sk1024_init(&ctx, hbits);
	sk1024_update(&ctx, src, slen);
	sk1024_final(&ctx, dst);

	memset(&ctx, 0, sizeof(sk1024_ctx));
}
