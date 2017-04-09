#ifndef TF1024_H
#define TF1024_H

#define tf_units(x) (sizeof(x)/sizeof(x[0]))

#define TF_SIZE_UNIT (sizeof(uint64_t)) /* single uint64_t */
#define TF_NR_UNITS 16 /* how many of them? ops with uint64_t's */

#define TF_KEY_SIZE (TF_SIZE_UNIT * TF_NR_UNITS) /* byteops - memset, memcpy etc. */

#define TF_BLOCK_SIZE TF_KEY_SIZE /* for byteops - memset, memcpy etc. */
#define TF_BLOCK_UNITS TF_NR_UNITS /* for uint64_t ops */

#define TF_TO_BITS(x)   ((x) * TF_SIZE_UNIT) /* nr. bytes to bits (128 -> 1024) */
#define TF_FROM_BITS(x) ((x) / TF_SIZE_UNIT) /* nr. bits to bytes (1024 -> 128) */
#define TF_MAX_BITS (TF_BLOCK_SIZE * TF_SIZE_UNIT) /* max. bits supported (128 * 8 == 1024) */

typedef struct {
	uint64_t K[TF_NR_UNITS+1];
	uint64_t T[3];
} tfs1024_ctx;

#ifdef TF_NEED_THREEFISH
typedef struct {
	tfs1024_ctx tfs;
#ifdef TF_NEED_CTR_BACKUP
	uint64_t ictr[TF_NR_UNITS];
#endif
	uint64_t ctr[TF_NR_UNITS];
} tf1024_ctx;
#endif

typedef struct {
	tfs1024_ctx tfs;
	size_t hl, bl;
	uint8_t B[TF_BLOCK_SIZE];
} sk1024_ctx;

void sk1024_init(sk1024_ctx *ctx, size_t hbits);
void sk1024_update(sk1024_ctx *ctx, const void *msg, size_t l);
void sk1024_final(sk1024_ctx *ctx, void *outhash);
void sk1024(const void *src, size_t slen, void *dst, size_t hbits);

#ifdef TF_NEED_THREEFISH
void tf1024_init(tf1024_ctx *ctx);
void tf1024_done(tf1024_ctx *ctx);
void tf1024_set_key(tf1024_ctx *ctx, const void *key, size_t klen);
void tf1024_set_tweak(tf1024_ctx *ctx, const void *tweak);
void tf1024_start_counter(tf1024_ctx *ctx, const void *ctr);
void tf1024_rewind_counter(tf1024_ctx *ctx, const void *newctr, size_t ctrsz);
void tf1024_crypt(tf1024_ctx *ctx, const void *src, size_t slen, void *dst);
#endif

#endif
