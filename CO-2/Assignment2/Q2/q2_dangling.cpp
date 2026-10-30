// Q2 - returning a reference to a local variable (undefined behaviour)
#include <iostream>

int& badHighest()
{
    int local = 91;
    return local;          // 'local' dies when the function returns
}

int main()
{
    int& r = badHighest();
    std::cout << "value read through dangling reference: " << r << '\n';
    r = 5;                 // writing through it is also undefined behaviour
    std::cout << "after r = 5: " << r << '\n';
}
