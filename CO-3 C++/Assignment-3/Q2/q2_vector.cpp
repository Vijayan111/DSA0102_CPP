// Q2 alternative: Rule of Zero - std::vector<std::string> inside, no special members written
#include <iostream>
#include <string>
#include <vector>

class Prescription {
    std::vector<std::string> medicines;
public:
    explicit Prescription(int count) : medicines(count) {}
    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
};

int main()
{
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");
    Prescription q = p;
    q.set(1, "Cetirizine");
    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");
    std::cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1)
              << " | " << r.get(0) << ' ' << r.get(1) << '\n';
}
