// Q6 - correctness check of the friend functions
#include <iostream>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b)
{
    int x = a.h * 60 + a.m;
    int y = b.h * 60 + b.m;
    return x > y ? x - y : y - x;
}

inline bool earlier(const Time& a, const Time& b)
{
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

void test(const char* label, Time a, Time b)
{
    std::cout << label << "  minutesBetween = " << minutesBetween(a, b)
              << "  earlier(a,b) = " << earlier(a, b) << "  earlier(b,a) = " << earlier(b, a) << '\n';
}

int main()
{
    std::cout << std::boolalpha;
    test("09:45 and 13:10 (given)       ", Time(9, 45),  Time(13, 10));
    test("11:50 and 12:10 (across noon) ", Time(11, 50), Time(12, 10));
    test("12:10 and 11:50 (reversed)    ", Time(12, 10), Time(11, 50));
    test("08:30 and 08:30 (same time)   ", Time(8, 30),  Time(8, 30));
    test("12:00 and 12:00 (noon twice)  ", Time(12, 0),  Time(12, 0));
}
