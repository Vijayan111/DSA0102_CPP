// Q5 - my own BusTicket design: static capacity, static counters, array of objects, function called twice
#include <iostream>
#include <string>

class BusTicket {
    static int issued;                       // seats given out (one copy for the whole class)
    static int waiting;                      // tickets on the waiting list
    static const int CAPACITY = 3;
    int seat;                                // 0 = waiting list
    std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY) seat = ++issued;
        else ++waiting;
    }
    static int seatsIssued()  { return issued; }     // no 'this', so it can only touch static members
    static int waitingCount() { return waiting; }
    void print() const
    {
        std::cout << "  " << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n';
    }
};

int BusTicket::issued  = 0;
int BusTicket::waiting = 0;

void bookTwo(const std::string& a, const std::string& b)
{
    BusTicket t1(a), t2(b);                  // local objects, destroyed at the closing brace
    t1.print();
    t2.print();
}

int main()
{
    std::cout << "Tickets before anything is created: issued = " << BusTicket::seatsIssued() << " (no object needed)\n\n";

    std::cout << "bookTwo called the first time:\n";
    bookTwo("Eswar", "Farah");
    std::cout << "  after call 1 -> issued = " << BusTicket::seatsIssued() << ", waiting = " << BusTicket::waitingCount() << "\n\n";

    std::cout << "bookTwo called the second time:\n";
    bookTwo("Gopi", "Hema");
    std::cout << "  after call 2 -> issued = " << BusTicket::seatsIssued() << ", waiting = " << BusTicket::waitingCount() << "\n\n";

    std::cout << "Array of 6 more tickets (capacity already used up):\n";
    BusTicket more[6] = {BusTicket("P1"), BusTicket("P2"), BusTicket("P3"),
                         BusTicket("P4"), BusTicket("P5"), BusTicket("P6")};
    for (const BusTicket& t : more) t.print();
    std::cout << "  final -> issued = " << BusTicket::seatsIssued() << ", waiting = " << BusTicket::waitingCount() << '\n';
}
