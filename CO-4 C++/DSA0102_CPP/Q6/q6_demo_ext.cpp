// Q6 Stage 5 - same program after adding the NEW type ElectricBus (only this file and electric_bus.h are new)
#include "electric_bus.h"
#include "fleet.h"

int main()
{
    Date today(2, 11, 2026);
    Fleet fleet;
    fleet.add(new Bicycle("BC-101", 100));
    fleet.add(new TwoWheeler("TN30A1234", 400, 8, Date(1, 12, 2026)));
    fleet.add(new Car("TN30B5678", 1200, 5, 30, Date(15, 1, 2027)));
    fleet.add(new ElectricCar("TN30E9012", 1500, 5, 36, 40, Date(20, 12, 2026)));
    fleet.add(new TwoWheeler("TN30A0000", 400, 9, Date(10, 10, 2026)));
    fleet.add(new ElectricBus("TN30BUS1", 5000, 40, 200, 300, Date(5, 3, 2027)));   // <-- the only new line

    std::cout << "Fleet:\n";           fleet.list();
    std::cout << "\nRenting:\n";
    fleet.rent("BC-101", today);  fleet.rent("TN30A1234", today);  fleet.rent("TN30B5678", today);
    fleet.rent("TN30E9012", today);  fleet.rent("TN30A0000", today);  fleet.rent("TN30BUS1", today);
    std::cout << "\nReturning:\n";
    double total = 0, b;
    if ((b = fleet.giveBack("BC-101", 2, 0, 0)) > 0) total += b;
    if ((b = fleet.giveBack("TN30A1234", 3, 1, 4)) > 0) total += b;
    if ((b = fleet.giveBack("TN30B5678", 4, 2, 25)) > 0) total += b;
    if ((b = fleet.giveBack("TN30E9012", 2, 1, 20)) > 0) total += b;
    if ((b = fleet.giveBack("TN30BUS1", 1, 0, 60)) > 0) total += b;
    std::cout << "\nTotal collected: Rs " << total << '\n';
}
