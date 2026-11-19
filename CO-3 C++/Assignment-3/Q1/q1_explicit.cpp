// Q1 design question: explicit constructors
// compile with   g++ q1_explicit.cpp               -> builds
// and with       g++ -DUSE_EXPLICIT q1_explicit.cpp -> error
#include <iostream>
#include <string>

class Book {
    std::string title;
public:
#ifdef USE_EXPLICIT
    explicit
#endif
    Book(const std::string& t) : title(t) {}
    void print() const { std::cout << "Shelved: " << title << '\n'; }
};

void shelve(const Book& b) { b.print(); }

int main()
{
    std::string name = "Dune";
    shelve(name);           // string silently becomes a Book
    Book b = name;          // copy-initialisation also needs a non-explicit constructor
    b.print();
}
