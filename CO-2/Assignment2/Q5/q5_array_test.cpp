// Q5 - array of tickets larger than the capacity, fresh program so the seat numbers start from 1
#include <iostream>
#include <string>

class BusTicket {
    static int issued;
    static int waiting;
    static const int CAPACITY = 3;
    int seat;
    std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY) seat = ++issued;
        else ++waiting;
    }
    static int seatsIssued()  { return issued; }
    static int waitingCount() { return waiting; }
    void print() const
    {
        std::cout << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n';
    }
};
int BusTicket::issued = 0;
int BusTicket::waiting = 0;

int main()
{
    BusTicket trip[6] = {BusTicket("Asha"), BusTicket("Bala"), BusTicket("Chitra"),
                         BusTicket("Dev"), BusTicket("Esha"), BusTicket("Farook")};
    for (const BusTicket& t : trip) t.print();
    std::cout << "Issued: " << BusTicket::seatsIssued() << "  Waiting list: " << BusTicket::waitingCount() << '\n';
}
