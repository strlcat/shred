override CFLAGS=-Wall -O2 -DSHRED_FAST64 -DTF_FAST -DTF_NEED_THREEFISH -D_LARGEFILE64_SOURCE

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: shred

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

shred: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm -f *.o shred
