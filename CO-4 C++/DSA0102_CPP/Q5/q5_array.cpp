// Q5.2 - array of pointers to Cart: find the cart with the highest total
#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string owner; std::string items[10]; double prices[10]; int n = 0; double discount = 0;
public:
    explicit Cart(const std::string& o = "") : owner(o) {}
    Cart& add(const std::string& item, double price) { if (n < 10) { items[n] = item; prices[n] = price; ++n; } return *this; }
    Cart& setDiscount(double d) { this->discount = d; return *this; }
    double total() const { double t = 0; for (int i = 0; i < n; ++i) t += prices[i]; return t * (100 - discount) / 100; }
    const std::string& getOwner() const { return owner; }
};

// pointer arithmetic version: walk from the first pointer to one past the last
const Cart* highestByPointer(Cart* const* first, int count)
{
    const Cart* best = nullptr;                       // nullptr = "no carts"
    for (Cart* const* p = first; p != first + count; ++p)
        if (!best || (*p)->total() > best->total()) best = *p;
    return best;
}

// indexing version
const Cart* highestByIndex(Cart* carts[], int count)
{
    if (count == 0) return nullptr;
    const Cart* best = carts[0];
    for (int i = 1; i < count; ++i)
        if (carts[i]->total() > best->total()) best = carts[i];
    return best;
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    Cart* carts[4] = { new Cart("Asha"), new Cart("Bala"), new Cart("Chitra"), new Cart("Dev") };
    carts[0]->add("Rice", 60).add("Dal", 120);
    carts[1]->add("Oil", 180).add("Milk", 50).setDiscount(10);
    carts[2]->add("Tea", 90).add("Sugar", 45).add("Ghee", 400).setDiscount(5);
    carts[3]->add("Soap", 30);

    for (Cart* c : carts) std::cout << std::left << std::setw(8) << c->getOwner() << std::right << std::setw(8) << c->total() << '\n';
    const Cart* b1 = highestByPointer(carts, 4);
    const Cart* b2 = highestByIndex(carts, 4);
    std::cout << "highest (pointer arithmetic): " << b1->getOwner() << " " << b1->total() << '\n';
    std::cout << "highest (indexing)          : " << b2->getOwner() << " " << b2->total() << '\n';
    std::cout << "empty array                 : " << (highestByPointer(carts, 0) == nullptr ? "nullptr" : "?") << '\n';
    for (Cart* c : carts) delete c;
}
