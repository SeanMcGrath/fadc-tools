CC = g++
CC_FLAGS = $(shell root-config --cflags) -w
LIB_FLAGS =  $(shell root-config --libs) 
SHARED_FLAGS = -shared -fPIC $(CC_FLAGS) $(LIB_FLAGS)

PREFIX = /usr

BUILD_DIR = ../build

TARGET=fadc
TARGET_LIB = libfadc.so
TARGET_DICT = FadcToolsDict

SOURCES = $(wildcard *.c)

$(TARGET): $(TARGET).o
	$(CC) -o ../bin/$@ $(BUILD_DIR)/$^ -L../lib -lfadc $(CC_FLAGS) $(LIB_FLAGS)

$(TARGET_LIB): $(TARGET_DICT).cxx $(SOURCES)
	$(CC) -o ../lib/$@ $^ $(SHARED_FLAGS)

$(TARGET).o: $(TARGET_LIB)
	$(CC) -o $(BUILD_DIR)/$@ $(TARGET).c -c $(CC_FLAGS) 

$(TARGET_DICT).cxx: fadclib.h LinkDef.h
	rootcint -f $@ -c $^

clean:
	rm $(TARGET_DICT).* 
	rm ../build/*
	rm ../lib/*
	rm ../bin/*

install:
	cp -R ../bin/ ../lib/ $(PREFIX)

uninstall:
	rm $(PREFIX)/bin/$(TARGET)
	rm $(PREFIX)/lib/$(TARGET_LIB)
