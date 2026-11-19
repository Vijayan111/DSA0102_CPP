// Q3 - Auditorium seat booking: dynamic constructor, destructor with summary, stack/heap/block objects
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

class Event {
    std::string name;
    int rows;
    int seatsPerRow;
    char** seat;          // seat[r][s] is '.' (free) or 'X' (booked)
    int booked;
    int cancelled;

public:
    // dynamic constructor: the size is only known when the event is created
    Event(const std::string& n, int r, int s)
        : name(n), rows(r), seatsPerRow(s), seat(nullptr), booked(0), cancelled(0)
    {
        if (r < 0 || s < 0)
            throw std::invalid_argument("rows and seats cannot be negative");
        seat = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            seat[i] = new char[seatsPerRow];
            std::memset(seat[i], '.', seatsPerRow);
        }
        std::cout << "  [ctor] " << name << ": " << rows << " x " << seatsPerRow << " seat map allocated\n";
    }

    Event(const Event&) = delete;              // a copy would share the seat map (Rule of Three)
    Event& operator=(const Event&) = delete;

    ~Event()
    {
        for (int i = 0; i < rows; ++i)
            delete[] seat[i];
        delete[] seat;
        std::cout << "  [dtor] " << name << ": closing summary - booked now " << booked
                  << ", cancellations " << cancelled << ", memory released\n";
    }

    bool book(int r, int s)
    {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow || seat[r][s] == 'X')
            return false;
        seat[r][s] = 'X';
        ++booked;
        return true;
    }

    bool cancel(int r, int s)
    {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow || seat[r][s] != 'X')
            return false;
        seat[r][s] = '.';
        --booked;
        ++cancelled;
        return true;
    }

    void show() const
    {
        for (int i = 0; i < rows; ++i) {
            std::cout << "    row " << i << ": ";
            for (int j = 0; j < seatsPerRow; ++j) std::cout << seat[i][j];
            std::cout << '\n';
        }
    }
};

int main()
{
    std::cout << "main starts\n";
    Event stackEvent("StackEvent", 3, 5);          // 1) object on the stack
    std::cout << "  book (1,2): " << std::boolalpha << stackEvent.book(1, 2) << '\n';
    std::cout << "  book (1,2) again: " << stackEvent.book(1, 2) << '\n';
    std::cout << "  book (0,4): " << stackEvent.book(0, 4) << '\n';
    std::cout << "  cancel (0,4): " << stackEvent.cancel(0, 4) << '\n';
    stackEvent.show();

    {
        std::cout << "block starts\n";
        Event blockEvent("BlockEvent", 2, 4);      // 2) object inside a block
        blockEvent.book(0, 0);
        std::cout << "block ends\n";
    }                                              // destroyed here

    Event* heapEvent = new Event("HeapEvent", 2, 3);   // 3) object on the heap
    heapEvent->book(1, 1);
    std::cout << "calling delete\n";
    delete heapEvent;

    std::cout << "zero-row event:\n";
    Event empty("EmptyEvent", 0, 50);
    std::cout << "  book (0,0) on zero rows: " << empty.book(0, 0) << '\n';

    std::cout << "main ends\n";
}
