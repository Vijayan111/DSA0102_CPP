// Q2 alternative: return the highest mark as index / pointer / reference
#include <iostream>
#include <vector>
#include <chrono>

int  highestIndex(const std::vector<int>& v) { int idx = 0; for (int i = 1; i < (int)v.size(); ++i) if (v[i] > v[idx]) idx = i; return idx; }
int* highestPtr  (std::vector<int>& v)       { int* p = &v[0]; for (auto& x : v) if (x > *p) p = &x; return p; }
int& highestRef  (std::vector<int>& v)       { int* p = &v[0]; for (auto& x : v) if (x > *p) p = &x; return *p; }

template <class F> double timeIt(F f)
{
    auto t0 = std::chrono::steady_clock::now();
    f();
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main()
{
    // calling code for the three styles
    std::vector<int> v = {72, 85, 91, 64, 88};
    int i = highestIndex(v);  v[i] += 2;                 // index
    int* p = highestPtr(v);   *p += 2;                   // pointer
    highestRef(v) += 2;                                  // reference
    std::cout << "marks after three +2 moderations: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "\n\n";

    // time of finding the highest mark for growing n (should be O(n) for all three)
    std::cout << "n          index(ms)  pointer(ms)  reference(ms)   (50 repeats)\n";
    for (int n : {1000000, 2000000, 4000000}) {
        std::vector<int> d(n);
        unsigned s = 12345;
        for (int k = 0; k < n; ++k) { s = s * 1103515245u + 12345u; d[k] = (s >> 8) % 100000; }
        volatile long long sink = 0;
        double a = timeIt([&] { for (int r = 0; r < 50; ++r) sink = highestIndex(d); });
        double b = timeIt([&] { for (int r = 0; r < 50; ++r) sink = *highestPtr(d); });
        double c = timeIt([&] { for (int r = 0; r < 50; ++r) sink = highestRef(d); });
        std::cout << n << "    " << a << "      " << b << "        " << c << '\n';
    }
}
