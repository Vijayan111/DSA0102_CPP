// Q6 alternative: ONE Vehicle class with a type code and a switch in charge()
#include <chrono>
#include <iostream>
#include "vehicles.h"

enum VType { BICYCLE, TWO_WHEELER, CAR, ELECTRIC_CAR };

class VehicleS {
    std::string regNo; double dailyRate; bool rented = false;
    VType type;
    double level; Date serviceDue; int seats; double battery;      // unused by some types
public:
    VehicleS(VType t, double rate, double lvl, int s, double bat)
        : regNo("X"), dailyRate(rate), type(t), level(lvl), serviceDue(1, 1, 2027), seats(s), battery(bat) {}
    double charge(int days, int late, double used) const
    {
        double base = days * dailyRate, lt = late * dailyRate * LATE_FACTOR;
        switch (type) {
            case BICYCLE:      return base + lt;
            case TWO_WHEELER:  return base + used * FUEL_PRICE + HELMET_FEE + lt;
            case CAR:          return base + used * FUEL_PRICE + days * INSURANCE_PER_DAY + lt;
            case ELECTRIC_CAR: return base + used * KWH_PRICE + days * INSURANCE_PER_DAY + lt;
        }
        return 0;
    }
};

template <class F> double bestOf(F f)
{
    double best = 1e18;
    for (int r = 0; r < 11; ++r) {
        auto t0 = std::chrono::steady_clock::now(); f();
        auto t1 = std::chrono::steady_clock::now();
        double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
        if (ms < best) best = ms;
    }
    return best;
}

int main()
{
    const int N = 1024; const long CALLS = 10000000;
    Vehicle* h[N]; VehicleS* s[N];
    for (int i = 0; i < N; ++i) {
        int k = (i * 5 + i / 3) % 4; double rate = 100 + i % 50;
        Date due(1, 1, 2027);
        if (k == 0)      { h[i] = new Bicycle("a", rate);                    s[i] = new VehicleS(BICYCLE, rate, 0, 0, 0); }
        else if (k == 1) { h[i] = new TwoWheeler("b", rate, 5, due);          s[i] = new VehicleS(TWO_WHEELER, rate, 5, 0, 0); }
        else if (k == 2) { h[i] = new Car("c", rate, 5, 20, due);             s[i] = new VehicleS(CAR, rate, 20, 5, 0); }
        else             { h[i] = new ElectricCar("d", rate, 5, 30, 40, due); s[i] = new VehicleS(ELECTRIC_CAR, rate, 30, 5, 40); }
    }
    std::cout << "sizeof: Bicycle=" << sizeof(Bicycle) << " TwoWheeler=" << sizeof(TwoWheeler) << " Car=" << sizeof(Car)
              << " ElectricCar=" << sizeof(ElectricCar) << "  |  single VehicleS=" << sizeof(VehicleS) << '\n';
    volatile double sink = 0; double sa = 0, sb = 0;
    double ta = bestOf([&] { double t = 0; for (long i = 0; i < CALLS; ++i) t += h[i & (N - 1)]->charge(3, 1, 4); sa = t; sink = t; });
    double tb = bestOf([&] { double t = 0; for (long i = 0; i < CALLS; ++i) t += s[i & (N - 1)]->charge(3, 1, 4); sb = t; sink = t; });
    std::cout << "10,000,000 charge() calls, best of 11:  virtual " << ta << " ms,  switch " << tb << " ms,  same total? "
              << (sa == sb ? "yes" : "NO") << '\n';
    for (int i = 0; i < N; ++i) { delete h[i]; delete s[i]; }
}
