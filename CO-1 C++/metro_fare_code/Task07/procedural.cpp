// Task 7 - procedural version: global balance, free functions
#include <iostream>

constexpr long long MIN_BALANCE_PAISE = 5000;
long long balance = 10000;                 // global: any function can change it

long long fare(int zone, bool peak)
{
    long long base = (zone == 0) ? 1000 : (zone == 1) ? 2000 : 3000;
    return peak ? base + base * 20 / 100 : base;
}
bool canTravel(long long bal, long long f) { return bal - f >= MIN_BALANCE_PAISE; }

int main()
{
    int zones[] = {0, 2, 1};
    bool peaks[] = {false, true, false};
    for (int i = 0; i < 3; ++i) {
        long long f = fare(zones[i], peaks[i]);
        if (canTravel(balance, f)) { balance -= f; std::cout << "paid " << f << " left " << balance << '\n'; }
        else std::cout << "denied, left " << balance << '\n';
    }
    balance -= 9000;       // nothing stops this line - the card goes below the minimum (even negative)
    std::cout << "after careless code: " << balance << '\n';
}
