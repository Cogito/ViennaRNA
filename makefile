all:	library programs gammel

library:
	cd lib;	$(MAKE)

programs:
	cd Progs; $(MAKE)

gammel:
	cd Analyse; $(MAKE)

install:	all
	cd lib; $(MAKE) install
	cd Progs; $(MAKE) install
	cd Analyse; $(MAKE) install

clean:	
	cd lib; $(MAKE) clean
	cd Progs; $(MAKE) clean
	cd Analyse; $(MAKE) clean
