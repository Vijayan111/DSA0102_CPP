// Q4 alternative: std::deque, push_back and pop_front
#include <iostream>
#include <iomanip>
#include <deque>

struct Transaction { int no; char type; long long amount; long long balanceAfter; };

class SavingsAccount {
    int accountNo;
    long long balance;
    std::deque<Transaction> last;
    int totalDone;
    static const std::size_t MAXTX = 10;
    void record(char type, long long amount)
    {
        ++totalDone;
        last.push_back(Transaction{totalDone, type, amount, balance});
        if (last.size() > MAXTX) last.pop_front();      // O(1)
    }
public:
    SavingsAccount(int no, long long opening) : accountNo(no), balance(opening), totalDone(0) {}
    void deposit(long long a)  { balance += a; record('D', a); }
    bool withdraw(long long a) { if (a > balance) return false; balance -= a; record('W', a); return true; }
    void miniStatement() const
    {
        std::cout << "Mini statement  A/c " << accountNo << "  (last " << last.size() << " of " << totalDone << ")\n";
        for (auto it = last.rbegin(); it != last.rend(); ++it)
            std::cout << std::setw(3) << it->no << "   " << it->type << "   "
                      << std::setw(6) << it->amount << "  " << std::setw(7) << it->balanceAfter << '\n';
    }
};

int main()
{
    SavingsAccount acc(1001, 10000);
    acc.deposit(500);   acc.withdraw(200);  acc.deposit(1500);  acc.deposit(250);
    acc.withdraw(1000); acc.withdraw(300);  acc.deposit(2000);  acc.withdraw(450);
    acc.deposit(100);   acc.withdraw(600);  acc.deposit(700);   acc.withdraw(1300);
    acc.miniStatement();
}
