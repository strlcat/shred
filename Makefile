CFLAGS=-Wall -O2 -DSHRED_FAST64 -D_LARGEFILE64_SOURCE

all: shred

shred: shred.o shred.c
	$(CC) $(CFLAGS) $(LDFLAGS) shred.o -o shred

clean:
	rm -f *.o shred
