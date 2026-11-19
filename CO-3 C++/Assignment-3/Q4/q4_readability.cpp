// Q4: the same bill written with named functions and with operators
#include <iostream>

struct Money { long long paise; };
Money add(Money a, Money b)        { return {a.paise + b.paise}; }
Money sub(Money a, Money b)        { return {a.paise - b.paise}; }
Money mul(Money a, long long k)    { return {a.paise * k}; }
Money pct(Money a, int p)          { return {(a.paise * p + 50) / 100}; }
void  print(Money a)               { std::cout << "Rs " << a.paise / 100 << '.' << (a.paise % 100 < 10 ? "0" : "") << a.paise % 100 << '\n'; }

struct Money2 {
    long long paise;
    Money2 operator+(Money2 o) const { return {paise + o.paise}; }
    Money2 operator-(Money2 o) const { return {paise - o.paise}; }
    Money2 operator*(long long k) const { return {paise * k}; }
    Money2 percent(int p) const { return {(paise * p + 50) / 100}; }
};
std::ostream& operator<<(std::ostream& os, Money2 a)
{ return os << "Rs " << a.paise / 100 << '.' << (a.paise % 100 < 10 ? "0" : "") << a.paise % 100; }

int main()
{
    Money nb{4550}, pn{1225}, mk{7999}, disc{2000};
    // 1) named functions
    Money subtotal  = add(add(mul(nb, 4), mul(pn, 10)), mul(mk, 2));
    Money taxable   = sub(subtotal, disc);
    Money bill      = add(taxable, pct(taxable, 5));
    print(bill);

    // 2) overloaded operators
    Money2 nb2{4550}, pn2{1225}, mk2{7999}, disc2{2000};
    Money2 subtotal2 = nb2 * 4 + pn2 * 10 + mk2 * 2;
    Money2 taxable2  = subtotal2 - disc2;
    Money2 bill2     = taxable2 + taxable2.percent(5);
    std::cout << bill2 << '\n';
}
