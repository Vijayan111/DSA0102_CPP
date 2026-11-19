// Q1 experiment: Book without a default constructor, then an array of Books
#include <iostream>
#include <string>

class Book {
    std::string title;
    int copies;
public:
    Book(const std::string& t, int c) : title(t), copies(c) {}   // no default constructor
    void print() const { std::cout << title << " " << copies << '\n'; }
};

int main()
{
    Book one("Dune", 2);      // fine
    Book shelf[3];            // needs Book::Book()
    one.print();
}
