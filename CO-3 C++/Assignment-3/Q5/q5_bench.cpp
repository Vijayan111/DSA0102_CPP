// Q5: 10,000,000 prefix and postfix increments, for a small class and for a class that owns a string
#include <chrono>
#include <iostream>
#include <string>

class Time {
public:
    int h = 0, m = 0, s = 0;
    Time& operator++() { if (++s == 60) { s = 0; if (++m == 60) { m = 0; ++h; } } return *this; }
    Time operator++(int) { Time old = *this; ++(*this); return old; }
};

class LabelledTime {                       // same clock, plus a 40 character label (heap memory)
public:
    int h = 0, m = 0, s = 0;
    std::string label = "playlist position of the current track.";
    LabelledTime& operator++() { if (++s == 60) { s = 0; if (++m == 60) { m = 0; ++h; } } return *this; }
    LabelledTime operator++(int) { LabelledTime old = *this; ++(*this); return old; }
};

template <class T, class F> double run(T& t, F f)
{
    auto s = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000000; ++i) { f(t); asm volatile("" : "+m"(t) :: "memory"); }
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - s).count();
}

int main()
{
    Time a, b;
    LabelledTime c, d;
    double pre = run(a, [](Time& t) { ++t; });
    double post = run(b, [](Time& t) { t++; });
    double lpre = run(c, [](LabelledTime& t) { ++t; });
    double lpost = run(d, [](LabelledTime& t) { t++; });
    std::cout << "10,000,000 increments (ms)\n";
    std::cout << "Time           prefix " << pre << "   postfix " << post << '\n';
    std::cout << "LabelledTime   prefix " << lpre << "   postfix " << lpost << '\n';
    std::cout << "(check " << a.s + b.s + c.s + d.s << ")\n";
}
