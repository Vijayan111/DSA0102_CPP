// Q6: 100,000 concatenations - Text versus std::string
#include <chrono>
#include <iostream>
#include <string>
#include "text.h"

template <class F> double ms(F f)
{
    auto s = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - s).count();
}

int main()
{
    const int N = 100000;
    Text piece("x");
    std::string spiece = "x";
    size_t lenText = 0, lenS1 = 0, lenS2 = 0, lenT2 = 0;

    double t1 = ms([&] { Text t; for (int i = 0; i < N; ++i) t = t + piece; lenText = t.size(); });
    double t2 = ms([&] { Text t; for (int i = 0; i < N; ++i) t += piece;    lenT2 = t.size(); });
    double s1 = ms([&] { std::string s; for (int i = 0; i < N; ++i) s = s + spiece; lenS1 = s.size(); });
    double s2 = ms([&] { std::string s; for (int i = 0; i < N; ++i) s += spiece;    lenS2 = s.size(); });

    std::cout << "100,000 concatenations of one character (final length " << lenText << ")\n";
    std::cout << "Text   t = t + x : " << t1 << " ms\n";
    std::cout << "Text   t += x    : " << t2 << " ms\n";
    std::cout << "string s = s + x : " << s1 << " ms\n";
    std::cout << "string s += x    : " << s2 << " ms\n";
    std::cout << "(lengths " << lenT2 << ' ' << lenS1 << ' ' << lenS2 << ")\n";
}
