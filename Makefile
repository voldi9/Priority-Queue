CXX=g++
CXXFLAGS=-O2 -std=c++11
LIBDIR=./lib
LIB=-L $(LIBDIR) -lpqueue
LIBFILE= $(LIBDIR)/libpqueue.a
LIBSOURCES= $(LIBDIR)/item.cpp $(LIBDIR)/item.hpp $(LIBDIR)/pqueue.cpp $(LIBDIR)/pqueue.hpp
HEADERS = timedcleaner.hpp ui.hpp wrapper.hpp main.hpp
BINARIES = timedcleaner.o ui.o wrapper.o


%.o: %.cpp $(HEADERS) $(LIBFILE)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIB)

all: main.cpp $(BINARIES) $(LIBFILE)
	$(CXX) $(CXXFLAGS) -o demo $^ $(LIB) -pthread

$(LIBFILE): $(LIBSOURCES)
	cd $(LIBDIR) && make

.PHONY: clean

clean:
	$(RM) *.o *.a demo log