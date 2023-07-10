SHELL=/bin/sh
.SUFFIXES: .o .c
.PHONY: clean

CC=gcc
CFLAGS=-g -Wall -Wextra -Wshadow -pedantic -O3 -std=c99
LDFLAGS=

bindir=bin
libdir=obj
srcdir=src

objects=$(patsubst $(srcdir)/%.c,$(libdir)/%.o,$(wildcard $(srcdir)/*.c))
.SECONDARY: $(objects)

all: $(bindir)/main

$(libdir)/%.o: $(srcdir)/%.c | $(libdir)
	$(CC) -c $(CFLAGS) $< -o $@

$(bindir)/%: $(objects) | $(bindir)
	$(CC) $(LDFLAGS) $^ -o $@

$(libdir):
	mkdir $(libdir)

$(bindir):
	mkdir $(bindir)

clean:
	rm -rf $(bindir)/* $(libdir)/*
