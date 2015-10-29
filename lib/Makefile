CXX=g++
CXXFLAGS=-O2 -std=c++11
AR=ar
ARFLAGS=rvs
HEADERS = item.hpp pqueue.hpp
SOURCES = item.cpp pqueue.cpp
BINARIES = item.o pqueue.o

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

libpqueue.a: $(BINARIES)
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) *.o *.a