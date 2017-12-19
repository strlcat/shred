#include <string.h>
#include "tf1024.h"

#define THREEFISH_PARITY 0x1bd11bdaa9fc1a22ULL

static void tf1024_init_for_skein(tfc1024_ctx *ctx)
{
	size_t i;

	ctx->K[TF_ARRAY_SZ(ctx->K) - 1] = THREEFISH_PARITY;
	for (i = 0; i < TF_ARRAY_SZ(ctx->K) - 1; i++)
		ctx->K[TF_ARRAY_SZ(ctx->K)-1] ^= ctx->K[i];

	ctx->T[2] = ctx->T[0] ^ ctx->T[1];
}

#ifdef TF_NEED_CORE
void tfc1024_init(tfc1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(tfc1024_ctx));
}

void tfc1024_done(tfc1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(tfc1024_ctx));
}

void tfc1024_set_key(tfc1024_ctx *ctx, const void *key, size_t klen)
{
	TF_UNIT_TYPE parity = THREEFISH_PARITY;
	int i;

	if (klen > TF_KEY_SIZE) return;

	memcpy(ctx->K, key, klen);
	memset((TF_BYTE_TYPE *)ctx->K+klen, 0, TF_KEY_SIZE-klen);
	data_to_little(ctx->K, sizeof(ctx->K));

	for (i = 0; i < TF_NR_UNITS; i++) parity ^= ctx->K[i];
	ctx->K[i] = parity;
}

void tfc1024_set_tweak(tfc1024_ctx *ctx, const void *tweak)
{
	const TF_UNIT_TYPE *tw = tweak;

	ctx->T[0] = tw[0];
	ctx->T[1] = tw[1];
	data_to_little(ctx->T, sizeof(ctx->T));

	ctx->T[2] = ctx->T[0] ^ ctx->T[1];
}
#endif

#ifdef TF_NEED_MODES
void tf1024_init(tf1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(tf1024_ctx));
}

void tf1024_done(tf1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(tf1024_ctx));
}

void tf1024_start_counter(tf1024_ctx *ctx, const void *ctr)
{
#ifdef TF_NEED_CTR_BACKUP
	memcpy(ctx->ictr, ctr, sizeof(ctx->ictr));
#endif
	memcpy(ctx->ctr, ctr, sizeof(ctx->ctr));

#ifdef TF_NEED_CTR_BACKUP
	data_to_little(ctx->ictr, sizeof(ctx->ictr));
#endif
	data_to_little(ctx->ctr, sizeof(ctx->ctr));
}

void tf1024_rewind_counter(tf1024_ctx *ctx, const void *newctr, size_t ctrsz)
{
#ifdef TF_NEED_CTR_BACKUP
	memcpy(ctx->ctr, ctx->ictr, sizeof(ctx->ctr));
#endif
	if (newctr && ctrsz) ctr_add(ctx->ctr, newctr, ctrsz > TF_ARRAY_SZ(ctx->ctr)
		? TF_ARRAY_SZ(ctx->ctr) : ctrsz);
}

#ifdef TF_NEED_TCTR_MODE
void tf1024_start_counter_tctr(tfc1024_ctx *ctx, const void *ctr)
{
	tfc1024_set_tweak(ctx, ctr);
#ifdef TF_NEED_CTR_BACKUP
	memcpy(ctx->iT, ctx->T, sizeof(ctx->iT));
#endif
}

void tf1024_rewind_counter_tctr(tfc1024_ctx *ctx, const void *newctr, size_t ctrsz)
{
#ifdef TF_NEED_CTR_BACKUP
	memcpy(ctx->T, ctx->iT, sizeof(ctx->T));
#endif
	if (newctr && ctrsz) ctr_add(ctx->T, newctr, ctrsz > TF_ARRAY_SZ(ctx->T)
		? TF_ARRAY_SZ(ctx->T) : ctrsz);
}
#endif

