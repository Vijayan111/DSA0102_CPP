// Q6 - tests for the Text class
#include <iostream>
#include <string>
#include "text.h"

int main()
{
    std::cout << "--- basic use ---\n";
    Text a("Hello"), b(", "), c("World");
    Text d = a + b + c;                        // chained concatenation
    std::cout << "a + b + c = \"" << d << "\" (size " << d.size() << ")\n";

    std::cout << "\n--- comparison ---\n";
    Text e("Hello, World");
    std::cout << std::boolalpha << "d == e : " << (d == e) << ",  d != e : " << (d != e)
              << ",  a == c : " << (a == c) << '\n';

    std::cout << "\n--- assignment and independence ---\n";
    Text f;
    f = d;
    d = Text("changed");
    std::cout << "f = \"" << f << "\", d = \"" << d << "\"\n";

    std::cout << "\n--- self-assignment ---\n";
    Text g("SMS gateway");
    Text& alias = g;
    g = alias;
    std::cout << "after g = g : \"" << g << "\"\n";

    std::cout << "\n--- empty messages ---\n";
    Text empty1, empty2("");
    Text both = empty1 + empty2;
    Text left = empty1 + a;
    std::cout << "empty + empty : size " << both.size() << ", \"" << both << "\"\n";
    std::cout << "empty + Hello : size " << left.size() << ", \"" << left << "\"\n";
    std::cout << "empty == empty: " << (empty1 == empty2) << '\n';

    std::cout << "\n--- long message ---\n";
    std::string big(5000, 'x');
    Text lg(big.c_str());
    Text lg2 = lg + lg + lg;
    std::cout << "5000 + 5000 + 5000 characters -> size " << lg2.size() << ", first/last: " << lg2.c_str()[0]
              << '/' << lg2.c_str()[lg2.size() - 1] << '\n';

    std::cout << "\n--- implicit conversion: const char* + Text ---\n";
    Text h = "Dear " + c;
    std::cout << h << '\n';
}
