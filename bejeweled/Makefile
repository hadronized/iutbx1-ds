# Bejeweled Makefile
# Ecrit par Dimitri Sabadie

CXX=g++
CXXFLAGS_DEBUG=-g
CXXFLAGS_RELEASE=-O2 -Os
CXXFLAGS=-Wall -Werror -pedantic $(CXXFLAGS_DEBUG)
INCLUDE=-I./include/
LIBS=-lSDL -lSDL_image -lSDL_ttf
TARGET=bejeweled

.PHONY: all, clean, mrproper

all: algorithm.o array.o diamond.o gameboard.o gameplay.o gui.o main.o matrix.o
	$(CXX) $^ -o $(TARGET) $(CXXFLAGS) $(LIBS)

main.o: src/main.cpp
	$(CXX) -c $< -o main.o $(CXXFLAGS) $(INCLUDE)

%.o: src/%.cpp include/%.h
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(TARGET)
