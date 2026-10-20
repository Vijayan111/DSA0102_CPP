// Task 10 - network totals with double rupees, long long paise, int paise, float
// (C++11 compatible: no generic lambda)
#include <chrono>
#include <iomanip>
#include <iostream>

typedef std::chrono::steady_clock::time_point TimePoint;

// 12 fares in paise: 3 zones x peak/off-peak, adult and 30% concession (assumed rate for this experiment)
constexpr long long BASE[] = {1000, 2000, 3000};

long long farePaise(int zone, bool peak, bool concession)
{
    long long f = BASE[zone];
    if (peak) f += f * 20 / 100;
    if (concession) f = f * 70 / 100;
    return f;
}
// the "hurried" way: everything in double rupees
double fareRupeesDouble(int zone, bool peak, bool concession)
{
    double f = BASE[zone] / 100.0;
    if (peak) f = f * 1.2;
    if (concession) f = f * 0.7;
    return f;
}

// milliseconds between two time points
double ms(TimePoint x, TimePoint y)
{
    return std::chrono::duration<double, std::milli>(y - x).count();
}

int main()
{
    long long counts[] = {20000, 500000, 3000000};
    std::cout << std::fixed;
    for (long long n : counts) {
        long long paise = 0; double rupees = 0.0; float fl = 0.0f; unsigned wrap = 0;
        for (long long i = 0; i < n; ++i) {
            int zone = static_cast<int>(i % 3);
            bool peak = (i / 3) % 2 == 1;
            bool conc = (i / 6) % 2 == 1;
            long long f = farePaise(zone, peak, conc);
            paise += f;
            rupees += fareRupeesDouble(zone, peak, conc);
            fl += static_cast<float>(f) / 100.0f;
            wrap += static_cast<unsigned>(f);          // 32-bit paise total, wrap-around shown with unsigned
        }
        double exactRs = paise / 100.0;
        std::cout << "n = " << n << '\n';
        std::cout << "  long long paise : " << paise << "  (Rs " << std::setprecision(2) << exactRs << ")\n";
        std::cout << "  double rupees   : " << std::setprecision(8) << rupees
                  << "  diff vs exact = " << std::scientific << std::setprecision(3) << (rupees - exactRs) << std::fixed << '\n';
        std::cout << "  double -> paise (truncate) : " << static_cast<long long>(rupees * 100)
                  << "  error " << static_cast<long long>(rupees * 100) - paise << " paise\n";
        std::cout << "  float rupees    : " << std::setprecision(2) << fl << "  diff = " << (fl - exactRs) << '\n';
        std::cout << "  32-bit int paise: " << static_cast<int>(wrap)
                  << (paise > 2147483647LL ? "  <-- OVERFLOW" : "  (fits)") << '\n';
    }

    // timing per addition
    const long long N = 200000000;
    TimePoint t0 = std::chrono::steady_clock::now();
    long long a = 0; for (long long i = 0; i < N; ++i) a += (i & 7) + 1000;
    TimePoint t1 = std::chrono::steady_clock::now();
    double d = 0; for (long long i = 0; i < N; ++i) d += static_cast<double>((i & 7) + 1000);
    TimePoint t2 = std::chrono::steady_clock::now();
    int s = 0; for (long long i = 0; i < N; ++i) s += static_cast<int>((i & 7) + 1000);
    TimePoint t3 = std::chrono::steady_clock::now();
    std::cout << std::setprecision(1) << "time for " << N << " additions (ms): long long " << ms(t0, t1)
              << ", double " << ms(t1, t2) << ", int " << ms(t2, t3) << "   [sinks: " << a << ' ' << d << ' ' << s << "]\n";
}
