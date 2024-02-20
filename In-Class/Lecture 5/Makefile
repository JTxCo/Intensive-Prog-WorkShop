CXX = g++
CXXFLAGS = -std=c++20 -Wall

SRCS = Library.cpp run_library.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = library

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
