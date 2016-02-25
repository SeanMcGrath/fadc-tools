CC = g++
CC_FLAGS = -shared $(shell root-config --cflags --libs) -Wall

TARGET = libWaves.so
SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)

WavesDict.cxx: $(HEADERS)
     rootcint -f $@ -c  $^
 
libWaves.so: WavesDict.cxx $(SOURCES)
     g++ -o $@ $^ $(CC_FLAGS)

