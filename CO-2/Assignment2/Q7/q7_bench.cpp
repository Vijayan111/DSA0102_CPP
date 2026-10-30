// Q7 - shifting array vs circular buffer: cost of adding a transaction as the capacity grows
#include <iostream>
#include <iomanip>
#include <chrono>

struct Transaction { int no; char type; long long amount; long long balanceAfter; };

template <int CAP>
class ShiftHistory {
    Transaction tx[CAP];
    int count = 0;
public:
    void add(const Transaction& t)
    {
        if (count == CAP) {
            for (int i = 1; i < CAP; ++i) tx[i - 1] = tx[i];     // O(CAP)
            --count;
        }
        tx[count++] = t;
    }
    long long checksum() const { long long s = 0; for (int i = 0; i < count; ++i) s += tx[i].no * (i + 1LL); return s; }
};

template <int CAP>
class CircularHistory {
    Transaction tx[CAP];
    int start = 0, count = 0;
public:
    void add(const Transaction& t)
    {
        if (count < CAP) { tx[(start + count) % CAP] = t; ++count; }
        else             { tx[start] = t; start = (start + 1) % CAP; }   // O(1)
    }
    long long checksum() const { long long s = 0; for (int i = 0; i < count; ++i) s += tx[(start + i) % CAP].no * (i + 1LL); return s; }
};

template <class H> double run(H* h, int adds, long long& sum)
{
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 1; i <= adds; ++i) h->add(Transaction{i, (i & 1) ? 'D' : 'W', i % 977, i});
    auto t1 = std::chrono::steady_clock::now();
    sum = h->checksum();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

template <int CAP> void compare(int adds)
{
    ShiftHistory<CAP>*    s = new ShiftHistory<CAP>();
    CircularHistory<CAP>* c = new CircularHistory<CAP>();
    long long sumS = 0, sumC = 0;
    double ts = run(s, adds, sumS);
    double tc = run(c, adds, sumC);
    std::cout << std::setw(6) << CAP << std::setw(10) << adds
              << std::setw(14) << std::fixed << std::setprecision(3) << ts
              << std::setw(14) << tc
              << std::setw(14) << std::setprecision(1) << ts / tc << "x"
              << std::setw(10) << (sumS == sumC ? "same" : "DIFFERENT") << '\n';
    delete s;
    delete c;
}

int main()
{
    std::cout << "  CAP      adds   shift(ms)  circular(ms)    speed-up  contents\n";
    compare<10>(200000);
    compare<50>(200000);
    compare<500>(200000);
    compare<2000>(100000);
    compare<10000>(50000);
}
