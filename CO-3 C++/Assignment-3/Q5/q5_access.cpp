// Q5 alternative: unchecked [], checked [] (prints error), and at() that throws
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

struct Track { int seconds; };

class Playlist {
    std::vector<Track> t;
    Track bad{0};
public:
    explicit Playlist(int n) : t(n, Track{3}) {}
    int size() const { return (int)t.size(); }
    Track& unchecked(int i) { return t[i]; }
    Track& operator[](int i) { if (i < 0 || i >= size()) { std::cout << "ERROR\n"; return bad; } return t[i]; }
    Track& at(int i) { if (i < 0 || i >= size()) throw std::out_of_range("playlist index out of range"); return t[i]; }
};

template <class F> double ms(F f)
{
    auto s = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - s).count();
}

int main()
{
    Playlist p(1000);
    long long sum = 0;
    const int N = 10000000;
    double a = ms([&] { for (int i = 0; i < N; ++i) sum += p.unchecked(i % 1000).seconds; });
    double b = ms([&] { for (int i = 0; i < N; ++i) sum += p[i % 1000].seconds; });
    double c = ms([&] { for (int i = 0; i < N; ++i) sum += p.at(i % 1000).seconds; });
    std::cout << "10,000,000 accesses (ms)\n";
    std::cout << "unchecked        : " << a << '\n';
    std::cout << "checked, prints  : " << b << '\n';
    std::cout << "at(), throws     : " << c << '\n';
    std::cout << "(check " << sum << ")\n";
    try { p.at(1000); } catch (const std::out_of_range& e) { std::cout << "at(1000) threw: " << e.what() << '\n'; }
}
