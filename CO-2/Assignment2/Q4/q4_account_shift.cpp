// Q4 - SavingsAccount with an array of the last 10 transactions (shifting design)
#include <iostream>
#include <iomanip>
#include <string>

#ifndef MAXTX
#define MAXTX 10
#endif

struct Transaction {
    int no;                    // running transaction number
    char type;                 // 'D' deposit, 'W' withdrawal
    long long amount;
    long long balanceAfter;
};

class SavingsAccount {
private:                                   // the history must not be touched from outside
    int accountNo;
    long long balance;
    Transaction tx[MAXTX];                 // last MAXTX transactions, oldest first
    int count;                             // how many are stored (0..MAXTX)
    int totalDone;                         // transactions ever made
    void record(char type, long long amount);   // defined outside the class

public:
    // defined inside the class
    SavingsAccount(int no, long long opening) : accountNo(no), balance(opening), count(0), totalDone(0) {}
    long long getBalance() const { return balance; }

    // defined outside the class with ::
    void deposit(long long amount);
    bool withdraw(long long amount);
    void miniStatement() const;
};

void SavingsAccount::record(char type, long long amount)
{
    ++totalDone;
    if (count == MAXTX) {                  // full: shift everything one place left, drop the oldest
        for (int i = 1; i < MAXTX; ++i)
            tx[i - 1] = tx[i];
        --count;
    }
    tx[count++] = Transaction{totalDone, type, amount, balance};
}

void SavingsAccount::deposit(long long amount)
{
    if (amount <= 0) return;
    balance += amount;
    record('D', amount);
}

bool SavingsAccount::withdraw(long long amount)
{
    if (amount <= 0 || amount > balance) return false;   // rejected, not recorded
    balance -= amount;
    record('W', amount);
    return true;
}

void SavingsAccount::miniStatement() const
{
    std::cout << "Mini statement  A/c " << accountNo << "  (last " << count << " of " << totalDone << ")\n";
    std::cout << " No  Type  Amount  Balance\n";
    for (int i = count - 1; i >= 0; --i)   // newest first, like an ATM slip
        std::cout << std::setw(3) << tx[i].no << "   " << tx[i].type << "   "
                  << std::setw(6) << tx[i].amount << "  " << std::setw(7) << tx[i].balanceAfter << '\n';
    std::cout << "Available balance: " << balance << '\n';
}

int main()
{
    SavingsAccount acc(1001, 10000);
    acc.deposit(500);   acc.withdraw(200);  acc.deposit(1500);  acc.deposit(250);
    acc.withdraw(1000); acc.withdraw(300);  acc.deposit(2000);  acc.withdraw(450);
    acc.deposit(100);   acc.withdraw(600);
    std::cout << "--- after 10 transactions ---\n";
    acc.miniStatement();
    acc.deposit(700);                         // 11th transaction: the oldest one must go
    acc.withdraw(1300);                       // 12th
    std::cout << "\n--- after 12 transactions ---\n";
    acc.miniStatement();
    std::cout << "\nwithdraw(99999) accepted? " << std::boolalpha << acc.withdraw(99999) << " (not recorded)\n";
}
