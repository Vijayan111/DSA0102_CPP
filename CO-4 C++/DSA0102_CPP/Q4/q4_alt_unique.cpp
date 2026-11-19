// Q4 alternative: std::vector<std::unique_ptr<Account>> instead of raw pointers deleted by hand
// build with -DVIRTUAL_DTOR to apply the destructor fix
#include <iostream>
#include <memory>
#include <vector>
#ifdef VIRTUAL_DTOR
#define VDTOR virtual
#else
#define VDTOR
#endif

class Account {
public:
    VDTOR ~Account() {}
    virtual double rate() const { return 3.5; }
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    ~SeniorAccount() { delete[] history; std::cout << "  ~SeniorAccount() ran\n"; }
    double rate() const override { return 4.0; }
};

int main()
{
    std::vector<std::unique_ptr<Account>> v;
    v.push_back(std::make_unique<Account>());
    v.push_back(std::make_unique<SeniorAccount>());
    for (auto& a : v) std::cout << a->rate() << "\n";
    Account sliced = *v[1];                      // unique_ptr does NOT stop slicing by copy
    std::cout << "sliced copy rate = " << sliced.rate() << "\n";
    std::cout << "sizeof(raw pointer)=" << sizeof(Account*) << "  sizeof(unique_ptr)=" << sizeof(std::unique_ptr<Account>) << "\n";
}
