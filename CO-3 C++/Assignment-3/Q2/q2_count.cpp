// Q2: counting copy-constructor calls (by value, by const reference, return by value)
#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;
public:
    static int copies;
    explicit Prescription(int count) : n(count), medicines(new std::string[count]) {}
    Prescription(const Prescription& o) : n(o.n), medicines(new std::string[o.n])
    {
        ++copies;
        std::cout << "    [copy constructor called]\n";
        for (int i = 0; i < n; ++i) medicines[i] = o.medicines[i];
    }
    Prescription& operator=(const Prescription&) = delete;
    ~Prescription() { delete[] medicines; }
    void set(int i, const std::string& m) { medicines[i] = m; }
};
int Prescription::copies = 0;

void byValue(Prescription p)            { (void)p; }
void byConstRef(const Prescription& p)  { (void)p; }
Prescription make(int k) { Prescription local(k); local.set(0, "ORS"); return local; }

int main()
{
    Prescription p(3);
    std::cout << "1) Prescription q = p;\n";
    Prescription q = p;
    std::cout << "2) byValue(p);\n";
    byValue(p);
    std::cout << "3) byConstRef(p);\n";
    byConstRef(p);
    std::cout << "4) Prescription r = make(3);   (return by value)\n";
    Prescription r = make(3);
    std::cout << "total copy-constructor calls: " << Prescription::copies << '\n';
}
