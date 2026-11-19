// Q3: the heap event is never deleted -> LeakSanitizer
#include <cstring>
#include <iostream>

class Event {
    int rows, seats; char** seat;
public:
    Event(int r, int s) : rows(r), seats(s), seat(new char*[r])
    {
        for (int i = 0; i < rows; ++i) { seat[i] = new char[seats]; std::memset(seat[i], '.', seats); }
    }
    ~Event() { for (int i = 0; i < rows; ++i) delete[] seat[i]; delete[] seat; }
};

void setUpEvent()
{
    Event* e = new Event(10, 20);
    std::cout << "event created at " << (e != nullptr) << ", forgot to delete\n";
    // delete e;      <- missing
}

int main()
{
    setUpEvent();
    std::cout << "back in main\n";
}
