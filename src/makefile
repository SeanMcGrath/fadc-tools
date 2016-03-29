CXX = g++
CXX_FLAGS = $(shell root-config --cflags) -w
LIB_FLAGS =  $(shell root-config --libs) 
SHARED_FLAGS = -shared -fPIC $(CXX_FLAGS) $(LIB_FLAGS)

PREFIX = /usr

BUILD_DIR = ../build
BIN_DIR = ../bin
LIB_DIR = ../lib

TARGET = fadc
TARGET_LIB = libfadc.so
TARGET_DICT = FadcToolsDict

SOURCES = $(wildcard *.c)
HEADERS := $(wildcard T*.h) 

$(TARGET): $(TARGET).o
	@echo "Compiling executable..."
	@mkdir -p $(BIN_DIR)
	@$(CXX) -o $(BIN_DIR)/$@ $(BUILD_DIR)/$^ -L$(LIB_DIR) -lfadc $(CXX_FLAGS) $(LIB_FLAGS)
	@echo "Done!"

$(TARGET_LIB): $(TARGET_DICT).cxx $(SOURCES)
	@echo "Compiling shared library..."
	@mkdir -p $(LIB_DIR)
	@$(CXX) -o ../lib/$@ $^ $(SHARED_FLAGS)
	@echo "Done!"

$(TARGET).o: $(TARGET_LIB)
	@echo "Compiling object files..."
	@mkdir -p $(BUILD_DIR)
	@$(CXX) -o $(BUILD_DIR)/$@ $(TARGET).c -c $(CXX_FLAGS) 
	@echo "Done!"

$(TARGET_DICT).cxx: $(HEADERS) LinkDef.h
	@echo "Generating ROOT Dictionary file for classes..."
	@rootcint -f $@ -c $^
	@echo "Done!"

clean:
	@rm -f $(TARGET_DICT).* 
	@rm -rf $(BUILD_DIR)
	@rm -rf $(LIB_DIR)
	@rm -rf $(BIN_DIR)
	@echo "Project clean"

install:
	@cp -R $(BIN_DIR) $(LIB_DIR) $(PREFIX)
	@echo "installed fadc in $(PREFIX)"

uninstall:
	@rm $(PREFIX)/bin/$(TARGET)
	@rm $(PREFIX)/lib/$(TARGET_LIB)
