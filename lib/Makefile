CXX=g++
CXXFLAGS=-O2 -std=c++11
AR=ar
ARFLAGS=rvs
HEADERS = item.hpp pqueue.hpp
SOURCES = item.cpp pqueue.cpp
BINARIES = item.o pqueue.o
LIB = libpqueue.a
TEST = test.cpp
THEADER = test.hpp

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

libpqueue.a: $(BINARIES)
	$(AR) $(ARFLAGS) $@ $^

test: $(TEST) $(LIB) $(THEADER)
	$(CXX) $(CXXFLAGS) -o test $< $(LIB)

clean:
	$(RM) *.o *.a