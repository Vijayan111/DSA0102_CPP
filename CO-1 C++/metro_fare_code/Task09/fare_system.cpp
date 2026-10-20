// Task 9 - complete fare logic + table-driven tests
#include <iomanip>
#include <iostream>
#include <string>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };
enum class Category { Adult, Student, Senior };

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_PERCENT = 20;
constexpr int CONCESSION_PERCENT = 50;          // assumption: students and seniors pay half
constexpr long long MIN_BALANCE_PAISE = 5000;

constexpr bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

bool zoneFromCode(int code, Zone& z)
{
    if (code < 0 || code > 2) return false;
    z = static_cast<Zone>(code);
    return true;
}

long long fare(Zone z, int hour, Category c)
{
    long long f = BASE_PAISE[static_cast<int>(z)];
    if (isPeak(hour)) f += f * PEAK_PERCENT / 100;
    if (c != Category::Adult) f = f * (100 - CONCESSION_PERCENT) / 100;
    return f;
}

class SmartCard {
public:
    explicit SmartCard(long long b) : balance_{b} {}
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    bool recharge(long long p) { if (p <= 0) return false; balance_ += p; return true; }
    long long balance() const { return balance_; }
private:
    long long balance_;
};

struct TestCase {
    const char* name; int zoneCode; int hour; Category cat; long long balance;
    long long expectedFare; bool expectedAllowed;
};

int main()
{
    const TestCase tests[] = {
        {"Inner off-peak",         0, 12, Category::Adult,   20000, 1000, true},
        {"Inner peak",             0,  9, Category::Adult,   20000, 1200, true},
        {"Middle off-peak",        1, 12, Category::Adult,   20000, 2000, true},
        {"Middle peak",            1, 18, Category::Adult,   20000, 2400, true},
        {"Outer off-peak",         2, 12, Category::Adult,   20000, 3000, true},
        {"Outer peak",             2,  8, Category::Adult,   20000, 3600, true},
        {"Boundary 7:xx (before)", 0,  7, Category::Adult,   20000, 1000, true},
        {"Boundary 08:00",         0,  8, Category::Adult,   20000, 1200, true},
        {"Boundary 10:00",         0, 10, Category::Adult,   20000, 1000, true},
        {"Boundary 16:xx (before)",0, 16, Category::Adult,   20000, 1000, true},
        {"Boundary 17:00",         0, 17, Category::Adult,   20000, 1200, true},
        {"Boundary 20:00",         0, 20, Category::Adult,   20000, 1000, true},
        {"Leaves exactly Rs 50",   0, 12, Category::Adult,    6000, 1000, true},
        {"Leaves Rs 49.99",        0, 12, Category::Adult,    5999, 1000, false},
        {"Student Outer off-peak", 2, 12, Category::Student, 20000, 1500, true},
        {"Senior Middle peak",     1,  9, Category::Senior,  20000, 1200, true},
    };

    int pass = 0, total = 0;
    std::cout << std::left << std::setw(26) << "Case" << std::setw(10) << "Exp fare" << std::setw(10)
              << "Act fare" << std::setw(8) << "Exp ok" << std::setw(8) << "Act ok" << "Result\n";
    for (const TestCase& t : tests) {
        Zone z{};
        zoneFromCode(t.zoneCode, z);
        long long f = fare(z, t.hour, t.cat);
        SmartCard card{t.balance};
        bool allowed = card.canTravel(f);
        bool ok = (f == t.expectedFare) && (allowed == t.expectedAllowed);
        ++total; if (ok) ++pass;
        std::cout << std::left << std::setw(26) << t.name << std::setw(10) << t.expectedFare << std::setw(10) << f
                  << std::setw(8) << std::boolalpha << t.expectedAllowed << std::setw(8) << allowed
                  << (ok ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "\n--- invalid cases ---\n";
    Zone z{};
    bool bad1 = zoneFromCode(5, z);
    std::cout << "unknown zone code 5 accepted? " << std::boolalpha << bad1 << (bad1 ? "  FAIL" : "  PASS") << '\n';
    total++; if (!bad1) pass++;
    SmartCard c2{10000};
    bool bad2 = c2.recharge(-200);
    std::cout << "negative recharge accepted?   " << bad2 << (bad2 ? "  FAIL" : "  PASS") << '\n';
    total++; if (!bad2) pass++;

    std::cout << "\n--- five journeys checked by hand ---\n";
    SmartCard card{50000};                                   // Rs 500.00
    struct J { const char* what; Zone z; int hour; Category c; long long hand; };
    J js[] = {
        {"Inner 09:00 adult  (peak)",    Zone::Inner,  9, Category::Adult,   1200},
        {"Middle 12:00 adult",           Zone::Middle, 12, Category::Adult,  2000},
        {"Outer 18:00 adult  (peak)",    Zone::Outer, 18, Category::Adult,   3600},
        {"Outer 14:00 student",          Zone::Outer, 14, Category::Student, 1500},
        {"Middle 08:00 senior (peak)",   Zone::Middle, 8, Category::Senior,  1200},
    };
    long long sum = 0;
    for (const J& j : js) {
        long long f = fare(j.z, j.hour, j.c);
        card.deduct(f);
        sum += f;
        std::cout << std::left << std::setw(30) << j.what << "hand " << std::setw(6) << j.hand << " program " << f
                  << (f == j.hand ? "  PASS" : "  FAIL") << '\n';
        ++total; if (f == j.hand) ++pass;
    }
    std::cout << "total paise = " << sum << " (hand: 9500)  final balance = " << card.balance() << " (hand: 40500)\n";
    std::cout << "\nPASSED " << pass << " of " << total << '\n';
}
