// Q2 alternative: composition (has-a) instead of the diamond; size and access-time comparison
#include <chrono>
#include <iostream>

struct Person { int id; };

// diamond with virtual base
struct StudentV : virtual Person { double cgpa; };
struct StaffV   : virtual Person { double salary; };
struct TA_V : StudentV, StaffV {};

// plain bases, no virtual (two Person parts) used as members
struct StudentP : Person { double cgpa; };
struct StaffP   : Person { double salary; };
struct TA_C { StudentP s; StaffP f; };          // composition: TA HAS a Student and HAS a Staff

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
    std::cout << "sizeof(Person)=" << sizeof(Person) << "  sizeof(TA_V, virtual diamond)=" << sizeof(TA_V)
              << "  sizeof(TA_C, composition)=" << sizeof(TA_C) << '\n';

    static TA_V v[1024]; static TA_C c[1024];
    for (int i = 0; i < 1024; ++i) { v[i].id = i; c[i].s.id = i; c[i].f.id = 2 * i; }
    // c[i].id would be a compile error?  c has no member id at all: the TA must say WHICH person part
    const long N = 100000000;
    volatile long sink = 0;
    double tv = bestOf([&] { long t = 0; for (long i = 0; i < N; ++i) t += v[i & 1023].id; sink = t; });
    double tc = bestOf([&] { long t = 0; for (long i = 0; i < N; ++i) t += c[i & 1023].s.id; sink = t; });
    std::cout << "100,000,000 reads of the id:  virtual base " << tv << " ms,  member object " << tc << " ms\n";
    std::cout << "composition holds two ids per TA: s.id=" << c[5].s.id << " f.id=" << c[5].f.id << " (can disagree)\n";
}
