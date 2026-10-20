// Task 12 - Metro Fare Management System
// Four zones, peak-hour surcharge, weekend discount, monthly pass

#include <iostream>
#include <iomanip>

enum class Zone { Inner, Middle, Outer, Express, Count };
enum class Category { Adult, Student, Senior };

// Fare constants (in paise)
const long long BASE_PAISE[static_cast<int>(Zone::Count)] =
    {1000, 2000, 3000, 6000};

const int PEAK_PERCENT = 20;
const int WEEKEND_DISCOUNT_PERCENT = 10;
const int CONCESSION_PERCENT = 50;
const long long MIN_BALANCE_PAISE = 5000;

// Check peak hours
bool isPeak(int hour)
{
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

// Calculate fare based on time and day
inline long long applyTimeRule(long long base, bool peak, bool weekend)
{
    if (weekend)
        return base * (100 - WEEKEND_DISCOUNT_PERCENT) / 100;

    if (peak)
        return base * (100 + PEAK_PERCENT) / 100;

    return base;
}

// Apply student and senior concession
inline long long applyConcession(long long f, Category c)
{
    if (c == Category::Adult)
        return f;

    return f * (100 - CONCESSION_PERCENT) / 100;
}

// Monthly metro pass
class Pass
{
public:
    Pass(Zone a, Zone b, int month)
        : a_(a), b_(b), month_(month)
    {
    }

    bool covers(Zone zone, int month) const
    {
        return month == month_ &&
               (zone == a_ || zone == b_);
    }

private:
    Zone a_, b_;
    int month_;
};

// Metro smart card
class SmartCard
{
public:
    explicit SmartCard(long long balance)
        : balance_(balance)
    {
    }

    bool canTravel(long long f) const
    {
        return f >= 0 &&
               balance_ - f >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long f)
    {
        if (!canTravel(f))
            return false;

        balance_ -= f;
        return true;
    }

    long long balance() const
    {
        return balance_;
    }

private:
    long long balance_;
};

// Metro journey details
struct Journey
{
    Zone zone;
    int hour;
    bool weekend;
    Category category;
    int month;
};

// Calculate metro fare
// Returns 0 if the monthly pass covers the journey
// Returns -1 for an invalid zone
long long fare(const Journey& j, const Pass* pass)
{
    int zi = static_cast<int>(j.zone);

    if (zi < 0 || zi >= static_cast<int>(Zone::Count))
        return -1;

    if (pass != NULL && pass->covers(j.zone, j.month))
        return 0;

    long long f = BASE_PAISE[zi];

    f = applyTimeRule(f, isPeak(j.hour), j.weekend);
    f = applyConcession(f, j.category);

    return f;
}

int main()
{
    struct Test
    {
        const char* name;
        Journey journey;
        bool usePass;
        long long expected;
    };

    // Monthly pass for Inner and Middle zones in October
    Pass pass(Zone::Inner, Zone::Middle, 10);

    const Test tests[] =
    {
        {"Express metro off-peak",
         {Zone::Express, 12, false, Category::Adult, 10},
         false, 6000},

        {"Express metro peak",
         {Zone::Express, 9, false, Category::Adult, 10},
         false, 7200},

        {"Express metro weekend",
         {Zone::Express, 12, true, Category::Adult, 10},
         false, 5400},

        {"Express weekend peak hour",
         {Zone::Express, 9, true, Category::Adult, 10},
         false, 5400},

        {"Inner metro weekend",
         {Zone::Inner, 8, true, Category::Adult, 10},
         false, 900},

        {"Outer metro student",
         {Zone::Outer, 12, true, Category::Student, 10},
         false, 1350},

        {"Pass: Inner covered",
         {Zone::Inner, 9, false, Category::Adult, 10},
         true, 0},

        {"Pass: Middle covered",
         {Zone::Middle, 18, false, Category::Adult, 10},
         true, 0},

        {"Pass: Outer not covered",
         {Zone::Outer, 12, false, Category::Adult, 10},
         true, 3000},

        {"Pass: Express not covered",
         {Zone::Express, 12, false, Category::Adult, 10},
         true, 6000},

        {"Pass: Wrong month",
         {Zone::Inner, 12, false, Category::Adult, 11},
         true, 1000},

        {"Invalid metro zone",
         {static_cast<Zone>(9), 12, false, Category::Adult, 10},
         false, -1}
    };

    int ok = 0;
    int n = sizeof(tests) / sizeof(tests[0]);

    std::cout << std::left
              << std::setw(32) << "Metro Journey"
              << std::setw(12) << "Expected"
              << std::setw(12) << "Actual"
              << "Result\n";

    std::cout << "------------------------------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        long long actual = fare(
            tests[i].journey,
            tests[i].usePass ? &pass : NULL
        );

        bool good = actual == tests[i].expected;

        if (good)
            ok++;

        std::cout << std::left
                  << std::setw(32) << tests[i].name
                  << std::setw(12) << tests[i].expected
                  << std::setw(12) << actual
                  << (good ? "PASS" : "FAIL")
                  << '\n';
    }

    // Test smart-card minimum balance
    SmartCard card(11000);

    Journey metroJourney =
        {Zone::Express, 12, false, Category::Adult, 10};

    bool first = card.deduct(fare(metroJourney, NULL));
    bool second = card.deduct(fare(metroJourney, NULL));

    std::cout << "\nMetro Smart Card Tests\n";

    std::cout << "First journey allowed: "
              << std::boolalpha << first
              << ", Balance: " << card.balance()
              << " paise\n";

    std::cout << "Second journey allowed: "
              << second
              << ", Balance: " << card.balance()
              << " paise\n";

    n += 2;

    if (first)
        ok++;

    if (!second)
        ok++;

    std::cout << "\nPASSED " << ok
              << " OF " << n << " TESTS\n";

    return 0;
}
