// Q1 alternative analysis: how much is copied per call, and how long does it take?
#include <iostream>
#include <chrono>

struct Student {
    char name[64];
    int marks[100];
    long long fee;
};

__attribute__((noipa)) long long byValue(Student s)          { return s.fee + s.marks[3]; }
__attribute__((noipa)) long long byRef(Student& s)           { return s.fee + s.marks[3]; }
__attribute__((noipa)) long long byConstRef(const Student& s){ return s.fee + s.marks[3]; }
__attribute__((noipa)) long long byLong(long long fee)       { return fee + 1; }

template <class F> double timeIt(F f)
{
    auto t0 = std::chrono::steady_clock::now();
    f();
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main()
{
    std::cout << "sizeof(long long) = " << sizeof(long long) << " bytes\n";
    std::cout << "sizeof(Student)   = " << sizeof(Student) << " bytes\n";
    std::cout << "sizeof(Student*)  = " << sizeof(Student*) << " bytes (what a reference costs in practice)\n\n";

    static Student s[64];
    for (int k = 0; k < 64; ++k) { s[k].fee = 45000 + k; s[k].marks[3] = 7; }
    const int N = 20000000;
    volatile long long sink = 0;

    double t1 = timeIt([&] { long long r = 0; for (int i = 0; i < N; ++i) r += byLong(s[i & 63].fee);     sink = r; });
    double t2 = timeIt([&] { long long r = 0; for (int i = 0; i < N; ++i) r += byValue(s[i & 63]);         sink = r; });
    double t3 = timeIt([&] { long long r = 0; for (int i = 0; i < N; ++i) r += byRef(s[i & 63]);           sink = r; });
    double t4 = timeIt([&] { long long r = 0; for (int i = 0; i < N; ++i) r += byConstRef(s[i & 63]);      sink = r; });

    std::cout << N << " calls each:\n";
    std::cout << "  long long by value   : " << t1 << " ms\n";
    std::cout << "  Student by value     : " << t2 << " ms\n";
    std::cout << "  Student by reference : " << t3 << " ms\n";
    std::cout << "  Student by const ref : " << t4 << " ms\n";
}
