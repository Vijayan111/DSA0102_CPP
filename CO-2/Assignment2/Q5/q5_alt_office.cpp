// Q5 alternative: a TicketOffice object keeps the counter, so two buses can run at once
#include <iostream>
#include <string>

class TicketOffice {
public:
    int issued = 0;
    int capacity;
    explicit TicketOffice(int cap) : capacity(cap) {}
};

class BusTicket {
    int seat;
    std::string name;
public:
    BusTicket(const std::string& n, TicketOffice& office) : seat(0), name(n)
    {
        if (office.issued < office.capacity) seat = ++office.issued;
    }
    void print() const { std::cout << "  " << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n'; }
};

int main()
{
    TicketOffice busA(2), busB(3);          // two buses, two independent counters
    BusTicket a1("Asha", busA), a2("Bala", busA), a3("Chitra", busA);
    BusTicket b1("Dev", busB), b2("Esha", busB);
    std::cout << "Bus A (2 seats):\n"; a1.print(); a2.print(); a3.print();
    std::cout << "Bus B (3 seats):\n"; b1.print(); b2.print();
    std::cout << "issued A = " << busA.issued << ", issued B = " << busB.issued << '\n';
}
