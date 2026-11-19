// Q3: memory and allocation count of three seat-map designs for three sizes
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>
#include <vector>

static size_t g_calls = 0, g_bytes = 0;
void* operator new(size_t n)   { ++g_calls; g_bytes += n; void* p = std::malloc(n ? n : 1); if (!p) throw std::bad_alloc(); return p; }
void* operator new[](size_t n) { ++g_calls; g_bytes += n; void* p = std::malloc(n ? n : 1); if (!p) throw std::bad_alloc(); return p; }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p, size_t) noexcept { std::free(p); }
void operator delete[](void* p, size_t) noexcept { std::free(p); }

static double ms(std::chrono::steady_clock::time_point s)
{
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - s).count();
}

int main()
{
    int sizes[3][2] = {{10, 20}, {100, 200}, {1000, 2000}};
    std::cout << "design                 size        allocations   bytes requested   build+free ms\n";
    for (auto& sz : sizes) {
        int R = sz[0], S = sz[1];
        char label[32]; std::snprintf(label, sizeof label, "%d x %d", R, S);
        {   // 1) array of row pointers (the Q3 design)
            g_calls = g_bytes = 0; auto t = std::chrono::steady_clock::now();
            char** m = new char*[R];
            for (int i = 0; i < R; ++i) { m[i] = new char[S]; std::memset(m[i], '.', S); }
            volatile char c = m[R - 1][S - 1]; (void)c;
            for (int i = 0; i < R; ++i) delete[] m[i];
            delete[] m;
            std::printf("%-22s %-11s %-13zu %-17zu %.3f\n", "row pointers (new[])", label, g_calls, g_bytes, ms(t));
        }
        {   // 2) one block, index r*S+s
            g_calls = g_bytes = 0; auto t = std::chrono::steady_clock::now();
            char* m = new char[(size_t)R * S];
            std::memset(m, '.', (size_t)R * S);
            volatile char c = m[(size_t)(R - 1) * S + S - 1]; (void)c;
            delete[] m;
            std::printf("%-22s %-11s %-13zu %-17zu %.3f\n", "one block", label, g_calls, g_bytes, ms(t));
        }
        {   // 3) vector<vector<char>>
            g_calls = g_bytes = 0; auto t = std::chrono::steady_clock::now();
            {
                std::vector<std::vector<char>> m(R, std::vector<char>(S, '.'));
                volatile char c = m[R - 1][S - 1]; (void)c;
            }
            std::printf("%-22s %-11s %-13zu %-17zu %.3f\n", "vector<vector<char>>", label, g_calls, g_bytes, ms(t));
        }
    }
}
