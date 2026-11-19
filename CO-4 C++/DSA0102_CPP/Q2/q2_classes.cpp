// Q2.3 - University people: class declarations with access specifiers
#include <iostream>
#include <string>

class Person {                                   // common data of every person
protected:
    std::string name;
    int id;
    std::string phone;
public:
    Person(const std::string& n, int i, const std::string& p) : name(n), id(i), phone(p) {}
    virtual ~Person() = default;
    const std::string& getName() const { return name; }
};

class Student : virtual public Person {          // is-a Person, public, virtual base
protected:
    std::string programme;
    double cgpa;
public:
    Student(const std::string& n, int i, const std::string& p, const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {}
};

class Staff : virtual public Person {            // is-a Person, public, virtual base
protected:
    std::string department;
    double salary;
public:
    Staff(const std::string& n, int i, const std::string& p, const std::string& d, double s)
        : Person(n, i, p), department(d), salary(s) {}
};

class TeachingAssistant : public Student, public Staff {   // is-a Student AND is-a Staff
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double c, const std::string& d, double s)
        : Person(n, i, p), Student(n, i, p, prog, c), Staff(n, i, p, d, s) {}
    void show() const {
        std::cout << name << " (id " << id << ") " << programme << " CGPA " << cgpa
                  << ", " << department << " Rs " << salary << '\n';   // 'name' is unambiguous
    }
};

class Fellowship {                               // member class: a scholar HAS a fellowship
    std::string agency;
    double monthly;
public:
    Fellowship(const std::string& a, double m) : agency(a), monthly(m) {}
    void show() const { std::cout << agency << " Rs " << monthly << "/month"; }
};

class ResearchScholar : public Student {         // is-a Student, has-a Fellowship
    Fellowship fellowship;
public:
    ResearchScholar(const std::string& n, int i, const std::string& p, const std::string& prog, double c,
                    const std::string& agency, double m)
        : Person(n, i, p), Student(n, i, p, prog, c), fellowship(agency, m) {}
    void show() const { std::cout << name << " - " << programme << ", fellowship "; fellowship.show(); std::cout << '\n'; }
};

int main()
{
    TeachingAssistant ta("Kavya", 1, "9000011111", "MTech CSE", 8.7, "CSE Dept", 15000);
    ta.show();
    ResearchScholar rs("Arun", 2, "9000022222", "PhD CSE", 9.1, "UGC", 31000);
    rs.show();
    std::cout << ta.getName() << ": sizeof(Person)=" << sizeof(Person) << ", sizeof(TeachingAssistant)="
              << sizeof(TeachingAssistant) << "\n";
}
