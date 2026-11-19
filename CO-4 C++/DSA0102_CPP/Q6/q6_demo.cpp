// Q6 Stage 5 - demonstration with the four original vehicle types
#include "fleet.h"

int main()
{
    Date today(2, 11, 2026);
    Fleet fleet;
    fleet.add(new Bicycle("BC-101", 100));
    fleet.add(new TwoWheeler("TN30A1234", 400, 8, Date(1, 12, 2026)));
    fleet.add(new Car("TN30B5678", 1200, 5, 30, Date(15, 1, 2027)));
    fleet.add(new ElectricCar("TN30E9012", 1500, 5, 36, 40, Date(20, 12, 2026)));
    fleet.add(new TwoWheeler("TN30A0000", 400, 9, Date(10, 10, 2026)));    // service overdue

    std::cout << "Fleet:\n";           fleet.list();
    std::cout << "\nRenting:\n";
    fleet.rent("BC-101", today);  fleet.rent("TN30A1234", today);  fleet.rent("TN30B5678", today);
    fleet.rent("TN30E9012", today);  fleet.rent("TN30A0000", today);  fleet.rent("BC-101", today);
    std::cout << "\nReturning:\n";
    double total = 0, b;
    if ((b = fleet.giveBack("BC-101", 2, 0, 0)) > 0) total += b;
    if ((b = fleet.giveBack("TN30A1234", 3, 1, 4)) > 0) total += b;
    if ((b = fleet.giveBack("TN30B5678", 4, 2, 25)) > 0) total += b;
    if ((b = fleet.giveBack("TN30E9012", 2, 1, 20)) > 0) total += b;
    fleet.giveBack("TN30A0000", 1, 0, 0);                                  // never rented
    std::cout << "\nTotal collected: Rs " << total << '\n';
}
