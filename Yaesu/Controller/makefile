CXX = g++
CXXFLAGS = -std=c++20 -s -O2

all: link
	
debug: CXXFLAGS = -std=c++20 -DDEBUG -g
debug: link

release: CXXFLAGS = -std=c++20 -s -O2
release: link
	
objects: FT891.o AsyncSerial.o Cat.o

FT891.o: 
	$(CXX) $(CXXFLAGS) -c FT891.cxx
AsyncSerial.o:	
	$(CXX) $(CXXFLAGS) -c AsyncSerial.cpp
Cat.o:	
	$(CXX) $(CXXFLAGS) -c ../CAT/Cat.cpp -o ./Cat.o

link: objects
	$(CXX) -o FT891.exe FT891.o Cat.o AsyncSerial.o -lfltk -lfmt -lwsock32 -lws2_32 -lboost_system-mt -lboost_thread-mt -lboost_program_options-mt

clean:
	rm -rf *.o
	rm -rf *.exe
