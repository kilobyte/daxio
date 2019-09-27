ALL=daxio

CC=gcc
CFLAGS=-Wall -g -O2

all: $(ALL)

.c.o:
	$(CC) $(CFLAGS) -c $<

daxio: daxio.o util.o dimm_ndctl.o
	$(CC) $(CFLAGS) -o $@ $^ -lndctl -ldaxctl -lpmem

clean:
	rm -f $(ALL) *.o
