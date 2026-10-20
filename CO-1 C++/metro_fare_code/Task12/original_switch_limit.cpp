// Task 12 B - what happens when the ORIGINAL switch design meets the new rules
#include <iostream>
enum class Zone { Inner, Middle, Outer };           // original: only three zones
constexpr int BASE_PAISE[] = {1000, 2000, 3000};    // array size 3

long long fareOld(Zone z, bool peak)
{
    long long base = 0;
    switch (z) {
        case Zone::Inner:  base = BASE_PAISE[0]; break;
        case Zone::Middle: base = BASE_PAISE[1]; break;
        case Zone::Outer:  base = BASE_PAISE[2]; break;
        default: return -1;                          // a 4th zone lands here
    }
    if (peak) base += base * 20 / 100;               // no place for "weekend" or "pass"
    return base;
}
int main()
{
    std::cout << "Airport (value 3) with old code -> " << fareOld(static_cast<Zone>(3), false)
              << "   (should be 6000)\n";
    std::cout << "Airport weekday peak with old code -> " << fareOld(static_cast<Zone>(3), true)
              << "   (should be 7200)\n";
    std::cout << "Outer weekend peak-hour with old code -> " << fareOld(Zone::Outer, true)
              << "   (should be 2700: weekend 10% off, no surcharge)\n";
}
