all:	library programs gammel

library:
	cd lib;	$(MAKE)

programs:
	cd Progs; $(MAKE)

gammel:
	cd Cluster; $(MAKE)

install:	all
	cd lib; $(MAKE) install
	cd Progs; $(MAKE) install
	cd Cluster; $(MAKE) install

clean:	
	cd lib; $(MAKE) clean
	cd Progs; $(MAKE) clean
	cd Cluster; $(MAKE) clean
