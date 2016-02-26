CC = g++
CC_FLAGS = -shared -fPIC $(shell root-config --cflags --libs) -w 

TARGET = libfadc.so
TARGET_DICT = FadcToolsDict

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard T*.h)
ROOTSYS = /usr
MACRO_DIR = share/root/macros

$(TARGET): $(TARGET_DICT).cxx $(SOURCES)
	g++ -o ../$(MACRO_DIR)/$@ $^ $(CC_FLAGS)

$(TARGET_DICT).cxx: $(HEADERS) LinkDef.h
	rootcint -f $@ -c $^

clean:
	rm ../$(MACRO_DIR)/$(TARGET)
	rm $(TARGET_DICT).*

install:
	cp -R ../bin/ ../share/ $(ROOTSYS)
	install ../etc/rootlogon.C ~
	install ../etc/rootrc ~/.rootrc
	chmod +rw ~/rootlogon.C ~/.rootrc

