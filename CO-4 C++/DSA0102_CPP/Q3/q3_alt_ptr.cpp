// Q3 alternative: Student holds Address* (heap) instead of an Address member object
#include <chrono>
#include <iostream>
#include <string>

class Address {
    std::string city; int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class StudentMember {                              // design A: member object
    long long regNo; Address home;
public:
    StudentMember(long long r, const std::string& c, int p) : regNo(r), home(c, p) {}
    int len() const { return (int)home.str().size() + (int)(regNo & 1); }
};

class StudentPtr {                                 // design B: pointer to a heap Address
    long long regNo; Address* home;
public:
    StudentPtr(long long r, const std::string& c, int p) : regNo(r), home(new Address(c, p)) {}
#ifndef NOCOPY
    StudentPtr(const StudentPtr& o) : regNo(o.regNo), home(new Address(*o.home)) {}   // deep copy
    StudentPtr& operator=(const StudentPtr& o) {
        if (this != &o) { Address* t = new Address(*o.home); delete home; home = t; regNo = o.regNo; }
        return *this;
    }
#endif
    ~StudentPtr() { delete home; }                  // the destructor is needed in both variants
    int len() const { return (int)home->str().size() + (int)(regNo & 1); }
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
#ifdef NOCOPY
    StudentPtr a(1, "Salem", 636001);
    StudentPtr b = a;                              // shallow copy: both point to the same Address
    std::cout << b.len() << '\n';
    return 0;                                      // a and b both delete the same Address -> double free
#else
    std::cout << "sizeof(StudentMember)=" << sizeof(StudentMember) << "  sizeof(StudentPtr)=" << sizeof(StudentPtr)
              << "  (+ " << sizeof(Address) << " bytes on the heap per StudentPtr)\n";
    const int N = 2000000;
    volatile long sink = 0;
    double ta = bestOf([&] { long t = 0; for (int i = 0; i < N; ++i) { StudentMember s(i, "Salem", 636001); t += s.len(); } sink = t; });
    double tb = bestOf([&] { long t = 0; for (int i = 0; i < N; ++i) { StudentPtr s(i, "Salem", 636001); t += s.len(); } sink = t; });
    std::cout << "2,000,000 create+use+destroy:  member " << ta << " ms,  pointer " << tb << " ms\n";
#endif
}
