/*
 * Simple Stupid file & device shredder
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <libgen.h>

#ifdef SHRED_FAST64
#include <time.h>
#include "tfskein1024.c"
#endif

static char *progname;

static char *randsrc = "/dev/urandom";
static int iters = 3, force = 0, rmf = 0, zrf = 0, noround = 0, verb = 0, syncio = 0, alwaysrand = 0;

static char sfbuf[PATH_MAX*2];

#define XRET(x) if (!xret && xret < x) xret = x

static void usage(void)
{
	printf("usage: %s [-rfnuxzsvSRB] FILE FILE ...\n", progname);
	printf("wipe & remove files or shred disks\n\n");
	printf("  -r DEV: random source file\n");
	printf("  -f: force; try to chmod file if we own it\n");
	printf("  -n NUM: wipe file this number of iterations\n");
	printf("  -u: truncate & remove file\n");
	printf("  -x: exact writes, do not extend file to last block\n");
	printf("  -z: zero file after wiping at last iteration\n");
	printf("  -s NUM: overwrite only first NUM bytes\n");
	printf("  -R: always overwrite with random bytes\n");
	printf("  -S: synchronized IO\n");
	printf("  -B NUM: specify alternative write block size\n");
	printf("  -v: tell what actually we do\n\n");
	exit(3);
}

int main(int argc, char **argv)
{
	progname = basename(*argv);

	struct stat st;
	char *buf, *fname, *s, *d, rc = 0;
	int c, f, rsf;
#ifdef SHRED_FAST64
	tf1024_ctx tctx; memset(&tctx, 0, sizeof(tf1024_ctx));
	unsigned char keybuf[128], nonce[128];
#endif
	int xret = 0, pat = 0, last = 0, special = 0, it = 0;
	size_t blksz = 0, x, y;
	ssize_t l, ll, howmany = -1;

	opterr = 0;
	while ((c = getopt(argc, argv, "r:fn:uxzs:vRSB:")) != -1) {
		switch (c) {
			case 'r': randsrc = optarg; break;
			case 'f': force = 1; break;
			case 'n': iters = atoi(optarg); break;
			case 'u': rmf = 1; break;
			case 'x': noround = 1; break;
			case 'z': zrf = 1; break;
			case 'v': verb = 1; break;
			case 's': howmany = atol(optarg); break;
			case 'R': alwaysrand = 1; break;
			case 'S': syncio = O_SYNC; break;
			case 'B': blksz = atol(optarg); break;
			default: usage(); break;
		}
	}
	
	rsf = open(randsrc, O_RDONLY | O_LARGEFILE);
	if (rsf == -1) { perror(randsrc); exit(1); }

	if (!*(argv+optind)) usage();

	while (*(argv+optind)) {
		special = pat = 0;
		it = iters;

		fname = *(argv+optind);
		if (verb) fprintf(stderr, "destroying %s ...\n", fname);

		if (stat(fname, &st) == -1) { perror(fname); XRET(1); goto _next; }
		if (!blksz) blksz = (size_t)st.st_blksize;
		if (howmany != -1) {
			l = ll = howmany;
			noround = 1;
		}
		else l = ll = st.st_size;
		if (l == 0 && !S_ISREG(st.st_mode)) special = 1;
		memset(&st, 0, sizeof(struct stat));

		if (force) if (chmod(fname, S_IRUSR|S_IWUSR) == -1) { perror(fname); XRET(1); }
		f = open(fname, O_WRONLY | O_LARGEFILE | O_NOCTTY | syncio);
		if (f == -1) {
			XRET(1);
			perror(fname);
			goto _next;
		}
		
		buf = malloc(blksz);
		if (!buf) {
			perror("malloc"); XRET(2);
			fprintf(stderr, "Continuing with fixed buffer (%lu bytes long)\n", sizeof(sfbuf));
			buf = sfbuf; blksz = sizeof(sfbuf);
		}
		memset(buf, 0, blksz);

#ifdef SHRED_FAST64
		if (read(rsf, buf, blksz) <= 0) fprintf(stderr, "%s: read 0 bytes (wanted %lu)\n", randsrc, blksz);
		sk1024(buf, blksz, keybuf, 1024);
		tf1024_init(&tctx);
		tf1024_set_key(&tctx, keybuf, 1024);
		sk1024(keybuf, sizeof(keybuf), nonce, 1024);
		tf1024_set_nonce(&tctx, nonce, 0);
		memset(keybuf, 0, 128);
		memset(nonce, 0, sizeof(nonce));
#endif

		while (it) {
			lseek(f, 0L, SEEK_SET);

			if (it <= 1 && zrf) {
				pat = 1;
				rc = 0;
			}
			else if (!alwaysrand) {
				if (read(rsf, &rc, 1) <= 0) fprintf(stderr, "%s: read 0 bytes (wanted 1)\n", randsrc);
				pat = rc%2;
				if (read(rsf, &rc, 1) <= 0) fprintf(stderr, "%s: read 0 bytes (wanted 1)\n", randsrc);
			}
			else pat = 0;
			
			if (verb) {
				if (pat) fprintf(stderr, "iteration %d (%02hhx%02hhx%02hhx) ...\n", iters-it+1, rc, rc, rc);
				else fprintf(stderr, "iteration %d (random) ...\n", iters-it+1);
			}

			while (1) {
				if (!pat) {
#ifdef SHRED_FAST64
					tf1024_crypt(&tctx, buf, blksz, buf);
#else
					if (read(rsf, buf, blksz) <= 0)
						fprintf(stderr, "%s: read 0 bytes (wanted %lu)\n", randsrc, blksz);
#endif
				}
				else memset(buf, rc, blksz);

				if (l <= blksz && !special) last = 1;
				errno = 0;
				l -= write(f, buf, (noround && last) ? l : blksz);
				if (errno) { perror(fname); errno = 0; break; }
				if (last) { last = 0; break; }
			}

			l = ll;
			fdatasync(f);
			it--;
		}

		if (rmf) {
			close(f);
			f = open(fname, O_WRONLY | O_TRUNC | O_LARGEFILE | O_NOCTTY | syncio);
			if (verb) fprintf(stderr, "removing %s ...\n", fname);
			x = strnlen(fname, sizeof(sfbuf)/2);
			s = sfbuf+(sizeof(sfbuf)/2);
			memcpy(sfbuf, fname, x); *(sfbuf+x) = 0;
			d = strrchr(sfbuf, '/');
			if (d) {
				d++;
				y = d-sfbuf;
				memset(d, '0', x-(d-sfbuf));
			}
			else {
				y = 0;
				memset(sfbuf, '0', x);
			}
			memcpy(s, sfbuf, x); *(s+x) = 0;

			/* Somehow I need to rename original to destination */
			if (access(s, R_OK) != -1) {
				fprintf(stderr, "%s already exists!\n", s);
				unlink(fname);
				goto _next;
			}
			if (verb) fprintf(stderr, "%s -> %s\n", fname, s);
			if (rename(fname, s) == -1) {
				perror(s);
				goto _next;
			}

			while (x > y+1) {
				*(sfbuf+x) = 0;
				x--;
				*(s+x) = 0;
				if (access(s, R_OK) != -1) {
					fprintf(stderr, "%s already exists!\n", s);
					unlink(sfbuf);
					goto _next;
				}
				if (verb) fprintf(stderr, "%s -> %s\n", sfbuf, s);
				if (rename(sfbuf, s) == -1) {
					perror(s);
					goto _next;
				}
			}

			if (verb) fprintf(stderr, "remove %s\n", s);
			unlink(s);
			if (verb) fprintf(stderr, "done away with %s.\n", fname);
		}

#ifdef SHRED_FAST64
		tf1024_done(&tctx);
#endif
		if (buf && buf != sfbuf) free(buf);
		if (f != -1) close(f);

_next:
		optind++;
	}
	
	close(rsf);

	return xret;
}
