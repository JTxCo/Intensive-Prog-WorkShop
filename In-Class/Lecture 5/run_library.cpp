#include <iostream>
#include <vector>
#include "Library.h"

using std::string;
// Name(s):
//
// Complete numbered coding tasks.
// Answer the questions with "Answer: " in the comments by writing your answer in the comments.
// some experiments might result in non-running/non-compiling code. Leave these experiments in, but
// comment them out.
// Turn in run_library.cpp, Library.h, and Library.cpp on Canvas before the end of class.
// make sure to leave a comment here and on canvas with your name and the name(s) of your partners.

int main() {
 // 1) Instantiate a couple Books. Set their fields equal to some values.

    Book b1 = {"The Great Gatsby", "F. Scott Fitzgerald"};
    Book b2 = {"The three musketeers", "Alexandre Dumas"};
    Book b3 = {"Thousand leagues under the sea", "Jules Verne"};
    Book b4 = {"The count of Monte Cristo", "Alexandre Dumas"};
    Book b5 = {"The Last of the Mohicans", "James Fenimore Cooper"};
    Book b6 = {"Moby Dick", "Herman Melville"};



    // Print out the values of the books' fields.
    // printf("%s %s", b1.author.c_str(), b1.title.c_str());

    // 2) Instantiate a Library.
    Library library;


    // 3) Add a void Donate(Book b) method to your Library class.
    // Your Library should store the new book at the end of its shelf.


    // 4) Donate one of the Books that you instantiated to your Library.
    library.Donate(b1);

    // 5) Print out the books in the Library (use the given PrintBooks method)
    library.PrintBooks();

    // 6) Change the title and/or author of the book that you donated to
    // something different.
    b1.author = "Joel Carlson";

    // Print out the new book information, then print out the books in your
    library.PrintBooks();



    // Library. Did changing the Book information change it in your Library?
    //
    // Answer (and your hypothesis for why/why not):
    // No it did not change the value of book b1 since it is pass by value

    // 7) Create two Books that are separate structs (not pointers or references)
    // but that have the same information.
    // use the == operator to test if they are equal. What happens?
    // if it succeeds, are these equal?
    Book b7 = {"The Hobbit", "J.R.R. Tolkien"};
    Book b8 = {"The Hobbit", "J.R.R. Tolkien"};

    if (b7 == b8) {
        std::cout << "The books are equal" << std::endl;
    } else {
        std::cout << "The books are not equal" << std::endl;
    }
    // library.BookEquals(b7, b8);

    //
    // Answer:
    // bad good, don't do that. it no worky


    // 8) Create two Book references to your Books from # 7.
    // use the == operator to test if they are equal. What happens?
    // if it succeeds, are these equal?
    Book &b9 = b7;
    Book &b10 = b8;

    if (b8 == b9) {
        std::cout << "The books are equal" << std::endl;
    } else {
        std::cout << "The books are not equal" << std::endl;
    }



    //
    // Answer:
    // see answer 8, it no worky

    // 9) Create two Book pointers to your Books from # 7.
    // use the == operator to test if they are equal. What happens?
    // if it succeeds, are these equal?
    Book *b11 = &b7;
    Book *b12 = &b8;

    if(b11 == b12) {
        std::cout << "The books are equal" << std::endl;
    } else {
        std::cout << "The books are not equal" << std::endl;
    }
    //
    // Answer:
    // see answer 8, it no worky


    // 10) Add a void Donate(Book b, int num_copies) method to your Library class.
    // your Library should add num_copies of Book b to its shelf.


    // 11) Finally, if you reach this far, work on finding a solution to making it so
    // that you would be able to do any of the comparisons from # 7, 8, and 9




}
