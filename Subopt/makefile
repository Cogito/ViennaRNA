NAME1    = RNAsubopt

VIENNA   = ..

CFLAGS   = -O -DSUBOPT -I$(VIENNA)/H

LDFLAGS  = -O -L$(VIENNA)/lib -lRNA -lm


FILES   = RNAsubopt.c\
          fold.c\
          list.c\
          subopt.c
          

OBJ     = RNAsubopt.o\
          fold.o\
          list.o\
          subopt.o
          

all:	$(NAME1) popt

$(NAME1):   $(OBJ)
	    $(CC) -o $(NAME1) $(OBJ) $(LDFLAGS)

fold.o:	$(VIENNA)/lib/fold.c
	   $(CC) $(CFLAGS) -c $?

popt:	popt.o
	$(CC) -o popt popt.o $(LDFLAGS)

veryclean:      
	   rm -f *.o $(NAME1)

clean:      
	   rm -f *.o
