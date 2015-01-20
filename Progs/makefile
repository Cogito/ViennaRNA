# Edit CFLAGS to suit your compiler;  make install will copy 
# executables and manpages to BINDIR and LIBDIR respectively.

SHELL	= /bin/sh

#CC	= gcc   # insert your favorite C compiler

CFLAGS  = -O -I../H

#On SGI IRIX >5 use
#LIBS    = -L../lib -lRNA -lm -lfpe
LIBS    = -L../lib -lRNA -lm 

BINDIR	= /usr/local/bin
MANDIR	= /usr/local/man/man1

ALL	= RNAfold RNAheat RNAeval RNAinverse RNAdistance RNApdist

all:	$(ALL)

$(ALL):	$$@.o
	$(CC) -o $@ $(CFLAGS) $@.o $(LIBS)

install:	all
	for i in $(ALL); do \
	cp $$i $(BINDIR); \
	strip $(BINDIR)/$$i; \
	cp ../man/$$i.man $(MANDIR)/$$i.1; \
	done

clean:
	rm -f *.o
	rm -f $(ALL)


RNAdistance.o:	../H/dist_vars.h ../H/RNAstruct.h ../H/treedist.h \
		../H/stringdist.h ../H/utils.h
RNAeval.o:	../H/fold_vars.h ../H/fold.h ../H/utils.h
RNAfold.o:	../H/fold.h ../H/part_func.h ../H/fold_vars.h ../H/utils.h
RNAheat.o:	../H/utils.h ../H/fold_vars.h ../H/part_func.h
RNAinverse.o:	../H/inverse.h ../H/fold_vars.h ../H/fold.h \
		../H/part_func.h ../H/utils.h
RNApdist.o:	../H/part_func.h ../H/fold_vars.h \
		../H/profiledist.h ../H/dist_vars.h ../H/utils.h
