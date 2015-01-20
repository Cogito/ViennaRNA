# makefile

CFLAGS	= -I../H # -g

LDFLAGS	= -L../lib -lRNA -lm

BINDIR = ../bin
MANDIR = ../man/man1

all:	RNAplot b2ct

RNAplot: RNAplot.o
	$(CC) -o $@ $@.o $(LDFLAGS)

install: all
	cp RNAplot b2ct ct2b.pl dpzoom.pl mountain.pl \
	   b2mt.pl Fold $(BINDIR)
	cp RNAplot.man $(MANDIR)/RNAplot.1

clean:	
	rm -f *.o
	rm -f RNAplot b2ct

# End of file
