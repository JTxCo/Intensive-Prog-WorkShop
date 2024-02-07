# This is an example make file

CXX = g++  # the compiler
CXXFLAGS = -std=c++20 -Wall  # flags for the compiler (use c++17 standards, turn on all optional warnings); add -ggdb if you want to use gdb to debug!

# runs for "make all"
all: scope

# note that lines below targets must be
# TABBED in (not spaces!)
clean:
	rm scopen

scope: scope.cpp
	$(CXX) $(CXXFLAGS) scope.cpp -o scope
