// Task 5 - peak check: expression vs lookup table, and the two precedence forms
#include <iostream>

constexpr bool isPeakExpr(int hour)
{
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}
constexpr bool isPeakNoParens(int hour)
{
    return hour >= 8 && hour < 10 || hour >= 17 && hour < 20;   // same result, && binds tighter than ||
}

int main()
{
    bool peak[24] = {};
    for (int h = 0; h < 24; ++h) peak[h] = isPeakExpr(h);   // table built once

    bool allSame = true;
    std::cout << "peak hours (start of hour): ";
    for (int h = 0; h < 24; ++h) {
        if (peak[h] != isPeakNoParens(h)) allSame = false;
        if (peak[h]) std::cout << h << ' ';
    }
    std::cout << "\nboth forms agree for 0..23 : " << std::boolalpha << allSame << '\n';
    std::cout << "hour 10 peak? " << isPeakExpr(10) << "   hour 20 peak? " << isPeakExpr(20) << '\n';
    std::cout << "hour 8 peak? " << isPeakExpr(8) << "   hour 17 peak? " << isPeakExpr(17) << '\n';

    int i = 5;
    i = i++;        // C++17: i ends as 5 (the old value is written back); before C++17 it was undefined. Never write this.
    std::cout << "i after i = i++ : " << i << '\n';
}
