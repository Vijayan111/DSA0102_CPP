// Q3 alternative: time to touch every seat once (O(1) per access) - row pointers versus one block
#include <chrono>
#include <cstring>
#include <iostream>

int main()
{
    const int R = 1000, S = 2000;
    char** a = new char*[R];
    for (int i = 0; i < R; ++i) { a[i] = new char[S]; std::memset(a[i], '.', S); }
    char* b = new char[(size_t)R * S];
    std::memset(b, '.', (size_t)R * S);

    long long c1 = 0, c2 = 0;
    auto t = std::chrono::steady_clock::now();
    for (int rep = 0; rep < 20; ++rep)
        for (int r = 0; r < R; ++r)
            for (int s = 0; s < S; ++s) c1 += (a[r][s] == '.');
    double t1 = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t).count();

    t = std::chrono::steady_clock::now();
    for (int rep = 0; rep < 20; ++rep)
        for (int r = 0; r < R; ++r)
            for (int s = 0; s < S; ++s) c2 += (b[(size_t)r * S + s] == '.');
    double t2 = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t).count();

    std::cout << "40,000,000 seat reads (1000 x 2000, 20 sweeps)\n";
    std::cout << "row pointers a[r][s]   : " << t1 << " ms  (count " << c1 << ")\n";
    std::cout << "one block b[r*S+s]     : " << t2 << " ms  (count " << c2 << ")\n";
    for (int i = 0; i < R; ++i) delete[] a[i];
    delete[] a; delete[] b;
}