#ifdef TF_NEED_CTR_MODE
/* CTR mode threefish */
void tf1024_crypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst)
{
	const TF_BYTE_TYPE *usrc = src;
	TF_BYTE_TYPE *udst = dst;
	TF_UNIT_TYPE x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t sl = slen, i;

	if (sl > TF_BLOCK_SIZE) {
		do {
			/* Load src data, convert to LE if necessary */
			memcpy(x, usrc, TF_BLOCK_SIZE);
			usrc += TF_BLOCK_SIZE;
			data_to_little(x, TF_BLOCK_SIZE);

			/* Adjust counter, process data */
			ctr_inc(ctx->ctr, TF_BLOCK_UNITS);
			tfc1024_encrypt_blk(&ctx->tfc, ctx->ctr, y);
			for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

			/* Convert from LE if necessary, store result data */
			data_to_little(y, TF_BLOCK_SIZE);
			memcpy(udst, y, TF_BLOCK_SIZE);
			udst += TF_BLOCK_SIZE;
		} while ((sl -= TF_BLOCK_SIZE) >= TF_BLOCK_SIZE);
	}

	/* If there is remaining, then process it partially */
	if (sl) {
		memset(x, 0, TF_BLOCK_SIZE);
		memcpy(x, usrc, sl);
		data_to_little(x, TF_BLOCK_SIZE);

		ctr_inc(ctx->ctr, TF_BLOCK_UNITS);
		tfc1024_encrypt_blk(&ctx->tfc, ctx->ctr, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

		data_to_little(y, TF_BLOCK_SIZE);
		memcpy(udst, y, sl);
	}
}
#endif


#ifdef TF_NEED_TCTR_MODE
/* Tweak CTR mode threefish. */
void tf1024_tctr_encrypt(tfc1024_ctx *ctx, const void *src, size_t slen, void *dst)
{
	const TF_BYTE_TYPE *usrc = src;
	TF_BYTE_TYPE *udst = dst;
	TF_UNIT_TYPE x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t sl = slen, i;

	if (sl >= TF_BLOCK_SIZE) {
		do {
			/* Load src data, convert to LE if necessary */
			memcpy(x, usrc, TF_BLOCK_SIZE);
			usrc += TF_BLOCK_SIZE;
			data_to_little(x, TF_BLOCK_SIZE);

			/*
			 * Increment tweak, up to it's full size,
			 * 192 bits wide counter.
			 */
			ctr_inc(ctx->T, TF_ARRAY_SZ(ctx->T));
			/* Encrypt plaintext. It's always going to be different. */
			tfc1024_encrypt_blk(ctx, x, y);

			/* Convert from LE if necessary, store result data */
			data_to_little(y, TF_BLOCK_SIZE);
			memcpy(udst, y, TF_BLOCK_SIZE);
			udst += TF_BLOCK_SIZE;
		} while ((sl -= TF_BLOCK_SIZE) >= TF_BLOCK_SIZE);
	}

	/*
	 * If there is remaining, then process it partially using plain CTR mode.
	 * This will automatically become TCTR again if block will be padded by caller.
	 */
	if (sl) {
		memset(x, 0, TF_BLOCK_SIZE);
		memcpy(x, usrc, sl);
		data_to_little(x, TF_BLOCK_SIZE);

		memset(y, 0, TF_BLOCK_SIZE);
		memcpy(y, ctx->T, sizeof(ctx->T));
		ctr_inc(y, TF_BLOCK_UNITS);
		tfc1024_encrypt_blk(ctx, y, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

		data_to_little(y, TF_BLOCK_SIZE);
		memcpy(udst, y, sl);
	}
}

void tf1024_tctr_decrypt(tfc1024_ctx *ctx, const void *src, size_t slen, void *dst)
{
	const TF_BYTE_TYPE *usrc = src;
	TF_BYTE_TYPE *udst = dst;
	TF_UNIT_TYPE x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t sl = slen, i;

	if (sl >= TF_BLOCK_SIZE) {
		do {
			/* Load src data, convert to LE if necessary */
			memcpy(x, usrc, TF_BLOCK_SIZE);
			usrc += TF_BLOCK_SIZE;
			data_to_little(x, TF_BLOCK_SIZE);

			/* Prepare known tweak */
			ctr_inc(ctx->T, TF_ARRAY_SZ(ctx->T));
			/* Decrypt ciphertext */
			tfc1024_decrypt_blk(ctx, x, y);

			/* Convert from LE if necessary, store result data */
			data_to_little(y, TF_BLOCK_SIZE);
			memcpy(udst, y, TF_BLOCK_SIZE);
			udst += TF_BLOCK_SIZE;
		} while ((sl -= TF_BLOCK_SIZE) >= TF_BLOCK_SIZE);
	}

	/*
	 * If there is remaining, then process it partially using plain CTR mode.
	 * This will automatically become TCTR again if block will be padded by caller.
	 */
	if (sl) {
		memset(x, 0, TF_BLOCK_SIZE);
		memcpy(x, usrc, sl);
		data_to_little(x, TF_BLOCK_SIZE);

		memset(y, 0, TF_BLOCK_SIZE);
		memcpy(y, ctx->T, sizeof(ctx->T));
		ctr_inc(y, TF_BLOCK_UNITS);
		tfc1024_encrypt_blk(ctx, y, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

		data_to_little(y, TF_BLOCK_SIZE);
		memcpy(udst, y, sl);
	}
}
#endif /* TF_NEED_TCTR_MODE */

#ifdef TF_NEED_CBC_MODE
/* CBC mode threefish. */
void tf1024_cbc_encrypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst)
{
	const TF_BYTE_TYPE *usrc = src;
	TF_BYTE_TYPE *udst = dst;
	TF_UNIT_TYPE x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t sl = slen, i;

	if (sl >= TF_BLOCK_SIZE) {
		do {
			/* Load src data, convert to LE if necessary */
			memcpy(x, usrc, TF_BLOCK_SIZE);
			usrc += TF_BLOCK_SIZE;
			data_to_little(x, TF_BLOCK_SIZE);

			/* Add plaintext to IV or previoud block */
			for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] = x[i] ^ ctx->ctr[i];
			/* Encrypt result */
			tfc1024_encrypt_blk(&ctx->tfc, y, x);
			/* Save result for next block */
			memcpy(ctx->ctr, x, TF_BLOCK_SIZE);

			/* Convert from LE if necessary, store result data */
			data_to_little(x, TF_BLOCK_SIZE);
			memcpy(udst, x, TF_BLOCK_SIZE);
			udst += TF_BLOCK_SIZE;
		} while ((sl -= TF_BLOCK_SIZE) >= TF_BLOCK_SIZE);
	}

	/*
	 * If there is remaining, then process it partially using plain CTR mode.
	 * This will automatically become CBC again if block will be padded by caller.
	 */
	if (sl) {
		memset(x, 0, TF_BLOCK_SIZE);
		memcpy(x, usrc, sl);
		data_to_little(x, TF_BLOCK_SIZE);

		ctr_inc(ctx->ctr, TF_BLOCK_UNITS);
		tfc1024_encrypt_blk(&ctx->tfc, ctx->ctr, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

		data_to_little(y, TF_BLOCK_SIZE);
		memcpy(udst, y, sl);
	}
}

void tf1024_cbc_decrypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst)
{
	const TF_BYTE_TYPE *usrc = src;
	TF_BYTE_TYPE *udst = dst;
	TF_UNIT_TYPE x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS], t[TF_BLOCK_UNITS];
	size_t sl = slen, i;

	if (sl >= TF_BLOCK_SIZE) {
		do {
			/* Load src data, convert to LE if necessary */
			memcpy(x, usrc, TF_BLOCK_SIZE);
			usrc += TF_BLOCK_SIZE;
			data_to_little(x, TF_BLOCK_SIZE);

			/* Save temporary */
			memcpy(t, x, TF_BLOCK_SIZE);
			/* Decrypt block */
			tfc1024_decrypt_blk(&ctx->tfc, x, y);
			/* Remove IV */
			for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= ctx->ctr[i];
			/* Save IV for next block */
			memcpy(ctx->ctr, t, TF_BLOCK_SIZE);

			/* Convert from LE if necessary, store result data */
			data_to_little(y, TF_BLOCK_SIZE);
			memcpy(udst, y, TF_BLOCK_SIZE);
			udst += TF_BLOCK_SIZE;
		} while ((sl -= TF_BLOCK_SIZE) >= TF_BLOCK_SIZE);
	}

	/*
	 * If there is remaining, then process it partially using plain CTR mode.
	 * This will automatically become CBC again if block will be padded by caller.
	 */
	if (sl) {
		memset(x, 0, TF_BLOCK_SIZE);
		memcpy(x, usrc, sl);
		data_to_little(x, TF_BLOCK_SIZE);

		ctr_inc(ctx->ctr, TF_BLOCK_UNITS);
		tfc1024_encrypt_blk(&ctx->tfc, ctx->ctr, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++) y[i] ^= x[i];

		data_to_little(y, TF_BLOCK_SIZE);
		memcpy(udst, y, sl);
	}
}
#endif /* TF_NEED_CBC_MODE */
#endif /* TF_NEED_MODES */

