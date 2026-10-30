// Q3 - the developer's original three functions (this file is SUPPOSED to fail)
#include <iostream>

double charge(double weight)                                   { return weight * 50; }
double charge(double weight, bool express)                     { return weight * 50 + (express ? 40 : 0); }
double charge(double weight, bool express = false, bool insured = false)
{
    return weight * 50 + (express ? 40 : 0) + (insured ? 25 : 0);
}

int main()
{
    std::cout << charge(2.0) << '\n';          // 1 or 3 ?
    std::cout << charge(2.0, true) << '\n';    // 2 or 3 ?
    std::cout << charge(2.0, true, true) << '\n';   // only 3 fits, this one is fine
}
