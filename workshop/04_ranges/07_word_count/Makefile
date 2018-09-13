PROGRAM=07_word_count
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -I../../range-v3/include -O3

$(PROGRAM): main.o
	$(CXX) -o $(PROGRAM) main.o

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


