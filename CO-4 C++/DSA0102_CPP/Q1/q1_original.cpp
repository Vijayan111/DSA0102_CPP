// Q1 - the three original classes exactly as given (evidence for the diagnosis)
#include <iostream>
#include <string>
using std::string;

class Professor { public: string name; int id; double basic; double da; double research;
                  double pay() { return basic + basic * 0.42 + research; } };

class LabAssistant { public: string name; int id; double basic; double da;
                     double pay() { return basic + basic * 0.42; } };

class GuestFaculty { public: string nm; int code; double hours; double rate;
                     double pay() { return hours * rate; } };

int main()
{
    Professor p;  p.name = "Dr. Meena"; p.id = 101; p.basic = 50000; p.da = 99999; p.research = 10000;
    LabAssistant l; l.name = "Ravi"; l.id = 102; l.basic = 20000; l.da = 0;
    GuestFaculty g; g.nm = "Anand"; g.code = 201; g.hours = 12; g.rate = 1500;

    std::cout << "Professor pay (da field = 99999) : " << p.pay() << '\n';
    p.da = 0;
    std::cout << "Professor pay (da field = 0)     : " << p.pay() << '\n';
    std::cout << "p.id = -5 is accepted silently   : " << (p.id = -5) << '\n';

    // three different types: no common array / loop is possible, three separate blocks are needed
    double total = p.pay();
    total += l.pay();
    total += g.pay();
    std::cout << "total (three separate calls)     : " << total << '\n';
}
