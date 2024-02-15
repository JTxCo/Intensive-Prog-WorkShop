CXX = g++
CXXFLAGS    = -std=c++17 -Wall

all: main

clean:
	rm Earth.o main

main: Point.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Earth.o -o main

Point.o: Earth.cpp
	$(CXX) $(CXXFLAGS) -c Earth.cpp
