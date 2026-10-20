// Task 4 - same program with explicit conversions and brace initialisation
#include <iostream>
int main()
{
    int a{7}, b{2};
    double c{static_cast<double>(a / b)};          // integer division on purpose
    double d{static_cast<double>(a) / b};          // real division
    std::cout << c << ' ' << d << '\n';

    char ch{static_cast<char>('A' + 2)};
    std::cout << ch << ' ' << static_cast<int>(ch) + 1 << '\n';

    bool flag{5 != 0};
    std::cout << flag << ' ' << std::boolalpha << flag << '\n';

    unsigned int u{1};
    int s{-1};
    bool less{s < 0 || static_cast<unsigned int>(s) < u};   // sign checked first
    std::cout << (less ? "s < u" : "s >= u") << '\n';

    // fare example: 20% surcharge on integer paise, no double involved
    long long base{3000};
    long long peakFare{base + base * 20 / 100};
    std::cout << "peak fare paise = " << peakFare << '\n';
}
