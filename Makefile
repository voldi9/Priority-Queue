CXX=g++
CXXFLAGS=-O2 -std=c++11
LIBDIR=./lib
LIB=-L $(LIBDIR) -lpqueue
LIBFILE=$(LIBDIR)/libpqueue.a
HEADERS = timedcleaner.hpp ui.hpp main.hpp
BINARIES = timedcleaner.o ui.o


%.o: %.cpp $(HEADERS) $(LIBFILE)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIB)

all: main.cpp $(BINARIES) $(LIBFILE)
	$(CXX) $(CXXFLAGS) -o demo $^ $(LIB) -pthread

$(LIBFILE):
	cd $(LIBDIR) && make

.PHONY: clean

clean:
	$(RM) *.o *.a demo log