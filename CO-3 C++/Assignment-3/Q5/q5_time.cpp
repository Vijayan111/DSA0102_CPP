// Q5 - Time with ++ (prefix and postfix), == and <, and a Playlist with a checked operator[]
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Time {
    int h, m, s;
public:
    Time(int hh = 0, int mm = 0, int ss = 0) : h(hh), m(mm), s(ss) {}

    int total() const { return h * 3600 + m * 60 + s; }

    Time& operator++()              // prefix: advance, then return the new value (no copy)
    {
        if (++s == 60) {
            s = 0;
            if (++m == 60) { m = 0; ++h; }
        }
        return *this;
    }

    Time operator++(int)            // postfix: the int is a dummy; return the OLD value (a copy)
    {
        Time old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Time& o) const { return total() == o.total(); }
    bool operator<(const Time& o) const { return total() < o.total(); }

    friend std::ostream& operator<<(std::ostream& os, const Time& t)
    {
        char old = os.fill('0');
        os << std::setw(2) << t.h << ':' << std::setw(2) << t.m << ':' << std::setw(2) << t.s;
        os.fill(old);
        return os;
    }
};

struct Track {
    std::string title;
    int seconds;
};

class Playlist {
    std::vector<Track> tracks;
    Track invalid{"<invalid track>", 0};      // returned after an error so the program can go on
public:
    void add(const std::string& t, int sec) { tracks.push_back({t, sec}); }
    int size() const { return (int)tracks.size(); }

    Track& operator[](int i)
    {
        if (i < 0 || i >= size()) {
            std::cout << "  ERROR: index " << i << " is out of range [0, " << size() << ")\n";
            return invalid;
        }
        return tracks[i];
    }
    const Track& operator[](int i) const
    {
        if (i < 0 || i >= size()) {
            std::cout << "  ERROR: index " << i << " is out of range [0, " << size() << ")\n";
            return invalid;
        }
        return tracks[i];
    }
};

void describe(const Playlist& p, int i)      // only the const version can be used here
{
    std::cout << "  const access: " << p[i].title << " (" << p[i].seconds << " s)\n";
}

int main()
{
    std::cout << "--- a = t++ and b = ++t ---\n";
    Time t(0, 0, 5);
    Time a = t++;
    std::cout << "after a = t++ : a = " << a << ", t = " << t << '\n';
    Time b = ++t;
    std::cout << "after b = ++t : b = " << b << ", t = " << t << '\n';

    std::cout << "\n--- roll-over ---\n";
    Time r1(0, 0, 59), r2(0, 59, 59), r3(1, 59, 59);
    std::cout << r1 << " -> " << ++r1 << '\n';
    std::cout << r2 << " -> " << ++r2 << '\n';
    std::cout << r3 << " -> " << ++r3 << '\n';

    std::cout << "\n--- comparisons ---\n";
    Time p(0, 1, 0), q(0, 0, 60), w(0, 1, 1);
    std::cout << std::boolalpha << "00:01:00 == 00:00:60 : " << (p == q) << "\n00:01:00 < 00:01:01  : " << (p < w)
              << "\n00:01:01 < 00:01:00  : " << (w < p) << '\n';

    std::cout << "\n--- playlist ---\n";
    Playlist list;
    list.add("Vaathi Coming", 3);
    list.add("Munbe Vaa", 2);
    list.add("Hukum", 4);
    std::cout << "  list[1] = " << list[1].title << '\n';
    list[1].seconds = 3;                          // non-const version lets us modify
    describe(list, 1);
    std::cout << "playlist[-1]:\n";
    list[-1];
    std::cout << "playlist[size]:\n";
    list[list.size()];

    std::cout << "\n--- short playback simulation ---\n";
    Time now;
    int cur = 0;
    Time endOfTrack(0, 0, list[0].seconds);
    std::cout << "  " << now << "  playing \"" << list[cur].title << "\"\n";
    while (cur < list.size()) {
        ++now;
        if (now == endOfTrack) {
            ++cur;
            if (cur < list.size()) {
                endOfTrack = Time(0, 0, endOfTrack.total() + list[cur].seconds);
                std::cout << "  " << now << "  playing \"" << list[cur].title << "\"\n";
            } else {
                std::cout << "  " << now << "  playlist finished\n";
            }
        }
    }
}
