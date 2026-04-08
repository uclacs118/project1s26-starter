CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=

all: proxy

proxy: proxy.c
	$(CC) $(CFLAGS) proxy.c -o proxy $(LDFLAGS)

clean:
	rm -rf proxy

.PHONY: all clean
