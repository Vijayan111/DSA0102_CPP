// Q2.2 evidence - without virtual a TeachingAssistant has TWO Person parts (this file is SUPPOSED to fail)
#include <string>
struct Person { std::string name; };
struct Student : Person {};
struct Staff : Person {};
struct TeachingAssistant : Student, Staff {};
int main()
{
    TeachingAssistant ta;
    ta.name = "Kavya";
}
