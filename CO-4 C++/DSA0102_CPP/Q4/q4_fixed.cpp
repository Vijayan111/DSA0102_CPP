// Q4.3 - repaired: virtual rate(), override, virtual destructor, pointers/references instead of copies
#include <iostream>
#include <vector>

class Account {
public:
    Account() { std::cout << "  Account()\n"; }
    Account(const Account&) = delete;            // slicing is now a compile error
    Account& operator=(const Account&) = delete;
    virtual ~Account() { std::cout << "  ~Account()\n"; }
    virtual double rate() const { return 3.5; }
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    SeniorAccount() { std::cout << "  SeniorAccount() allocated 800 bytes\n"; }
    ~SeniorAccount() override { delete[] history; std::cout << "  ~SeniorAccount() released 800 bytes\n"; }
    double rate() const override { return 4.0; }
};

void show(const Account& a) { std::cout << "reference sees " << a.rate() << "\n"; }   // by reference: no slicing

int main()
{
    Account* accounts[2] = { new Account, new SeniorAccount };
    std::cout << "rates through Account*:\n";
    for (Account* a : accounts) std::cout << a->rate() << "\n";
    show(*accounts[1]);
    std::cout << "deleting through Account*:\n";
    for (Account* a : accounts) delete a;

    // Account copy = SeniorAccount();   // error: use of deleted function 'Account::Account(const Account&)'
    std::vector<Account*> v;                    // pointers, not copies
    v.push_back(new SeniorAccount);
    std::cout << "v[0]->rate() = " << v[0]->rate() << "\n";
    for (Account* a : v) delete a;
    std::cout << "end of main\n";
}
