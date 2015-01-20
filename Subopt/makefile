VIENNA   = ..

CFLAGS   = -O -I$(VIENNA)/H #  -g -Wall -mpentiumpro 

LDFLAGS  = -O -L$(VIENNA)/lib -lRNA -lm  # -g -mpentiumpro

BINDIR	= ../bin
MANDIR  = ../man/man1

FILES   = RNAsubopt.c\
          fold.c\
          list.c\
          subopt.c
          

OBJ     = RNAsubopt.o\
          fold.o\
          list.o\
          subopt.o
          

all:	RNAsubopt popt

RNAsubopt:   $(OBJ)
	    $(CC) -o RNAsubopt $(OBJ) $(LDFLAGS)

popt:	    popt.o
	    $(CC) -o popt popt.o $(LDFLAGS)

fold.o:	$(VIENNA)/lib/fold.c
	   $(CC) $(CFLAGS) -DSUBOPT -c $?

install: all
	cp RNAsubopt $(BINDIR)
	cp RNAsubopt.man $(MANDIR)/RNAsubopt.1	
	cp popt	$(BINDIR)

veryclean:      
	   rm -f *.o RNAsubopt popt

clean:      
	   rm -f *.o
