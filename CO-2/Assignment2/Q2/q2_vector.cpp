// Q2 - changed condition: the register is a std::vector that can grow
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {72, 85, 91};            // capacity 3
    int& ref = v[2];                              // reference to the highest mark
    int* ptr = &v[2];                             // pointer to the highest mark
    std::size_t idx = 2;                          // index of the highest mark
    const int* oldBuffer = v.data();

    std::cout << "capacity before push_back : " << v.capacity() << '\n';
    v.push_back(64);                              // full -> new bigger buffer, old one freed
    std::cout << "capacity after push_back  : " << v.capacity() << '\n';
    std::cout << "buffer moved to new address: " << std::boolalpha << (oldBuffer != v.data()) << '\n';
    std::cout << "pointer still points into the vector? " << (ptr == &v[2]) << '\n';
    std::cout << "index still valid, v[idx] = " << v[idx] << '\n';
    v[idx] += 2;                                  // safe moderation through the index
    std::cout << "after v[idx] += 2        : " << v[idx] << '\n';
    (void)ref;                                    // we do NOT touch ref or ptr: they dangle now
}
