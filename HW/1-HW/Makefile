CXX = g++
CXXFLAGS = -std=c++20 -Wall -I$(INCDIR)

SRCDIR = src
TESTDIR = test
OBJDIR = obj
INCDIR = include

SRCS = $(filter-out $(SRCDIR)/Main.cpp, $(wildcard $(SRCDIR)/*.cpp))
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp)
OBJ_MAIN = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
OBJ_TEST = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TESTSRCS)) $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET_MAIN = Main
TARGET_TEST = test_runner



.PHONY: all main test clean

all: main test

main: obj_dir $(TARGET_MAIN)

test: obj_dir $(TARGET_TEST)

$(TARGET_MAIN): $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) $(OBJ_MAIN) -o $(TARGET_MAIN)

$(TARGET_TEST): $(OBJ_TEST) 
	$(CXX) $(CXXFLAGS) $(OBJ_TEST) -o $(TARGET_TEST)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj_dir:
	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(TARGET_MAIN) $(TARGET_TEST)
