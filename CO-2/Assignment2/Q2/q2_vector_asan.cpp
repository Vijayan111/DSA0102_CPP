// Q2 - same situation, but now we really use the stale reference (run with AddressSanitizer)
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {72, 85, 91};
    int& ref = v[2];
    v.push_back(64);                              // reallocation
    std::cout << ref << '\n';                     // use after free
}
