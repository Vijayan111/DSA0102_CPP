// Task 7 - object-oriented version: SmartCard keeps balance private
#include <iostream>

class SmartCard {
public:
    static constexpr long long MIN_BALANCE_PAISE = 5000;
    explicit SmartCard(long long openingPaise) : balance_{openingPaise >= 0 ? openingPaise : 0} {}

    bool canTravel(long long farePaise) const
    {
        return farePaise >= 0 && balance_ - farePaise >= MIN_BALANCE_PAISE;
    }
    bool deduct(long long farePaise)            // the only way to reduce the balance
    {
        if (!canTravel(farePaise)) return false;
        balance_ -= farePaise;
        return true;
    }
    bool recharge(long long paise)              // negative recharge rejected
    {
        if (paise <= 0) return false;
        balance_ += paise;
        return true;
    }
    long long balance() const { return balance_; }
private:
    long long balance_;
};

enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_PERCENT = 20;

long long fare(Zone z, bool peak)
{
    long long base = BASE_PAISE[static_cast<int>(z)];
    return peak ? base + base * PEAK_PERCENT / 100 : base;
}

int main()
{
    SmartCard card{10000};
    struct Trip { Zone z; bool peak; };
    Trip trips[] = {{Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}};
    for (const Trip& t : trips) {
        long long f = fare(t.z, t.peak);
        if (card.deduct(f)) std::cout << "paid " << f << " left " << card.balance() << '\n';
        else std::cout << "denied, left " << card.balance() << '\n';
    }
    std::cout << "negative recharge accepted? " << std::boolalpha << card.recharge(-500) << '\n';
    std::cout << "deduct(9000) accepted? " << card.deduct(9000) << "  balance " << card.balance() << '\n';
    // card.balance_ = -5;   // compile error: 'balance_' is private
}
