CXX = g++
CXXFLAGS = -std=c++20 -Wall -I$(INCDIR)
LDFLAGS = -L/usr/local/lib -lbenchmark -pthread

SRCDIR = src
TESTDIR = test
BENCHDIR = Benchmark
OBJDIR = obj
INCDIR = include

SRCS = $(filter-out $(SRCDIR)/Main.cpp, $(wildcard $(SRCDIR)/*.cpp))
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp)
BENCHSRCS = $(wildcard $(BENCHDIR)/*.cpp)
OBJ_MAIN = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
OBJ_TEST = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TESTSRCS)) $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
OBJ_BENCH = $(patsubst $(BENCHDIR)/%.cpp,$(OBJDIR)/%.o,$(BENCHSRCS)) $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET_MAIN = Main
TARGET_TEST = test_runner
TARGET_BENCH = benchmark_runner

.PHONY: all main test benchmark clean

all: main test benchmark

main: obj_dir $(TARGET_MAIN)

test: obj_dir $(TARGET_TEST)

benchmark: obj_dir $(TARGET_BENCH)

$(TARGET_MAIN): $(SRCDIR)/Main.cpp $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/Main.cpp $(OBJ_MAIN) -o $(TARGET_MAIN) $(LDFLAGS)

$(TARGET_TEST): $(OBJ_TEST) 
	$(CXX) $(CXXFLAGS) $(OBJ_TEST) -o $(TARGET_TEST) $(LDFLAGS)

$(TARGET_BENCH): $(OBJ_BENCH) 
	$(CXX) $(CXXFLAGS) $(OBJ_BENCH) -o $(TARGET_BENCH) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(BENCHDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj_dir:
	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(TARGET_MAIN) $(TARGET_TEST) $(TARGET_BENCH)
