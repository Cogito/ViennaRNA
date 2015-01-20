# Edit the options in CFLAGS and ARFLAGS to suit your system.
# make install will copy libRNA.a to LIBDIR
SHELL	= /bin/sh

RANLIB	= ranlib
AR	= ar
ARFLAGS = rv

RM	= rm -f

#CC	= gcc   # insert your favorite compiler here

# add -DSUN4 if compiling for SunOS 4.1*  or -DHP9  for hpux-9.?? for faster 
# handling of floting point exceptions
# add -DLARGE_PF if you want pf_fold() to use doubles instead of floats
CFLAGS  = -O -I../H

LIBDIR	= /usr/local/lib

OBJ	= \
	fold.o \
	part_func.o \
	fold_vars.o \
	PS_dot.o \
	RNAstruct.o \
	treedist.o \
	stringdist.o \
	ProfileDist.o \
	dist_vars.o \
	inverse.o \
	utils.o

all:	libRNA.a
	

libRNA.a: $(OBJ)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $(OBJ)
	-$(RANLIB) $@

install:
	cp libRNA.a $(LIBDIR) 

clean:	
	$(RM) libRNA.a $(OBJ)


fold.o part_func.o: energy_par.h ./pair_mat.h ../H/fold_vars.h \
		    ../H/utils.h
PS_dot.o:	../H/utils.h ../H/fold_vars.h
RNAstruct.o:	../H/utils.h
treedist.c:	edit_cost.h ../H/dist_vars.h ../H/utils.h
stringdist.c:	edit_cost.h ../H/dist_vars.h ../H/utils.h
ProfileDist.c:	../H/fold_vars.h ../H/dist_vars.h ../H/utils.h ../H/part_func.h
inverse.c:	../H/fold_vars.h ../H/dist_vars.h ../H/utils.h ../H/part_func.h\
		../H/fold.h ./pair_mat.h ../H/treedist.h ../H/RNAstruct.h 
