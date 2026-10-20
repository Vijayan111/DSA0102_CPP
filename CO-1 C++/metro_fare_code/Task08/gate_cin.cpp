// Task 8 - reading with cin >> and recovering from bad input
#include <iomanip>
#include <iostream>
#include <limits>

void printRupees(long long paise)
{
    std::cout << "Rs " << paise / 100 << '.' << std::setw(2) << std::setfill('0') << paise % 100
              << std::setfill(' ');
}

// keeps asking until a number inside [lo, hi] is typed; returns false only on end of input
bool readInt(const char* prompt, int lo, int hi, int& out)
{
    while (true) {
        std::cout << prompt;
        if (std::cin >> out) {
            if (out >= lo && out <= hi) return true;
            std::cout << "  out of range (" << lo << ".." << hi << "), try again\n";
        } else {
            if (std::cin.eof()) return false;
            std::cin.clear();                                              // reset the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // throw away the bad line
            std::cout << "  not a number, try again\n";
        }
    }
}

int main()
{
    int zone = 0, hour = 0, balanceRs = 0;
    if (!readInt("zone (0=Inner 1=Middle 2=Outer): ", 0, 2, zone)) return 1;
    if (!readInt("hour (0-23): ", 0, 23, hour)) return 1;
    if (!readInt("card balance in Rs (0-100000): ", 0, 100000, balanceRs)) return 1;

    constexpr long long BASE[] = {1000, 2000, 3000};
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long f = peak ? BASE[zone] + BASE[zone] * 20 / 100 : BASE[zone];
    long long bal = balanceRs * 100LL;
    bool ok = bal - f >= 5000;

    std::cout << "\n===== JOURNEY REPORT =====\n";
    std::cout << std::left << std::setw(10) << "Zone" << std::right << std::setw(6) << zone << '\n';
    std::cout << std::left << std::setw(10) << "Hour" << std::right << std::setw(6) << hour << '\n';
    std::cout << std::left << std::setw(10) << "Peak" << std::right << std::setw(6) << (peak ? "yes" : "no") << '\n';
    std::cout << std::left << std::setw(10) << "Fare" << std::right << std::setw(14); printRupees(f); std::cout << '\n';
    std::cout << std::left << std::setw(10) << "Status" << std::right << std::setw(14) << (ok ? "ALLOWED" : "DENIED") << '\n';
    if (ok) { std::cout << std::left << std::setw(10) << "Balance" << std::right << std::setw(14); printRupees(bal - f); std::cout << '\n'; }
    // fixed + setprecision shown on a double, only for display
    std::cout << std::fixed << std::setprecision(2) << "(display only) fare as double: " << f / 100.0 << '\n';
}