#define SKEIN_VERSION 1
#define SKEIN_ID 0x33414853 /* LE: "SHA3" */

#define SKEIN_BLOCK_KEY (0)
#define SKEIN_BLOCK_CFG ((TF_UNIT_TYPE)4 << 56)
#define SKEIN_BLOCK_MSG ((TF_UNIT_TYPE)48 << 56)
#define SKEIN_BLOCK_OUT ((TF_UNIT_TYPE)63 << 56)

#define SKEIN_FLAG_FIRST ((TF_UNIT_TYPE)1 << 62)
#define SKEIN_FLAG_LAST ((TF_UNIT_TYPE)1 << 63)

static inline void skput64lsb(TF_BYTE_TYPE *dst, const TF_UNIT_TYPE *src, size_t l)
{
	size_t n;

	for (n = 0; n < l; n++)
		dst[n] = (TF_BYTE_TYPE)(src[n>>3] >> (TF_SIZE_UNIT*(n&7)));
}

static inline void skget64lsb(TF_UNIT_TYPE *dst, const TF_BYTE_TYPE *src, size_t l)
{
	size_t n;

	for (n = 0; n<TF_SIZE_UNIT*l; n += TF_SIZE_UNIT)
		dst[n/TF_SIZE_UNIT] = (((TF_UNIT_TYPE)src[n])) +
			(((TF_UNIT_TYPE)src[n+1]) << 8) +
			(((TF_UNIT_TYPE)src[n+2]) << 16) +
			(((TF_UNIT_TYPE)src[n+3]) << 24) +
			(((TF_UNIT_TYPE)src[n+4]) << 32) +
			(((TF_UNIT_TYPE)src[n+5]) << 40) +
			(((TF_UNIT_TYPE)src[n+6]) << 48) +
			(((TF_UNIT_TYPE)src[n+7]) << 56);
}

