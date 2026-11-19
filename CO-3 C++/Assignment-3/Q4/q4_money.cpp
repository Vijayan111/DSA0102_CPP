// Q4 - Money class for a billing counter (paise stored in a long long)
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Money {
    long long paise;                                   // 1 rupee = 100 paise, can be negative (credit)
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    static Money fromPaise(long long p) { Money m; m.paise = p; return m; }
    long long totalPaise() const { return paise; }
    bool isNegative() const { return paise < 0; }

    // compound assignment changes *this and returns a reference to it
    Money& operator+=(const Money& o) { paise += o.paise; return *this; }
    Money& operator-=(const Money& o) { paise -= o.paise; return *this; }

    // + and - build a new object, written with the compound versions
    Money operator+(const Money& o) const { Money r = *this; r += o; return r; }
    Money operator-(const Money& o) const { Money r = *this; r -= o; return r; }

    // money times a plain number makes sense (4 notebooks), money times money does not
    Money operator*(long long k) const { return fromPaise(paise * k); }

    // percentage of an amount, rounded half up to the nearest paisa
    Money percent(int pct) const { return fromPaise((paise * pct + 50) / 100); }

    bool operator==(const Money& o) const { return paise == o.paise; }
    bool operator!=(const Money& o) const { return !(*this == o); }
    bool operator<(const Money& o) const { return paise < o.paise; }
    bool operator>(const Money& o) const { return o < *this; }

    friend std::ostream& operator<<(std::ostream& os, const Money& m)
    {
        long long a = m.paise < 0 ? -m.paise : m.paise;
        char old = os.fill('0');
        os << (m.paise < 0 ? "-Rs " : "Rs ") << a / 100 << '.' << std::setw(2) << a % 100;
        os.fill(old);
        return os;
    }

    // reads amounts such as 120.75, 7.5 or 40
    friend std::istream& operator>>(std::istream& is, Money& m)
    {
        std::string s;
        if (!(is >> s)) return is;
        size_t dot = s.find('.');
        std::string r = s.substr(0, dot), p = dot == std::string::npos ? "" : s.substr(dot + 1);
        bool ok = !r.empty() && p.size() <= 2 && r.find_first_not_of("0123456789") == std::string::npos &&
                  p.find_first_not_of("0123456789") == std::string::npos;
        if (!ok) { is.setstate(std::ios::failbit); return is; }
        if (p.size() == 1) p += '0';
        m = fromPaise(std::stoll(r) * 100 + (p.empty() ? 0 : std::stoi(p)));
        return is;
    }
};

int main()
{
    std::cout << "--- carry: Rs 0.75 + Rs 0.50 ---\n";
    Money x(0, 75), y(0, 50);
    std::cout << x << " + " << y << " = " << x + y << "   (125 paise carried into 1 rupee)\n";

    std::cout << "\n--- subtraction giving a negative amount ---\n";
    Money d = y - x;
    std::cout << y << " - " << x << " = " << d << "   isNegative = " << std::boolalpha << d.isNegative() << '\n';

    std::cout << "\n--- comparisons ---\n";
    std::cout << "x == Money(0,75): " << (x == Money(0, 75)) << ", x < y: " << (x < y)
              << ", y < x: " << (y < x) << ", x != y: " << (x != y) << '\n';

    std::cout << "\n--- += and reading with >> ---\n";
    std::istringstream in("120.75 7.5 40 12.345 abc");
    Money total, t;
    while (in >> t) { std::cout << "  read " << t << '\n'; total += t; }
    std::cout << "  stopped at bad input, total so far = " << total << '\n';

    std::cout << "\n--- bill calculation with operators ---\n";
    Money notebook(45, 50), pen(12, 25), marker(79, 99);
    Money subtotal = notebook * 4 + pen * 10 + marker * 2;
    Money discount(20);
    Money taxable = subtotal - discount;
    Money gst = taxable.percent(5);
    Money bill = taxable + gst;
    Money paid(500);
    std::cout << "  4 notebooks  : " << notebook * 4 << '\n';
    std::cout << "  10 pens      : " << pen * 10 << '\n';
    std::cout << "  2 markers    : " << marker * 2 << '\n';
    std::cout << "  subtotal     : " << subtotal << '\n';
    std::cout << "  discount     : " << discount << '\n';
    std::cout << "  GST 5%       : " << gst << '\n';
    std::cout << "  bill         : " << bill << '\n';
    std::cout << "  paid         : " << paid << '\n';
    std::cout << "  change       : " << paid - bill << '\n';
    if (bill < paid) std::cout << "  (customer paid enough)\n";
}
