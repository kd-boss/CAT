CXX = g++
CXXFLAGS = -std=c++20 -s -O2

all: link
	
debug: CXXFLAGS = -std=c++20 -DDEBUG -g
debug: link

release: CXXFLAGS = -std=c++20 -s -O2
release: link
	
objects: FT891.o AsyncSerial.o Cat.o ComPortDialog.o MemoryEditor.o

FT891.o: 
	$(CXX) $(CXXFLAGS) -c FT891.cxx
AsyncSerial.o:	
	$(CXX) $(CXXFLAGS) -c AsyncSerial.cpp
Cat.o:	
	$(CXX) $(CXXFLAGS) -c ../CAT/Cat.cpp -o ./Cat.o
ComPortDialog.o:
	$(CXX) $(CXXFLAGS) -c ComPortDialog.cpp
MemoryEditor.o:
	$(CXX) $(CXXFLAGS) -c MemoryEditor.cpp
	
link: objects
	$(CXX) -o FT891.exe FT891.o ComPortDialog.o MemoryEditor.o Cat.o AsyncSerial.o -lfltk -lfmt -lwsock32 -lws2_32 -lboost_system-mt -lboost_thread-mt -mwindows

clean:
	rm -rf *.o
	rm -rf *.exe
