// Q7: time per operation, my Complex versus std::complex<double> (20,000,000 operations each)
#include <chrono>
#include <complex>
#include <iostream>
#include "complex.h"

template <class F> double ns(F f, int n)
{
    auto s = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - s).count() / n;
}

int main()
{
    const int N = 20000000;
    Complex m(1.0, 0.5), mk(0.6, 0.8), macc(1, 1);
    std::complex<double> s(1.0, 0.5), sk(0.6, 0.8), sacc(1, 1);

    double a1 = ns([&] { for (int i = 0; i < N; ++i) { macc = macc + mk; asm volatile("" : "+m"(macc)); } }, N);
    double a2 = ns([&] { for (int i = 0; i < N; ++i) { sacc = sacc + sk; asm volatile("" : "+m"(sacc)); } }, N);
    double m1 = ns([&] { for (int i = 0; i < N; ++i) { macc = macc * mk; asm volatile("" : "+m"(macc)); } }, N);
    double m2 = ns([&] { for (int i = 0; i < N; ++i) { sacc = sacc * sk; asm volatile("" : "+m"(sacc)); } }, N);
    double d1 = ns([&] { for (int i = 0; i < N; ++i) { macc = macc / mk; asm volatile("" : "+m"(macc)); } }, N);
    double d2 = ns([&] { for (int i = 0; i < N; ++i) { sacc = sacc / sk; asm volatile("" : "+m"(sacc)); } }, N);

    std::cout << "ns per operation (-O2)      my Complex    std::complex\n";
    std::cout << "addition                    " << a1 << "         " << a2 << '\n';
    std::cout << "multiplication              " << m1 << "         " << m2 << '\n';
    std::cout << "division                    " << d1 << "         " << d2 << '\n';
    std::cout << "sizeof: " << sizeof(Complex) << " and " << sizeof(std::complex<double>) << " bytes\n";
    (void)m; (void)s;
}
