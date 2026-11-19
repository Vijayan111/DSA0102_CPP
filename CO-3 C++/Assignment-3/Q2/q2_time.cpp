// Q2: time to copy a prescription with 10, 1000 and 100000 medicines
// manual deep copy (new[]), std::vector (Rule of Zero), and a shallow (pointer only) copy
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class Manual {
public:
    int n; std::string* m;
    explicit Manual(int c) : n(c), m(new std::string[c]) {}
    Manual(const Manual& o) : n(o.n), m(new std::string[o.n]) { for (int i = 0; i < n; ++i) m[i] = o.m[i]; }
    Manual& operator=(const Manual&) = delete;
    ~Manual() { delete[] m; }
};
struct Vec { std::vector<std::string> m; };
struct Shallow { int n; std::string* m; };

template <class F> double perCopyUs(int reps, F f)
{
    auto s = std::chrono::steady_clock::now();
    for (int i = 0; i < reps; ++i) f();
    return std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - s).count() / reps;
}

int main()
{
    std::cout << "n medicines | deep copy (new[]) | vector copy | shallow copy   (microseconds per copy)\n";
    for (int n : {10, 1000, 100000}) {
        int reps = n == 10 ? 200000 : (n == 1000 ? 2000 : 20);
        Manual a(n); for (int i = 0; i < n; ++i) a.m[i] = "Paracetamol-500mg-tablet-" + std::to_string(i);
        Vec v; for (int i = 0; i < n; ++i) v.m.push_back("Paracetamol-500mg-tablet-" + std::to_string(i));
        Shallow s{n, a.m};
        volatile size_t sink = 0;
        double d = perCopyUs(reps, [&] { Manual c(a); sink = sink + c.m[n - 1].size(); });
        double w = perCopyUs(reps, [&] { Vec c(v); sink = sink + c.m[n - 1].size(); });
        double sh = perCopyUs(reps * 50, [&] { Shallow c = s; sink = sink + (size_t)c.n; asm volatile("" ::: "memory"); });
        std::cout << n << "\t" << d << "\t" << w << "\t" << sh << '\n';
    }
}
