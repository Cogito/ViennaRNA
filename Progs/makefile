# Edit CFLAGS to suit your compiler;  
# make install will copy executables to BINDIR.

SHELL	= /bin/sh

#CC	= gcc -mpentiumpro -Wall  # insert your favorite C compiler
BINDIR	= ../bin
MANDIR	= ../man/man1

COPT    = -O # -g

CFLAGS  = $(COPT) -I../H

LDFLAGS = $(COPT) -L../lib -lRNA -lm # -ldmalloc


ALL	= RNAfold RNAheat RNAeval RNAinverse RNAdistance RNApdist

all:	$(ALL)

RNAfold: RNAfold.o ../lib/libRNA.a
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
	cp ../man/$$i.man $(MANDIR)/$$i.1; \
	done

clean:
	rm -f *.o
	rm -f $(ALL)

