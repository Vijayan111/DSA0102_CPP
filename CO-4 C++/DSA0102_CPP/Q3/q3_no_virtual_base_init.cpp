// Q3.1 evidence - TeachingAssistant does NOT name the virtual base Person in its initializer list (this file is SUPPOSED to fail)
#include <iostream>
#include <string>

class Address {                                   // member class of Person
    std::string city; int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) { std::cout << "  Address(" << city << ")\n"; }
    ~Address() { std::cout << "  ~Address\n"; }
};

class Course {                                    // member class of Student
    std::string code; int credits;
public:
    Course(const std::string& c, int cr) : code(c), credits(cr) { std::cout << "  Course(" << code << ")\n"; }
    ~Course() { std::cout << "  ~Course\n"; }
};

class Person {
protected:
    std::string name; int id;
    Address addr;                                 // has-a
public:
    Person(const std::string& n, int i, const std::string& city, int pin) : name(n), id(i), addr(city, pin)
    { std::cout << "  Person(" << name << ")\n"; }
    virtual ~Person() { std::cout << "  ~Person\n"; }
};

class Student : virtual public Person {
protected:
    std::string programme; Course course;         // has-a
public:
    Student(const std::string& n, int i, const std::string& city, int pin,
            const std::string& prog, const std::string& ccode, int cr)
        : Person(n, i, city, pin), programme(prog), course(ccode, cr)
    { std::cout << "  Student\n"; }
    ~Student() { std::cout << "  ~Student\n"; }
};

class Staff : virtual public Person {
protected:
    std::string department; double salary;
public:
    Staff(const std::string& n, int i, const std::string& city, int pin, const std::string& d, double s)
        : Person(n, i, city, pin), department(d), salary(s)
    { std::cout << "  Staff\n"; }
    ~Staff() { std::cout << "  ~Staff\n"; }
};

class TeachingAssistant : public Student, public Staff {
public:
    // the most-derived class calls the virtual base itself ("TA-Person"); the Person(...) calls
    // inside Student and Staff (with "ignored") are skipped
    TeachingAssistant(const std::string& n, int i, const std::string& city, int pin)
        : Student("ignored-1", 0, "none", 0, "MTech", "CS501", 4),
          Staff("ignored-2", 0, "none", 0, "CSE", 15000)
    { std::cout << "  TeachingAssistant\n"; }
    ~TeachingAssistant() { std::cout << "  ~TeachingAssistant\n"; }
};

int main()
{
    std::cout << "--- Student object\n";
    { Student s("Asha", 11, "Salem", 636001, "BTech", "CS301", 3); }
    std::cout << "--- Staff object\n";
    { Staff f("Bala", 12, "Chennai", 600001, "CSE", 40000); }
    std::cout << "--- TeachingAssistant object\n";
    { TeachingAssistant t("Kavya", 13, "Madurai", 625001); }
}
