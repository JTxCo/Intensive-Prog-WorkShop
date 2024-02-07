CXX = g++
CXXFLAGS = -std=c++20 -Wall

SRCS = functions_to_implement.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)
TARGET = main

SRCS2 = functions_to_implement.cpp test.cpp 
OBJS2 = $(SRCS2:.cpp=.o)
TARGET2 = target2

.PHONY: all clean

all: $(TARGET) $(TARGET2)

$(TARGET): catch.hpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(TARGET2): $(OBJS2)
	$(CXX) $(CXXFLAGS) $(OBJS2) -o $(TARGET2)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(OBJS2) $(TARGET2)
