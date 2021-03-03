CXX = g++ 
CXXFLAGS = -Wall -g -MMD

.PHONY: clean all

all: explicit 

clean:
	rm *.d
	rm *.o
	rm explicit

explicit: vector.o matrix.o

-include *.d

