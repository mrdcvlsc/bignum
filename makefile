CPP = g++
CXXFLAGS= -I ./include -Wall -Wextra -O3 -march=native
LDFLAGS = -lbignum
OBJ := $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))

all : libbignum.a calc

calc: calc.cpp
	$(CPP) $(CXXFLAGS) $^ -L. $(LDFLAGS) -o $@

libbignum.a : $(OBJ)
	ar rvs $@ $?

$(OBJ): %.o : %.cpp
	$(CPP) -c $(CXXFLAGS) $< -o $@

clean:
	rm calc libbignum.a $(OBJ) $(TARGET)
