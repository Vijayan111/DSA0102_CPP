#include <iomanip>
#include <iostream>

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // TODO 1: Overload + as a member function that returns a new Money object
    Money operator+(const Money& other) const
    {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }

    // TODO 2: Overload == as a member, and << as a friend that prints "Rs 200.00"
    bool operator==(const Money& other) const { return paise == other.paise; }

    friend std::ostream& operator<<(std::ostream& os, const Money& m)
    {
        char old = os.fill('0');
        os << "Rs " << m.paise / 100 << '.' << std::setw(2) << m.paise % 100;
        os.fill(old);
        return os;
    }
};

int main()
{
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    // extra test asked in the question: paise carry into rupees
    Money x(0, 75), y(0, 50);
    std::cout << x << " + " << y << " = " << x + y << '\n';
}
