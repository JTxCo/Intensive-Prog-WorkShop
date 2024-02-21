#ifndef _LIBRARY_H_ // this is the header guard
#define _LIBRARY_H_

struct Book {
  std::string title;
  std::string author;

bool operator==(const Book &other) const {
    return (title == other.title) && (author == other.author);
  }
};


class Library {
public:
  Library();

  void PrintBooks();
  void Donate(Book b);
  void Donate(Book b, int num_copies);
  void BookEquals(Book b1, Book b2);

private:
  // arrays require size to be known at compile time.
  // if we were only going to store a fixed number of books
  // we could do this easily:
  // Book shelf_[10];
  std::vector<Book> shelf_;
};



#endif // _LIBRARY_H_
