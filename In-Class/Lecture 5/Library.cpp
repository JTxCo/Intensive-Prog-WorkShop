#include <iostream>
#include <string>
#include <vector>

#include "Library.h"

/**
  Zero argument constructor initializes a library with a shelf but no books.
*/
Library::Library() {
  std::vector<Book> tmp;
  shelf_ = tmp;  // initialize my shelf
}

/**
  Prints out each book in the library, one per line to cout
*/
void Library::PrintBooks() {
  for (Book b : shelf_) {
    std::cout << b.title << " by " << b.author << std::endl;
  }
}


//adds a book b to the library
void Library::Donate(Book b) {
  shelf_.push_back(b);
}

//adds a book b to the library wiht n copies

void Library::Donate(Book b, int num_copies) {
  for (int i = 0; i < num_copies; i++) {
    shelf_.push_back(b);
  }
}

void Library::BookEquals(Book b1, Book b2) {
  if (b1.title == b2.title && b1.author == b2.author) {
    std::cout << "The books are equal" << std::endl;
  } else {
    std::cout << "The books are not equal" << std::endl;
  }
}

