// fleet.h - the fleet is an array of base-class pointers
#pragma once
#include <iomanip>
#include <iostream>
#include "vehicles.h"

class Fleet {
    static const int MAXV = 20;
    Vehicle* v[MAXV];
    int count = 0;
    Vehicle* find(const std::string& reg) const
    {
        for (int i = 0; i < count; ++i) if (v[i]->getReg() == reg) return v[i];
        return nullptr;
    }
public:
    Fleet() = default;
    Fleet(const Fleet&) = delete;
    Fleet& operator=(const Fleet&) = delete;
    ~Fleet() { for (int i = 0; i < count; ++i) delete v[i]; }       // virtual destructors make this safe

    bool add(Vehicle* x) { if (count == MAXV) { delete x; return false; } v[count++] = x; return true; }

    bool rent(const std::string& reg, const Date& today)
    {
        Vehicle* x = find(reg);
        if (!x)                       { std::cout << "  rent " << reg << ": REFUSED (not in fleet)\n"; return false; }
        if (!x->rentable(today))      { std::cout << "  rent " << reg << ": REFUSED (" << (x->isRented() ? "already rented" : "service overdue") << ")\n"; return false; }
        x->setRented(true);
        std::cout << "  rent " << reg << ": OK (" << x->type() << ")\n";
        return true;
    }

    double giveBack(const std::string& reg, int days, int lateDays, double used)
    {
        Vehicle* x = find(reg);
        if (!x || !x->isRented() || days <= 0 || lateDays < 0 || used < 0) {
            std::cout << "  return " << reg << ": REFUSED\n";
            return -1;
        }
        double bill = x->charge(days, lateDays, used);          // run-time dispatch
        x->setRented(false);
        std::cout << "  return " << std::left << std::setw(10) << reg << std::setw(13) << x->type() << std::right
                  << days << " days, " << lateDays << " late, used " << std::setw(3) << used << "  -> Rs " << std::setw(6) << bill << '\n';
        return bill;
    }

    void list() const
    {
        for (int i = 0; i < count; ++i)
            std::cout << "  " << std::left << std::setw(13) << v[i]->type() << std::setw(11) << v[i]->getReg()
                      << std::right << "Rs " << std::setw(5) << v[i]->getRate() << "/day  "
                      << (v[i]->isRented() ? "RENTED     " : "available  ") << v[i]->details() << '\n';
    }
};
