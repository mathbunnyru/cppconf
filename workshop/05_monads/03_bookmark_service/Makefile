PROGRAM   = main
CXX       = g++
CXXFLAGS  = -g -std=c++1z -Wall \
            -I../common \
            -I../common/3rd-party/ericniebler/range-v3/include \
            -I../common/3rd-party/philsquared/catch/include \
            -I../common/3rd-party/nlohmann/json/src \
            -fexceptions
LD_FLAGS  = -lboost_system

$(PROGRAM): main.o service.o
	$(CXX) $(LD_FLAGS)  -o $(PROGRAM) main.o service.o

.PHONY: clean dist

clean:
	-rm -f *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


