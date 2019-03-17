override CFLAGS=-Wall -O3

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: shred

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

shred: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm -f *.o shred
