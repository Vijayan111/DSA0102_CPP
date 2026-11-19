// Q1 - Library Book Records: constructors, initializer lists, delegation, validation
#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;

    // the only place in the class that checks the number of copies
    static int checkCopies(int c)
    {
        if (c < 0)
            throw std::invalid_argument("copies cannot be negative: " + std::to_string(c));
        return c;
    }

public:
    // 1) full details - the main constructor, all the others delegate to it
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(checkCopies(c))
    {
        std::cout << "  ctor: full details\n";
    }

    // 2) donated book: only a title, one copy received
    explicit Book(const std::string& t) : Book(t, "Unknown", 1)
    {
        std::cout << "  ctor: title only (delegated)\n";
    }

    // 3) empty record that will be filled later
    Book() : Book("Untitled", "Unknown", 0)
    {
        std::cout << "  ctor: default (delegated)\n";
    }

    // filling an empty record later goes through the same check
    void fill(const std::string& t, const std::string& a, int c)
    {
        copies = checkCopies(c);
        title = t;
        author = a;
    }

    void print() const
    {
        std::cout << "  -> \"" << title << "\" by " << author << ", copies = " << copies << '\n';
    }
};

int main()
{
    std::cout << "--- one object for every constructor ---\n";
    Book b1("Wings of Fire", "A. P. J. Abdul Kalam", 5);
    b1.print();
    Book b2("Ponniyin Selvan");
    b2.print();
    Book b3;
    b3.print();

    std::cout << "\n--- filling the empty record later ---\n";
    b3.fill("Discrete Mathematics", "Kenneth Rosen", 3);
    b3.print();

    std::cout << "\n--- array of Books uses the default constructor ---\n";
    Book shelf[2];
    for (const Book& b : shelf) b.print();

    std::cout << "\n--- invalid number of copies ---\n";
    try {
        Book bad("Broken", "Nobody", -4);
        bad.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "  rejected: " << e.what() << '\n';
    }
    try {
        b3.fill("Another", "Someone", -1);
    } catch (const std::invalid_argument& e) {
        std::cout << "  rejected: " << e.what() << '\n';
    }
    std::cout << "  b3 after the failed fill:\n";
    b3.print();
}
