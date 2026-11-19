// Q1 experiment: members initialised in declaration order, not in list order
#include <iostream>

class Shelf {
    int total;        // declared first, so it is initialised first
    int available;    // declared second
public:
    // the list says available first, and it reads total, which is not set yet
    Shelf(int t) : available(total), total(t) {}
    void print() const { std::cout << "total = " << total << ", available = " << available << '\n'; }
};

int main()
{
    Shelf s(40);
    s.print();
}
