CC = g++
CC_FLAGS = -shared -fPIC $(shell root-config --cflags --libs) -w 

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard T*.h)
ROOTSYS = /usr
MACRO_DIR = share/root/macros

libWaves.so: WavesDict.cxx $(SOURCES)
	g++ -o ../$(MACRO_DIR)/$@ $^ $(CC_FLAGS)

WavesDict.cxx: $(HEADERS) LinkDef.h
	rootcint -f $@ -c $^

clean:
	rm ../$(MACRO_DIR)/libWaves.so WavesDict.*  

install:
	cp -R ../bin/ ../share/ $(ROOTSYS)
	install ../etc/rootlogon.C ~
	install ../etc/rootrc ~/.rootrc
	chmod +rw ~/rootlogon.C ~/.rootrc

