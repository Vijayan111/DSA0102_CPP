// Q6: copies made while evaluating a + b + c (n1 = n2 = n3 = 1000 characters)
#include <iostream>
#include <string>
#include "text.h"

int main()
{
    std::string s(1000, 'a');
    Text a(s.c_str()), b(s.c_str()), c(s.c_str());
    Text::resetStats();
    Text r = a + b + c;
    std::cout << "result size             : " << r.size() << '\n';
    std::cout << "copy constructor calls  : " << Text::copyCtors << '\n';
    std::cout << "characters copied       : " << Text::charsCopied << "  (expected (n1+n2) + (n1+n2+n3) = 2000 + 3000)\n";
}
