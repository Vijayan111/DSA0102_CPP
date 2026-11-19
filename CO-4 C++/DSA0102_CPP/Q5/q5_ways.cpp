// Q5.1 - four ways to reach a Cart object, method chaining and the this pointer
#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string owner;
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;                              // percent
public:
    explicit Cart(const std::string& owner = "") : owner(owner) {}   // parameter has the member's name
    Cart& add(const std::string& item, double price)
    {
        if (n < 10) { items[n] = item; prices[n] = price; ++n; }
        return *this;                                 // *this is the object the call was made on
    }
    Cart& setDiscount(double discount)
    {
        this->discount = discount;                    // this->discount = member, discount = parameter
        return *this;
    }
    double total() const
    {
        double t = 0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100 - discount) / 100;
    }
    const std::string& getOwner() const { return owner; }
    const Cart* self() const { return this; }         // shows that 'this' is a pointer to the object
};

void viaReference(Cart& r) { r.add("Tea", 90); }      // (c) through a reference

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    Cart a("Asha");                                   // (a) directly by name, automatic lifetime
    a.add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << "(a) by name        : " << a.total() << '\n';

    Cart* p = &a;                                     // (b) through a pointer with ->
    p->add("Oil", 180);
    std::cout << "(b) through pointer: " << p->total() << '\n';

    viaReference(a);                                  // (c) through a reference
    std::cout << "(c) via reference  : " << a.total() << '\n';

    Cart* d = new Cart("Bala");                       // (d) heap object, released by the programmer
    d->add("Milk", 50).add("Ghee", 400).setDiscount(5);
    std::cout << "(d) new / delete   : " << d->total() << '\n';
    delete d;

    std::cout << "this == &a ? " << std::boolalpha << (a.self() == &a) << '\n';
}
