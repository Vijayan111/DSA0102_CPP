// Q3.4 - effect of 'virtual' on output and on sizeof. Build with and without -DNOVIRTUAL
#include <iostream>
#ifdef NOVIRTUAL
#define VIRT
#else
#define VIRT virtual
#endif

struct Person { int id; Person(int i) : id(i) { std::cout << "Person "; } };
struct Student : VIRT Person { double cgpa; Student(int i, double c) : Person(i), cgpa(c) { std::cout << "Student "; } };
struct Staff   : VIRT Person { double salary; Staff(int i, double s) : Person(i), salary(s) { std::cout << "Staff "; } };
struct TeachingAssistant : Student, Staff {
    TeachingAssistant(int i, double c, double s)
#ifndef NOVIRTUAL
        : Person(i), Student(i, c), Staff(i, s)
#else
        : Student(i, c), Staff(i, s)
#endif
    { std::cout << "TA "; }
};

int main()
{
    TeachingAssistant ta(7, 8.5, 20000);
    std::cout << '\n' << "sizeof(Student)=" << sizeof(Student) << " sizeof(Staff)=" << sizeof(Staff)
              << " sizeof(TeachingAssistant)=" << sizeof(TeachingAssistant) << '\n';
}
