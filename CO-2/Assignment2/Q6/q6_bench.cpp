// Q6 - cost of 10,000,000 calls: friend inline / friend noinline / member / getters
#include <iostream>
#include <chrono>
#include <algorithm>

class Time {
    int h, m;
public:
    Time(int hh = 0, int mm = 0) : h(hh), m(mm) {}
    friend int minutesBetween(const Time&, const Time&);
    friend bool earlier(const Time&, const Time&);
    friend int minutesBetweenNI(const Time&, const Time&);
    friend bool earlierNI(const Time&, const Time&);
    int minutesTo(const Time& o) const { int x = h * 60 + m, y = o.h * 60 + o.m; return x > y ? x - y : y - x; }
    bool isEarlier(const Time& o) const { return h * 60 + m < o.h * 60 + o.m; }
    int getH() const { return h; }
    int getM() const { return m; }
};

inline int minutesBetween(const Time& a, const Time& b) { int x = a.h * 60 + a.m, y = b.h * 60 + b.m; return x > y ? x - y : y - x; }
inline bool earlier(const Time& a, const Time& b)       { return a.h * 60 + a.m < b.h * 60 + b.m; }

__attribute__((noinline)) int  minutesBetweenNI(const Time& a, const Time& b) { int x = a.h * 60 + a.m, y = b.h * 60 + b.m; return x > y ? x - y : y - x; }
__attribute__((noinline)) bool earlierNI(const Time& a, const Time& b)        { return a.h * 60 + a.m < b.h * 60 + b.m; }

inline int  minutesGet(const Time& a, const Time& b) { int x = a.getH() * 60 + a.getM(), y = b.getH() * 60 + b.getM(); return x > y ? x - y : y - x; }
inline bool earlierGet(const Time& a, const Time& b) { return a.getH() * 60 + a.getM() < b.getH() * 60 + b.getM(); }

static Time t[1024];
volatile long long sink;
const long N = 10000000;

template <class F> double best(F f)
{
    double b = 1e18;
    for (int rep = 0; rep < 21; ++rep) {
        auto t0 = std::chrono::steady_clock::now();
        long long r = f();
        auto t1 = std::chrono::steady_clock::now();
        sink = r;
        b = std::min(b, std::chrono::duration<double, std::milli>(t1 - t0).count());
    }
    return b;
}

int main()
{
    for (int i = 0; i < 1024; ++i) t[i] = Time((i * 7) % 24, (i * 13) % 60);

    double a = best([] { long long r = 0; for (long i = 0; i < N; ++i) { const Time& x = t[i & 1023]; const Time& y = t[(i * 5 + 3) & 1023]; r += minutesBetween(x, y) + earlier(x, y); } return r; });
    double b = best([] { long long r = 0; for (long i = 0; i < N; ++i) { const Time& x = t[i & 1023]; const Time& y = t[(i * 5 + 3) & 1023]; r += minutesBetweenNI(x, y) + earlierNI(x, y); } return r; });
    double c = best([] { long long r = 0; for (long i = 0; i < N; ++i) { const Time& x = t[i & 1023]; const Time& y = t[(i * 5 + 3) & 1023]; r += x.minutesTo(y) + x.isEarlier(y); } return r; });
    double d = best([] { long long r = 0; for (long i = 0; i < N; ++i) { const Time& x = t[i & 1023]; const Time& y = t[(i * 5 + 3) & 1023]; r += minutesGet(x, y) + earlierGet(x, y); } return r; });

    std::cout << "10,000,000 iterations (each = one minutes call + one earlier call), best of 21\n";
    std::cout << "friend, inline          : " << a << " ms\n";
    std::cout << "friend, noinline        : " << b << " ms\n";
    std::cout << "member functions        : " << c << " ms\n";
    std::cout << "public getters          : " << d << " ms\n";
}
