CXX = g++
CXXFLAGS = -std=c++20 -Wall

SRCS = Game.cpp Player.cpp Main.cpp 
# using main to run the game
OBJS = $(SRCS:.cpp=.o)
TARGET = Main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
