# Edit CFLAGS to suit your compiler;  make install will copy 
# executables and manpages to BINDIR and LIBDIR respectively.

SHELL	= /bin/sh

#CC	= gcc   # insert your favorite C compiler

COPT    = -O

CFLAGS  = $(COPT) -I../H

LDFLAGS = $(COPT) -L../lib -lRNA -lm 

BINDIR	= /usr/local/bin
MANDIR	= /usr/local/man/man1

ALL	= RNAfold RNAheat RNAeval RNAinverse RNAdistance RNApdist

all:	$(ALL)

RNAfold: RNAfold.o
	$(CC) -o $@ $@.o $(LDFLAGS)

RNAheat: RNAheat.o
	$(CC) -o $@ $@.o $(LDFLAGS)

RNAeval: RNAeval.o
	$(CC) -o $@ $@.o $(LDFLAGS)

RNAinverse: RNAinverse.o
	$(CC) -o $@ $@.o $(LDFLAGS)

RNAdistance: RNAdistance.o
	$(CC) -o $@ $@.o $(LDFLAGS)

RNApdist: RNApdist.o
	$(CC) -o $@ $@.o $(LDFLAGS)


install:	all
	for i in $(ALL); do \
	cp $$i $(BINDIR); \
	strip $(BINDIR)/$$i; \
	cp ../man/$$i.man $(MANDIR)/$$i.1; \
	done

clean:
	rm -f *.o
	rm -f $(ALL)

