// Q4 alternative: + as a non-member friend, so 100 + m works as well as m + 100
#include <iostream>

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
#ifdef AS_FRIEND
    friend Money operator+(const Money& a, const Money& b)
    {
        Money r;
        r.paise = a.paise + b.paise;
        return r;
    }
#else
    Money operator+(const Money& o) const
    {
        Money r;
        r.paise = paise + o.paise;
        return r;
    }
#endif
    long long get() const { return paise; }
};

int main()
{
    Money m(5, 50);
    Money a = m + 100;          // works in both versions: m is the left operand
    Money b = 100 + m;          // needs the non-member (friend) form
    std::cout << a.get() << ' ' << b.get() << '\n';
}
