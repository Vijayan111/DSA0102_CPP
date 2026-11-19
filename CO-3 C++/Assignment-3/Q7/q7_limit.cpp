// Q7: remaining limitation - my division overflows for very large numbers, std::complex does not
#include <complex>
#include <iostream>
#include "complex.h"

int main()
{
    Complex a(1e200, 1e200), b(1e200, 1e200);
    std::complex<double> sa(1e200, 1e200), sb(1e200, 1e200);
    std::cout << "(1e200+1e200j)/(1e200+1e200j)\n";
    std::cout << "  my Complex      : " << a / b << '\n';
    std::cout << "  std::complex    : " << sa / sb << '\n';
}
