// Task 7 alternative - balance as a public data member: any code can break the rule
#include <iostream>
struct BadCard { long long balance; };
int main()
{
    BadCard c{6000};
    c.balance -= 9000;      // compiles, runs, no check at all
    std::cout << "balance now " << c.balance << " paise\n";
}
