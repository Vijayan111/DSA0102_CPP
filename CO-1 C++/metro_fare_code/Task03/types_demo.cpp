// Task 3 - data types, sizeof, ranges, precision and overflow evidence
#include <climits>
#include <cfloat>
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "---- sizeof on this system ----\n";
    std::cout << "bool        " << sizeof(bool) << '\n';
    std::cout << "char        " << sizeof(char) << '\n';
    std::cout << "short       " << sizeof(short) << '\n';
    std::cout << "int         " << sizeof(int) << '\n';
    std::cout << "unsigned    " << sizeof(unsigned) << '\n';
    std::cout << "long        " << sizeof(long) << '\n';
    std::cout << "long long   " << sizeof(long long) << '\n';
    std::cout << "float       " << sizeof(float) << '\n';
    std::cout << "double      " << sizeof(double) << '\n';

    std::cout << "---- ranges ----\n";
    std::cout << "INT_MIN  " << INT_MIN << "\nINT_MAX  " << INT_MAX << '\n';
    std::cout << "UINT_MAX " << UINT_MAX << '\n';
    std::cout << "LLONG_MIN " << LLONG_MIN << "\nLLONG_MAX " << LLONG_MAX << '\n';
    std::cout << "SHRT_MAX " << SHRT_MAX << "\nCHAR_MAX " << CHAR_MAX << '\n';
    std::cout << "DBL_DIG (safe decimal digits) " << DBL_DIG << '\n';

    std::cout << "---- precision problem ----\n";
    std::cout << std::setprecision(17);
    double a = 0.1, b = 0.2;
    std::cout << "0.1 + 0.2 = " << a + b << '\n';
    std::cout << "0.1 + 0.2 == 0.3 ? " << std::boolalpha << (a + b == 0.3) << '\n';
    double recharge = 19.99;
    std::cout << "Rs 19.99 * 100 = " << recharge * 100 << '\n';
    std::cout << "truncated to paise = " << static_cast<int>(recharge * 100) << " (should be 1999)\n";

    std::cout << "---- error growth when n fares of Rs 0.10 are added ----\n";
    std::cout << std::setw(10) << "n" << std::setw(26) << "double rupees"
              << std::setw(16) << "paise/100" << std::setw(16) << "abs error" << '\n';
    long long ns[] = {10, 1000, 100000, 1000000, 3000000, 100000000};
    for (long long n : ns) {
    double d = 0.0;
    long long p = 0;
    for (long long i = 0; i < n; ++i) { d += 0.10; p += 10; }
    double exact = static_cast<double>(p) / 100.0;
            std::cout << std::setw(10) << n << std::setw(26) << std::setprecision(17) << d
                  << std::setw(16) << std::setprecision(10) << exact
                  << std::setw(16) << std::scientific << std::setprecision(3) << (d - exact)
                  << '\n';
        std::cout.unsetf(std::ios_base::floatfield);   // same effect as std::defaultfloat
}

    std::cout << "---- overflow evidence ----\n";
    long long journeys = 3000000, avgPaise = 2000;
    long long trueTotal = journeys * avgPaise;
    unsigned wrapped = static_cast<unsigned>(trueTotal);   // what a 32-bit int would hold (mod 2^32)
    int asInt = static_cast<int>(wrapped);
    std::cout << "true total (long long paise) = " << trueTotal << '\n';
    std::cout << "same total stored in 32-bit int = " << asInt << '\n';
    std::cout << "INT_MAX paise is only Rs " << INT_MAX / 100 << '\n';
}
