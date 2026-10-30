// Q4 - same class, circular index instead of shifting
#include <iostream>
#include <iomanip>

#ifndef MAXTX
#define MAXTX 10
#endif

struct Transaction {
    int no;
    char type;
    long long amount;
    long long balanceAfter;
};

class SavingsAccount {
private:
    int accountNo;
    long long balance;
    Transaction tx[MAXTX];
    int start;                             // index of the oldest stored transaction
    int count;
    int totalDone;
    void record(char type, long long amount);

public:
    SavingsAccount(int no, long long opening) : accountNo(no), balance(opening), start(0), count(0), totalDone(0) {}
    long long getBalance() const { return balance; }
    void deposit(long long amount);
    bool withdraw(long long amount);
    void miniStatement() const;
};

void SavingsAccount::record(char type, long long amount)
{
    ++totalDone;
    Transaction t{totalDone, type, amount, balance};
    if (count < MAXTX) {
        tx[(start + count) % MAXTX] = t;   // still room
        ++count;
    } else {
        tx[start] = t;                     // overwrite the oldest, nothing moves
        start = (start + 1) % MAXTX;
    }
}

void SavingsAccount::deposit(long long amount)
{
    if (amount <= 0) return;
    balance += amount;
    record('D', amount);
}

bool SavingsAccount::withdraw(long long amount)
{
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    record('W', amount);
    return true;
}

void SavingsAccount::miniStatement() const
{
    std::cout << "Mini statement  A/c " << accountNo << "  (last " << count << " of " << totalDone
              << ", start index " << start << ")\n";
    std::cout << " No  Type  Amount  Balance\n";
    for (int i = count - 1; i >= 0; --i) {
        const Transaction& t = tx[(start + i) % MAXTX];
        std::cout << std::setw(3) << t.no << "   " << t.type << "   "
                  << std::setw(6) << t.amount << "  " << std::setw(7) << t.balanceAfter << '\n';
    }
    std::cout << "Available balance: " << balance << '\n';
}

int main()
{
    SavingsAccount acc(1001, 10000);
    acc.deposit(500);   acc.withdraw(200);  acc.deposit(1500);  acc.deposit(250);
    acc.withdraw(1000); acc.withdraw(300);  acc.deposit(2000);  acc.withdraw(450);
    acc.deposit(100);   acc.withdraw(600);
    acc.deposit(700);
    acc.withdraw(1300);
    acc.miniStatement();
}
