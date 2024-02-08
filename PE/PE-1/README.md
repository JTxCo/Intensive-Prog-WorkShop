# Project 1: Multidimensional Point Class

The first project in the course focuses on the creation of a `Point` class in C++, used to represent and manipulate points in n-dimensional space. The project offered a hands-on experience in object-oriented programming, ensuring an understanding of classes, objects, and member functions, while dealing with advanced concepts like multi-dimensional arrays or vectors.

Key elements of the project include:

-  Establishing a `Point` class with custom constructors to support creation of n-dimensional points at the origin or with specified coordinates.
-  Incorporating getter and setter methods for each coordinate.
-  Implementing a method `Distance` to calculate the Euclidean distance between two points of equivalent dimensions.
-  Designing a `Translate` method to shift all coordinates by a specified integer value.
-  Constructing a `main.cpp` to demonstrate the functionality of the `Point` class.
-  Crafting a `Makefile` to successfully build and clean the project.

This project further encourages error handling and system robustness: in the event that the `Distance` method is invoked with two points of differing dimensions, the program identifies the error and throws an exception, ensuring no false distance is reported.

The makefile provided parallel a professional development setup, supporting commands `make` to compile the code, and `make clean` to remove all .o and binary files.

A focus on carefully crafted and commented code to meet the provided style guidelines ensures the codebase remains maintainable and understandable.

