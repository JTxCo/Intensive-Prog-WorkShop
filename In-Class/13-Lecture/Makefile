CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: main

clean:
	rm main Emotion.o Creature.o

main: main.cpp Emotion.o Creature.o
	$(CXX) $(CXXFLAGS) main.cpp Emotion.o Creature.o -o main

Emotion.o: Emotion.cpp
	$(CXX) $(CXXFLAGS) -c Emotion.cpp

Creature.o: Creature.cpp
	$(CXX) $(CXXFLAGS) -c Creature.cpp
