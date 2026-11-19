// Q5 alternative: std::vector<Cart> (objects) instead of an array of Cart*
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class Cart {
    std::string items[10]; double prices[10]; int n = 0; double discount = 0;
public:
    Cart& add(const std::string& item, double price) { if (n < 10) { items[n] = item; prices[n] = price; ++n; } return *this; }
    Cart& setDiscount(double d) { this->discount = d; return *this; }
    double total() const { double t = 0; for (int i = 0; i < n; ++i) t += prices[i]; return t * (100 - discount) / 100; }
};

template <class F> double bestOf(F f)
{
    double best = 1e18;
    for (int r = 0; r < 11; ++r) {
        auto t0 = std::chrono::steady_clock::now(); f();
        auto t1 = std::chrono::steady_clock::now();
        double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
        if (ms < best) best = ms;
    }
    return best;
}

int main()
{
    std::cout << "sizeof(Cart)=" << sizeof(Cart) << " bytes copied into the vector per cart; sizeof(Cart*)=" << sizeof(Cart*) << '\n';

    // growth: a pointer into the vector is invalidated
    std::vector<Cart> v(3);
    v[0].add("Rice", 60);
    Cart* ptr = &v[0];
    std::cout << "capacity " << v.capacity() << ", &v[0] before = " << (const void*)ptr << '\n';
    v.push_back(Cart());                                // vector is full: reallocation
    std::cout << "capacity " << v.capacity() << ", &v[0] after  = " << (const void*)&v[0]
              << (ptr == &v[0] ? "  (same)" : "  (MOVED: ptr is dangling)") << '\n';

    // speed of the 'find the highest total' search, both O(n)
    const int N = 100000;
    std::vector<Cart> objs(N);
    std::vector<Cart*> ptrs;
    for (int i = 0; i < N; ++i) objs[i].add("a", i % 97).add("b", i % 13).add("c", 5);
    for (int i = 0; i < N; ++i) ptrs.push_back(new Cart(objs[(i * 7919) % N]));   // pointers in scattered order
    volatile double sink = 0;
    double tv = bestOf([&] { double m = 0; for (int r = 0; r < 20; ++r) for (const Cart& c : objs) { double t = c.total(); if (t > m) m = t; } sink = m; });
    double tp = bestOf([&] { double m = 0; for (int r = 0; r < 20; ++r) for (Cart* c : ptrs)  { double t = c->total(); if (t > m) m = t; } sink = m; });
    std::cout << "highest-total search, 100,000 carts x 20 passes: vector<Cart> " << tv << " ms, Cart* array " << tp << " ms\n";
    for (Cart* c : ptrs) delete c;
}
