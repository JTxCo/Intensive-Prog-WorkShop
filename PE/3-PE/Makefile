XX = g++
CXXFLAGS = -std=c++17 -Wall

all: test main

test: test.cpp pe3_references.cpp
	g++ -std=c++17 -o test test.cpp pe3_references.cpp

main: main.cpp pe3_references.cpp
	g++ -std=c++17 -o main main.cpp pe3_references.cpp

clean:
	rm -f main test