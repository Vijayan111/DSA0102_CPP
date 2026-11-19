// Q2: self-assignment p = p with and without the guard
#include <iostream>
#include <string>

class Good {
    int n; std::string* m;
public:
    explicit Good(int c) : n(c), m(new std::string[c]) {}
    Good(const Good& o) : n(o.n), m(new std::string[o.n]) { for (int i = 0; i < n; ++i) m[i] = o.m[i]; }
    Good& operator=(const Good& o)
    {
        if (this == &o) return *this;
        std::string* f = new std::string[o.n];
        for (int i = 0; i < o.n; ++i) f[i] = o.m[i];
        delete[] m; m = f; n = o.n;
        return *this;
    }
    ~Good() { delete[] m; }
    void set(int i, const std::string& s) { m[i] = s; }
    std::string get(int i) const { return m[i]; }
};

class Bad {                                   // no guard, releases the old array first
    int n; std::string* m;
public:
    explicit Bad(int c) : n(c), m(new std::string[c]) {}
    Bad(const Bad& o) : n(o.n), m(new std::string[o.n]) { for (int i = 0; i < n; ++i) m[i] = o.m[i]; }
    Bad& operator=(const Bad& o)
    {
        delete[] m;                           // if &o == this, o.m is gone now
        n = o.n;
        m = new std::string[n];
        for (int i = 0; i < n; ++i) m[i] = o.m[i];
        return *this;
    }
    ~Bad() { delete[] m; }
    void set(int i, const std::string& s) { m[i] = s; }
    std::string get(int i) const { return m[i]; }
};

int main()
{
#ifdef USE_BAD
    Bad p(2);
    p.set(0, "Paracetamol"); p.set(1, "ORS");
    Bad& alias = p;
#else
    Good p(2);
    p.set(0, "Paracetamol"); p.set(1, "ORS");
    Good& alias = p;
#endif
    p = alias;                                // self-assignment
    std::cout << "after p = p : " << p.get(0) << ' ' << p.get(1) << '\n';
}
