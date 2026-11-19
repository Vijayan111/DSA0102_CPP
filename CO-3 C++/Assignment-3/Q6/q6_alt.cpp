// Q6 alternative: operator+ written with += on a by-value copy, compared on a + b + c
// build 1:  g++ q6_alt.cpp               (no move constructor)
// build 2:  g++ -DTEXT_MOVE q6_alt.cpp   (with a move constructor)
#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
#include "text.h"

static std::size_t g_allocs = 0, g_bytes = 0;
void* operator new(std::size_t n)   { ++g_allocs; g_bytes += n; void* p = std::malloc(n); if (!p) throw std::bad_alloc(); return p; }
void* operator new[](std::size_t n) { ++g_allocs; g_bytes += n; void* p = std::malloc(n); if (!p) throw std::bad_alloc(); return p; }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }
void operator delete[](void* p, std::size_t) noexcept { std::free(p); }

Text plusViaAssign(Text a, const Text& b) { a += b; return a; }       // the alternative operator+

int main()
{
    const int n = 1000;
    std::string s(n, 'a');
    Text a(s.c_str()), b(s.c_str()), c(s.c_str());
    std::string sa = s, sb = s, sc = s;

    g_allocs = g_bytes = 0; Text::resetStats();
    { Text r = a + b + c; (void)r; }
    std::cout << "A  operator+(const&,const&)  : allocations " << g_allocs << ", bytes " << g_bytes
              << ", copy ctors " << Text::copyCtors << ", chars copied " << Text::charsCopied << '\n';

    g_allocs = g_bytes = 0; Text::resetStats();
    { Text r = plusViaAssign(plusViaAssign(a, b), c); (void)r; }
    std::cout << "B  by-value a, a += b         : allocations " << g_allocs << ", bytes " << g_bytes
              << ", copy ctors " << Text::copyCtors << ", chars copied " << Text::charsCopied << '\n';

    g_allocs = g_bytes = 0;
    { std::string r = sa + sb + sc; (void)r; }
    std::cout << "C  std::string  a + b + c     : allocations " << g_allocs << ", bytes " << g_bytes << '\n';
}
