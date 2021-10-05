BUILD = ./obj
BIN = ./bin
.PHONY: all
copy = cp
ROOT = /mingw64/bin

objects = $(BUILD)/Cat.o
CFLAGS = -s -O3 -static -lfmt -lws2_32

CXX = g++
FILES = PowerSwitch.cpp

PowerSwitch.exe: $(objects) | $(if $(BIN), mkbin) $(if $(copy), copy)
	$(CXX) $(FILES) $(objects) $(CFLAGS) -o $(BIN)/PowerSwitch.exe

$(objects): ../../Cat.cpp | $(if $(BUILD), mkbuild)
	$(CXX) -c ../../Cat.cpp -o $(BUILD)/Cat.o

mkbuild:
	mkdir $(BUILD)
mkbin:
	mkdir $(BIN)
	
copy:
	cp $(ROOT)/libstdc++-6.dll $(BIN)/libstdc++-6.dll

.PHONY : clean
clean:
	rm -rf $(BUILD)
	rm -rf $(BIN)
