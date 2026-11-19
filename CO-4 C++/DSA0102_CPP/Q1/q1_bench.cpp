// Q1 alternative: ONE Staff class with a type field and a switch, compared with the hierarchy
#include <chrono>
#include <iostream>
#include <string>

const double DA_RATE = 0.42;

// ---------- design A: hierarchy (virtual pay) ----------
class StaffH {
    std::string name; int id;
public:
    StaffH(const std::string& n, int i) : name(n), id(i) {}
    virtual ~StaffH() = default;
    virtual double pay() const = 0;
};
class ProfH : public StaffH {
    double basic, research;
public:
    ProfH(double b, double r) : StaffH("p", 1), basic(b), research(r) {}
    double pay() const override { return basic + basic * DA_RATE + research; }
};
class LabH : public StaffH {
    double basic;
public:
    explicit LabH(double b) : StaffH("l", 2), basic(b) {}
    double pay() const override { return basic + basic * DA_RATE; }
};
class GuestH : public StaffH {
    double hours, rate;
public:
    GuestH(double h, double r) : StaffH("g", 3), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

// ---------- design B: one class, type field, switch ----------
enum StaffType { PROFESSOR, LAB_ASSISTANT, GUEST };
class StaffS {
    std::string name; int id;
    StaffType type;
    double basic, research, hours, rate;      // each object carries ALL fields, most unused
public:
    StaffS(StaffType t, double b, double r, double h, double rt)
        : name("x"), id(0), type(t), basic(b), research(r), hours(h), rate(rt) {}
    double pay() const {
        switch (type) {
            case PROFESSOR:     return basic + basic * DA_RATE + research;
            case LAB_ASSISTANT: return basic + basic * DA_RATE;
            case GUEST:         return hours * rate;
        }
        return 0;
    }
};

template <class F> double bestOf(F f)
{
    double best = 1e18;
    for (int rep = 0; rep < 11; ++rep) {
        auto t0 = std::chrono::steady_clock::now();
        f();
        auto t1 = std::chrono::steady_clock::now();
        double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
        if (ms < best) best = ms;
    }
    return best;
}

int main()
{
    const int N = 1024;
    const long CALLS = 10000000;
    StaffH* h[N]; StaffS* s[N];
    for (int i = 0; i < N; ++i) {
        int k = (i * 7 + i / 3) % 3;                       // irregular mix of the three types
        double b = 20000 + i, r = 1000 + i, hrs = 5 + i % 9, rt = 1000 + i % 50;
        if (k == 0)      { h[i] = new ProfH(b, r);   s[i] = new StaffS(PROFESSOR, b, r, 0, 0); }
        else if (k == 1) { h[i] = new LabH(b);       s[i] = new StaffS(LAB_ASSISTANT, b, 0, 0, 0); }
        else             { h[i] = new GuestH(hrs, rt); s[i] = new StaffS(GUEST, 0, 0, hrs, rt); }
    }

    std::cout << "sizeof(ProfH)=" << sizeof(ProfH) << " sizeof(LabH)=" << sizeof(LabH)
              << " sizeof(GuestH)=" << sizeof(GuestH) << "  sizeof(StaffS)=" << sizeof(StaffS) << '\n';

    volatile double sink = 0;
    double sumH = 0, sumS = 0;
    double tH = bestOf([&] { double t = 0; for (long i = 0; i < CALLS; ++i) t += h[i & (N - 1)]->pay(); sumH = t; sink = t; });
    double tS = bestOf([&] { double t = 0; for (long i = 0; i < CALLS; ++i) t += s[i & (N - 1)]->pay(); sumS = t; sink = t; });
    std::cout << "10,000,000 pay() calls, best of 11\n";
    std::cout << "  virtual call (hierarchy) : " << tH << " ms\n";
    std::cout << "  switch (one class)       : " << tS << " ms\n";
    std::cout << "  same total? " << (sumH == sumS ? "yes" : "NO") << "  (" << sumH << ")\n";
    for (int i = 0; i < N; ++i) { delete h[i]; delete s[i]; }
}