static void sk1024_process_blk(sk1024_ctx *ctx, const TF_BYTE_TYPE *in, size_t bnum, size_t l)
{
	TF_UNIT_TYPE x[TF_BLOCK_UNITS], y[TF_BLOCK_UNITS];
	size_t i;

	do {
		ctx->tfc.T[0] += l;

		skget64lsb(x, in, TF_ARRAY_SZ(x));
		in += sizeof(x);

		tf1024_init_for_skein(&ctx->tfc);
		tfc1024_encrypt_blk(&ctx->tfc, x, y);
		for (i = 0; i < TF_BLOCK_UNITS; i++)
			ctx->tfc.K[i] = y[i] ^ x[i];

		ctx->tfc.T[1] &= ~SKEIN_FLAG_FIRST;
	} while (--bnum);
}

void sk1024_init_key(sk1024_ctx *ctx)
{
	memset(ctx, 0, sizeof(sk1024_ctx));

	ctx->hl = TF_MAX_BITS;
	ctx->bl = 0;
	ctx->tfc.T[0] = 0;
	ctx->tfc.T[1] = SKEIN_BLOCK_KEY | SKEIN_FLAG_FIRST;
	memset(ctx->tfc.K, 0, sizeof(ctx->tfc.K));
}

void sk1024_update_key(sk1024_ctx *ctx, const void *key, size_t klen)
{
	sk1024_update(ctx, key, klen);
}

