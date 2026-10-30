// Q3 alternative: ONE function that takes a Parcel with optional fields (no overloads)
#include <iostream>
#include <iomanip>

struct Parcel {
    double kg = 0;
    bool express = false;
    bool insured = false;
    bool fragile = false;        // a new option costs one line here ...
};

double charge(const Parcel& p)
{
    double c = p.kg * 50.0;
    if (p.express) c += 40;
    if (p.insured) c += 25;
    if (p.fragile) c += 15;      // ... and one line here; no new overload, no new default argument
    return c;
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    Parcel a; a.kg = 2.0;
    Parcel b; b.kg = 1.5; b.express = true; b.insured = true;
    Parcel c; c.kg = 3.0; c.fragile = true;
    std::cout << charge(a) << '\n' << charge(b) << '\n' << charge(c) << '\n';
}
