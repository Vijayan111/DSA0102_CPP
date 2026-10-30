// Q1 - Hostel Fee Concession Updater: by value, by reference, by pointer
#include <iostream>

// 1) by value: the function works on a private copy of the fee
void applyByValue(long long fee, int percent)
{
    fee -= fee * percent / 100;
    std::cout << "  inside applyByValue   : " << fee << '\n';
}

// 2) by reference: 'fee' is another name for the caller's variable
void applyByRef(long long& fee, int percent)
{
    fee -= fee * percent / 100;
    std::cout << "  inside applyByRef     : " << fee << '\n';
}

// 3) by pointer: the function gets the address of the caller's variable
void applyByPtr(long long* fee, int percent)
{
    if (fee == nullptr) return;          // a pointer can be null, a reference cannot
    *fee -= *fee * percent / 100;
    std::cout << "  inside applyByPtr     : " << *fee << '\n';
}

// Design decision: pure function that returns the new fee (easy to chain)
long long afterConcession(long long fee, int percent)
{
    return fee - fee * percent / 100;
}

int main()
{
    const long long original = 45000;
    long long fee;

    fee = original;
    std::cout << "call by value:\n";
    applyByValue(fee, 10);
    std::cout << "  stored fee afterwards : " << fee << "\n\n";

    fee = original;
    std::cout << "call by reference:\n";
    applyByRef(fee, 10);
    std::cout << "  stored fee afterwards : " << fee << "\n\n";

    fee = original;
    std::cout << "call by pointer:\n";
    applyByPtr(&fee, 10);
    std::cout << "  stored fee afterwards : " << fee << "\n\n";

    // several concessions on one student: merit 10%, sports 15%, single parent 25%
    long long f = original;
    f = afterConcession(f, 10);
    std::cout << "after merit 10%          : " << f << '\n';
    f = afterConcession(f, 15);
    std::cout << "after sports 15% as well : " << f << '\n';
    f = afterConcession(f, 25);
    std::cout << "after single parent 25%  : " << f << '\n';
    std::cout << "one-line chain           : "
              << afterConcession(afterConcession(afterConcession(original, 10), 15), 25) << '\n';
}