void sk1024_final_key(sk1024_ctx *ctx)
{
	TF_UNIT_TYPE cfg[TF_BLOCK_UNITS];

	memset(cfg, 0, sizeof(cfg));
	sk1024_final_pad(ctx, (void *)cfg, 1);
	memcpy(ctx->tfc.K, cfg, sizeof(cfg));
	data_to_little(ctx->tfc.K, TF_KEY_SIZE);
}

void sk1024_init(sk1024_ctx *ctx, size_t bits, int with_key)
{
	TF_UNIT_TYPE cfg[TF_BLOCK_UNITS];

	if (!with_key) memset(ctx, 0, sizeof(sk1024_ctx));

	ctx->hl = bits;
	ctx->bl = 0;

	memset(cfg, 0, sizeof(cfg));
	cfg[0] = TF_SWAP_FUNC(((TF_UNIT_TYPE)SKEIN_VERSION << 32) + SKEIN_ID);
	cfg[1] = TF_SWAP_FUNC(bits);

	ctx->tfc.T[0] = 0;
	ctx->tfc.T[1] = SKEIN_BLOCK_CFG | SKEIN_FLAG_FIRST | SKEIN_FLAG_LAST;

	sk1024_process_blk(ctx, (TF_BYTE_TYPE *)cfg, 1, 32);

	ctx->tfc.T[0] = 0;
	ctx->tfc.T[1] = SKEIN_BLOCK_MSG | SKEIN_FLAG_FIRST;
}

void sk1024_update(sk1024_ctx *ctx, const void *msg, size_t l)
{
	const TF_BYTE_TYPE *umsg = msg;
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

void sk1024_final_pad(sk1024_ctx *ctx, void *outhash, short do_pad)
{
	TF_BYTE_TYPE *hash = outhash;
	TF_UNIT_TYPE key[TF_BLOCK_UNITS], *X;
	size_t i, b, n;

	if (ctx->bl < TF_BLOCK_SIZE)
		memset(ctx->B + ctx->bl, 0, TF_BLOCK_SIZE - ctx->bl);
	ctx->tfc.T[1] |= SKEIN_FLAG_LAST;
	sk1024_process_blk(ctx, ctx->B, 1, ctx->bl);

	if (do_pad) {
		skput64lsb(outhash, ctx->tfc.K, TF_BLOCK_SIZE);
		return;
	}

	b = (ctx->hl + 7) / 8;

	memset(ctx->B, 0, sizeof(ctx->B));
	memcpy(key, ctx->tfc.K, sizeof(key));

	for (i = 0; i * TF_BLOCK_SIZE < b; i++) {
		X = (TF_UNIT_TYPE *)ctx->B;
		X[0] = TF_SWAP_FUNC((TF_UNIT_TYPE)i);
		ctx->tfc.T[0] = 0;
		ctx->tfc.T[1] = SKEIN_BLOCK_OUT | SKEIN_FLAG_FIRST | SKEIN_FLAG_LAST;
		ctx->bl = 0;

		sk1024_process_blk(ctx, ctx->B, 1, sizeof(TF_UNIT_TYPE));
		n = b - i*TF_BLOCK_SIZE;
		if (n >= TF_BLOCK_SIZE) n = TF_BLOCK_SIZE;
		skput64lsb(hash+i*TF_BLOCK_SIZE, ctx->tfc.K, n);
		memcpy(ctx->tfc.K, key, sizeof(key));
	}
}

void sk1024_final(sk1024_ctx *ctx, void *outhash)
{
	sk1024_final_pad(ctx, outhash, 0);
}

void sk1024(const void *src, size_t slen, void *dst, size_t bits)
{
	sk1024_ctx ctx;
	memset(&ctx, 0, sizeof(sk1024_ctx));

	sk1024_init(&ctx, bits, 0);
	sk1024_update(&ctx, src, slen);
	sk1024_final(&ctx, dst);

	memset(&ctx, 0, sizeof(sk1024_ctx));
}
