// Q3 - Courier Charge Calculator: default arguments + overloading, no ambiguity
#include <iostream>
#include <iomanip>

const double RATE_PER_KG  = 50.0;
const double EXPRESS_FEE  = 40.0;
const double INSURANCE_FEE = 25.0;

struct Parcel {
    double kg;
    bool express;
    bool insured;
};

// weight in kg (double)
double charge(double kg, bool express = false, bool insured = false)
{
    std::cout << "[double kg ] ";
    return kg * RATE_PER_KG + (express ? EXPRESS_FEE : 0) + (insured ? INSURANCE_FEE : 0);
}

// weight in grams (int)
double charge(int grams, bool express = false, bool insured = false)
{
    std::cout << "[int grams ] ";
    return (grams / 1000.0) * RATE_PER_KG + (express ? EXPRESS_FEE : 0) + (insured ? INSURANCE_FEE : 0);
}

// a whole Parcel object
double charge(const Parcel& p)
{
    std::cout << "[Parcel    ] ";
    return p.kg * RATE_PER_KG + (p.express ? EXPRESS_FEE : 0) + (p.insured ? INSURANCE_FEE : 0);
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "charge(2)                      -> " << charge(2) << '\n';
    std::cout << "charge(2.0)                    -> " << charge(2.0) << '\n';
    std::cout << "charge(2.0f)                   -> " << charge(2.0f) << '\n';
    std::cout << "charge(1500, true)             -> " << charge(1500, true) << '\n';
    std::cout << "charge(1.5, true, true)        -> " << charge(1.5, true, true) << '\n';
    std::cout << "charge(Parcel{3.0,false,true}) -> " << charge(Parcel{3.0, false, true}) << '\n';
}
