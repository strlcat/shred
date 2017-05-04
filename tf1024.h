#ifndef TF1024_H
#define TF1024_H

/*
 * Config block for tfcrypt's tf1024.
 * Please modify or remove it it for your own
 * needs when porting to other projects.
 */
#define TF_FAST
#define TF_NEED_CORE
#define TF_NEED_MODES
/* #define TF_NEED_DECRYPT */
#define TF_NEED_CTR_MODE
/* #define TF_NEED_CTR_BACKUP */
/* #define TF_NEED_TCTR_MODE */
/* #define TF_NEED_CBC_MODE */
/* Config block end. */

#include <stdint.h>
#include <endian.h>

#define tf_units(x) (sizeof(x)/sizeof(x[0]))

#define TF_SIZE_UNIT (sizeof(uint64_t)) /* single uint64_t */
#define TF_NR_UNITS 16 /* how many of them? ops with uint64_t's */

#define TF_KEY_SIZE (TF_SIZE_UNIT * TF_NR_UNITS) /* byteops - memset, memcpy etc. */

#define TF_BLOCK_SIZE TF_KEY_SIZE /* for byteops - memset, memcpy etc. */
#define TF_BLOCK_UNITS TF_NR_UNITS /* for uint64_t ops */

#define TF_TO_BITS(x)   ((x) * TF_SIZE_UNIT) /* nr. bytes to bits (128 -> 1024) */
#define TF_FROM_BITS(x) ((x) / TF_SIZE_UNIT) /* nr. bits to bytes (1024 -> 128) */
#define TF_MAX_BITS (TF_BLOCK_SIZE * TF_SIZE_UNIT) /* max. bits supported (128 * 8 == 1024) */

/* If host is big endian, then do proper conversions. */
static inline void data_to_le64(void *p, size_t l)
{
	size_t idx;
	uint64_t *P = p;
	uint64_t t;

	for (idx = 0; idx < (l/sizeof(uint64_t)); idx++) {
		t = htole64(P[idx]);
		P[idx] = t;
	}
}

/* Counter operations: CTR and other similar modes. */
static inline void ctr_inc(uint64_t *x, size_t l)
{
	size_t i;

	for (i = 0; i < l; i++) {
		x[i] = ((x[i] + (uint64_t)1) & ((uint64_t)~0));
		if (x[i]) break;
	}
}

/* This one wants rewrite, but not called much often. */
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

typedef struct {
	uint64_t K[TF_NR_UNITS+1];
	uint64_t T[3];
#ifdef TF_NEED_MODES
#ifdef TF_NEED_TCTR_MODE
#ifdef TF_NEED_CTR_BACKUP
	uint64_t iT[3];
#endif
#endif
#endif
} tfc1024_ctx;

#ifdef TF_NEED_MODES
typedef struct {
	tfc1024_ctx tfc;
#ifdef TF_NEED_CTR_BACKUP
	uint64_t ictr[TF_NR_UNITS];
#endif
	uint64_t ctr[TF_NR_UNITS];
} tf1024_ctx;
#endif

typedef struct {
	tfc1024_ctx tfc;
	size_t hl, bl;
	uint8_t B[TF_BLOCK_SIZE];
} sk1024_ctx;

#ifdef TF_NEED_CORE
void tfc1024_init(tfc1024_ctx *ctx);
void tfc1024_done(tfc1024_ctx *ctx);
void tfc1024_set_key(tfc1024_ctx *ctx, const void *key, size_t klen);
void tfc1024_set_tweak(tfc1024_ctx *ctx, const void *tweak);
#endif

void tfc1024_encrypt_blk(tfc1024_ctx *ctx, const uint64_t *input, uint64_t *output);
#ifdef TF_NEED_DECRYPT
void tfc1024_decrypt_blk(tfc1024_ctx *ctx, const uint64_t *input, uint64_t *output);
#endif


void sk1024_init_key(sk1024_ctx *ctx, const void *key, size_t klen, size_t hbits);
void sk1024_init(sk1024_ctx *ctx, size_t hbits);
void sk1024_update(sk1024_ctx *ctx, const void *msg, size_t l);
void sk1024_final_pad(sk1024_ctx *ctx, void *outhash, short do_pad);
void sk1024_final(sk1024_ctx *ctx, void *outhash);
void sk1024(const void *src, size_t slen, void *dst, size_t hbits);

#ifdef TF_NEED_MODES
void tf1024_init(tf1024_ctx *ctx);
void tf1024_done(tf1024_ctx *ctx);
void tf1024_start_counter(tf1024_ctx *ctx, const void *ctr);
void tf1024_rewind_counter(tf1024_ctx *ctx, const void *newctr, size_t ctrsz);
#ifdef TF_NEED_CTR_MODE
void tf1024_crypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst);
#endif
#ifdef TF_NEED_TCTR_MODE
void tf1024_start_counter_tctr(tfc1024_ctx *ctx, const void *ctr);
void tf1024_rewind_counter_tctr(tfc1024_ctx *ctx, const void *newctr, size_t ctrsz);
void tf1024_tctr_encrypt(tfc1024_ctx *ctx, const void *src, size_t slen, void *dst);
void tf1024_tctr_decrypt(tfc1024_ctx *ctx, const void *src, size_t slen, void *dst);
#endif
#ifdef TF_NEED_CBC_MODE
void tf1024_cbc_encrypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst);
void tf1024_cbc_decrypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst);
#endif
#endif

#endif
