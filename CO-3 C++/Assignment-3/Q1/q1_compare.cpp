// Q1 alternative: cost of creating objects, overloads + delegation versus default arguments
#include <chrono>
#include <iostream>
#include <string>

struct BookA {                       // overloaded constructors with delegation
    std::string title, author; int copies;
    BookA(const std::string& t, const std::string& a, int c) : title(t), author(a), copies(c < 0 ? 0 : c) {}
    explicit BookA(const std::string& t) : BookA(t, "Unknown", 1) {}
    BookA() : BookA("Untitled", "Unknown", 0) {}
};
struct BookB {                       // one constructor with default arguments
    std::string title, author; int copies;
    BookB(const std::string& t = "Untitled", int c = 0, const std::string& a = "Unknown")
        : title(t), author(a), copies(c < 0 ? 0 : c) {}
};

template <class F> double timeMs(F f)
{
    auto s = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - s).count();
}

int main()
{
    const int N = 5000000;
    long long sink = 0;
    double a = timeMs([&] { for (int i = 0; i < N; ++i) { BookA b("Dune", "Herbert", i & 7); sink += b.copies; asm volatile("" ::: "memory"); } });
    double b = timeMs([&] { for (int i = 0; i < N; ++i) { BookB b("Dune", i & 7, "Herbert"); sink += b.copies; asm volatile("" ::: "memory"); } });
    std::cout << "objects created      : " << N << '\n';
    std::cout << "overloads+delegation : " << a << " ms\n";
    std::cout << "default arguments    : " << b << " ms\n";
    std::cout << "(checksum " << sink << ")\n";
    std::cout << "sizeof(BookA) = " << sizeof(BookA) << ", sizeof(BookB) = " << sizeof(BookB) << " bytes\n";
}
