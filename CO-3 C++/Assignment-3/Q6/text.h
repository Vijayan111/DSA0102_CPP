// Text - a small string class with its own dynamic character array
#pragma once
#include <cstddef>
#include <cstring>
#include <iostream>

class Text {
    char* data;
    std::size_t len;
public:
    static std::size_t copyCtors, charsCopied;          // counters used by the experiments
    static void resetStats() { copyCtors = charsCopied = 0; }

    Text(const char* s = "") : data(nullptr), len(std::strlen(s))
    {
        data = new char[len + 1];
        std::memcpy(data, s, len + 1);
        charsCopied += len;
    }

    Text(const Text& o) : data(new char[o.len + 1]), len(o.len)       // copy constructor
    {
        std::memcpy(data, o.data, len + 1);
        ++copyCtors;
        charsCopied += len;
    }

#ifdef TEXT_MOVE
    Text(Text&& o) noexcept : data(o.data), len(o.len) { o.data = new char[1]{'\0'}; o.len = 0; }
#endif

    Text& operator=(const Text& o)                                    // copy assignment
    {
        if (this == &o) return *this;                                 // self-assignment guard
        char* fresh = new char[o.len + 1];                            // build the new array first
        std::memcpy(fresh, o.data, o.len + 1);
        charsCopied += o.len;
        delete[] data;                                                // then release the old one
        data = fresh;
        len = o.len;
        return *this;
    }

    ~Text() { delete[] data; }

    std::size_t size() const { return len; }
    const char* c_str() const { return data; }

    Text& operator+=(const Text& o)
    {
        char* fresh = new char[len + o.len + 1];
        std::memcpy(fresh, data, len);
        std::memcpy(fresh + len, o.data, o.len + 1);
        charsCopied += len + o.len;
        delete[] data;
        data = fresh;
        len += o.len;
        return *this;
    }

    friend Text operator+(const Text& a, const Text& b)               // concatenation
    {
        Text r;
        delete[] r.data;
        r.len = a.len + b.len;
        r.data = new char[r.len + 1];
        std::memcpy(r.data, a.data, a.len);
        std::memcpy(r.data + a.len, b.data, b.len + 1);               // +1 copies the '\0' too
        charsCopied += r.len;
        return r;
    }

    friend bool operator==(const Text& a, const Text& b) { return a.len == b.len && std::strcmp(a.data, b.data) == 0; }
    friend bool operator!=(const Text& a, const Text& b) { return !(a == b); }
    friend std::ostream& operator<<(std::ostream& os, const Text& t) { return os << t.data; }
};

inline std::size_t Text::copyCtors = 0;
inline std::size_t Text::charsCopied = 0;
