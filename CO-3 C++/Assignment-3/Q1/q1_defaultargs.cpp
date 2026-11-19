// Q1 alternative: ONE constructor with default arguments instead of overloads + delegation
#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;
public:
    Book(const std::string& t = "Untitled", int c = 0, const std::string& a = "Unknown")
        : title(t), author(a), copies(c < 0 ? throw std::invalid_argument("copies cannot be negative") : c) {}

    void print() const
    {
        std::cout << '"' << title << "\" by " << author << ", copies = " << copies << '\n';
    }
};

int main()
{
    Book b1("Wings of Fire", 5, "A. P. J. Abdul Kalam");
    Book b2("Ponniyin Selvan");      // donated: we WANTED 1 copy, but the default gives 0
    Book b3;
    b1.print(); b2.print(); b3.print();
    try { Book bad("Broken", -4); } catch (const std::invalid_argument& e) { std::cout << "rejected: " << e.what() << '\n'; }
}
