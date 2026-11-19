// Q4.1/4.2 - the program from the question with trace output added to the constructors/destructors
#include <iostream>
#include <vector>

class Account {
public:
    Account() { std::cout << "  Account()\n"; }
    double rate() const { return 3.5; }
    ~Account() { std::cout << "  ~Account()\n"; }
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    SeniorAccount() { std::cout << "  SeniorAccount() allocated 800 bytes\n"; }
    double rate() const { return 4.0; }
    ~SeniorAccount() { delete[] history; std::cout << "  ~SeniorAccount() released 800 bytes\n"; }
};

int main()
{
    Account* accounts[2] = { new Account, new SeniorAccount };
    std::cout << "rates through Account*:\n";
    for (Account* a : accounts) std::cout << a->rate() << "\n";
    std::cout << "deleting through Account*:\n";
    for (Account* a : accounts) delete a;

    std::cout << "slicing:\n";
    Account copy = SeniorAccount();          // stored in a vector<Account> elsewhere
    std::cout << "copy.rate() = " << copy.rate() << "\n";
    std::vector<Account> v;
    v.push_back(SeniorAccount());
    std::cout << "v[0].rate()  = " << v[0].rate() << "\n";
    std::cout << "end of main\n";
}
