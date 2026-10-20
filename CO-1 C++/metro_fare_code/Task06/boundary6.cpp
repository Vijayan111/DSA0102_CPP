// Task 6 extra - journeys at exactly 10:00 and 20:00 plus a switch with no matching case
#include <iostream>
enum class Zone { Inner, Middle, Outer };
constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;

constexpr bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

long long fare(Zone z, bool peak)
{
    long long base = 0;
    switch (z) {
        case Zone::Inner:  base = BASE_PAISE[0]; break;
        case Zone::Middle: base = BASE_PAISE[1]; break;
        case Zone::Outer:  base = BASE_PAISE[2]; break;
        default: return -1;
    }
    if (peak) base += base * PEAK_SURCHARGE_PERCENT / 100;
    return base;
}

// alternative: array indexed by zone, no switch
constexpr long long FARE[] = {1000, 2000, 3000};
long long fareTable(Zone z, bool peak)
{
    long long base = FARE[static_cast<int>(z)];
    return peak ? base + base * PEAK_SURCHARGE_PERCENT / 100 : base;
}

int main()
{
    int hours[] = {7, 8, 9, 10, 16, 17, 19, 20};
    for (int h : hours)
        std::cout << "hour " << h << " Inner fare paise = " << fare(Zone::Inner, isPeak(h))
                  << (isPeak(h) ? "  (peak)" : "  (off-peak)") << '\n';
    std::cout << "invalid zone value 7 -> " << fare(static_cast<Zone>(7), false) << '\n';
    std::cout << "table version Outer peak = " << fareTable(Zone::Outer, true) << '\n';
}
