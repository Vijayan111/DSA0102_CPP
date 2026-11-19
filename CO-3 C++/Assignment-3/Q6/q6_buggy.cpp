// Q6: first version of operator+ - forgot the room for the '\0'
#include <cstring>
#include <iostream>

class Text {
    char* data; std::size_t len;
public:
    Text(const char* s = "") : data(new char[std::strlen(s) + 1]), len(std::strlen(s)) { std::strcpy(data, s); }
    Text(const Text& o) : data(new char[o.len + 1]), len(o.len) { std::strcpy(data, o.data); }
    ~Text() { delete[] data; }
    friend Text operator+(const Text& a, const Text& b)
    {
        Text r;
        delete[] r.data;
        r.len = a.len + b.len;
        r.data = new char[r.len];                // BUG: should be r.len + 1
        std::strcpy(r.data, a.data);
        std::strcat(r.data, b.data);
        return r;
    }
    const char* c_str() const { return data; }
};

int main()
{
    Text a("Hello"), b("World");
    Text c = a + b;
    std::cout << c.c_str() << '\n';
}
