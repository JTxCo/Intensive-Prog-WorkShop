CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude

SRCDIR = src
OBJDIR = obj
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET = Main

.PHONY: all clean

all: obj_dir $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj_dir:
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
