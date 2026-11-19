// Q1.2 - Repaired design: common base class, protected/private data, pay() overridden
#include <iomanip>
#include <iostream>
#include <string>

const double DA_RATE = 0.42;                 // dearness allowance = 42% of basic (one place only)

class Staff {                                // abstract base: what every staff member has
    std::string name;
    int id;
public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;
    const std::string& getName() const { return name; }
    int getId() const { return id; }
    virtual double pay() const = 0;          // every category must define its own pay rule
    virtual const char* category() const = 0;
};

class SalariedStaff : public Staff {         // shared rule: basic + DA
    double basic;
protected:
    double salary() const { return basic + basic * DA_RATE; }
public:
    SalariedStaff(const std::string& n, int i, double b) : Staff(n, i), basic(b) {}
};

class Professor : public SalariedStaff {
    double research;
public:
    Professor(const std::string& n, int i, double b, double r) : SalariedStaff(n, i, b), research(r) {}
    double pay() const override { return salary() + research; }
    const char* category() const override { return "Professor"; }
};

class LabAssistant : public SalariedStaff {
public:
    LabAssistant(const std::string& n, int i, double b) : SalariedStaff(n, i, b) {}
    double pay() const override { return salary(); }
    const char* category() const override { return "Lab Assistant"; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(const std::string& n, int i, double h, double r) : Staff(n, i), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
    const char* category() const override { return "Guest Faculty"; }
};

// ---- a NEW category, added later: no existing class is edited ----
class Librarian : public SalariedStaff {
public:
    Librarian(const std::string& n, int i, double b) : SalariedStaff(n, i, b) {}
    double pay() const override { return salary(); }
    const char* category() const override { return "Librarian"; }
};

int main()
{
    Staff* list[4] = {
        new Professor("Dr. Meena", 101, 50000, 10000),
        new LabAssistant("Ravi", 102, 20000),
        new GuestFaculty("Anand", 201, 12, 1500),
        new Librarian("Sita", 103, 30000)
    };

    std::cout << std::fixed << std::setprecision(2);
    double total = 0;
    for (Staff* s : list) {                  // ONE loop for every category
        std::cout << std::left << std::setw(15) << s->category() << std::setw(12) << s->getName()
                  << std::right << std::setw(10) << s->pay() << '\n';
        total += s->pay();
    }
    std::cout << "Total payroll  : " << total << '\n';

    for (Staff* s : list) delete s;          // safe: ~Staff is virtual
}
