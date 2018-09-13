PROGRAM=01_average
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -I/usr/local/hpx/include

$(PROGRAM): main.o
	$(CXX) -o $(PROGRAM) main.o -L/usr/local/hpx/lib/ -lhpx -lboost_system

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


