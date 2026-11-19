// Q4: 1,000,000 additions of Rs 0.10 with double and with Money (paise)
#include <chrono>
#include <iomanip>
#include <iostream>

struct Money { long long paise; };

int main()
{
    const int N = 1000000;
    double d = 0.0;
    Money m{0};
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) d += 0.10;
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) m.paise += 10;
    auto t2 = std::chrono::steady_clock::now();

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "expected total        : Rs 100000.00\n";
    std::cout << "double sum            : " << d << '\n';
    std::cout << "double error          : " << d - 100000.0 << '\n';
    std::cout << "double == 100000.0 ?  : " << std::boolalpha << (d == 100000.0) << '\n';
    std::cout << "Money total (paise)   : " << m.paise << " -> Rs " << m.paise / 100 << '.' << m.paise % 100 << "0\n";
    std::cout << "Money == 10000000 ?   : " << (m.paise == 10000000) << '\n';
    std::cout << std::setprecision(3);
    std::cout << "time double: " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms,  time Money: "
              << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms (-O0)\n";
}
