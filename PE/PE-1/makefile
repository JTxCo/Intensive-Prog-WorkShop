CXX = g++
CXXFLAGS = -std=c++20 -Wall

SRCS = Point.cpp Main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main	

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(OBJ) $(OUT)
