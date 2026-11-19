// Q2 step 1: Prescription WITHOUT a copy constructor (compiler copies the pointer only)
#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;
public:
    explicit Prescription(int count) : n(count), medicines(new std::string[count]) {}
    ~Prescription() { delete[] medicines; }
    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
    int size() const { return n; }
};

int main()
{
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;                 // shallow copy: q.medicines == p.medicines
    q.set(1, "Cetirizine");             // doctor edits the follow-up copy

    std::cout << "original p : " << p.get(0) << ' ' << p.get(1) << '\n';
    std::cout << "follow-up q: " << q.get(0) << ' ' << q.get(1) << '\n';
    std::cout << "end of main, destructors run now\n" << std::flush;
}
