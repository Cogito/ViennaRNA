all:	library programs util gammel

library:
	cd lib;	$(MAKE)

programs:
	cd Progs; $(MAKE)

util:
	cd Utils; $(MAKE)

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
	cd Utils; $(MAKE) clean
