// Q7 - AC circuit impedance calculator built on the Complex class
#include <iostream>
#include "complex.h"

int main()
{
    const double w = 1000.0;                 // rad/s
    const double R = 40.0;                   // ohm
    const double L = 0.1;                    // henry     -> XL = w L = 100 ohm
    const double C = 1.0 / (w * 70.0);       // farad     -> 1/(w C) = 70 ohm  (about 14.2857 uF)

    Complex zr = resistor(R), zl = inductor(w, L), zc = capacitor(w, C);
    std::cout << "ZR = " << zr << "\nZL = " << zl << "\nZC = " << zc << '\n';

    std::cout << "\n--- series RLC ---\n";
    Complex zs = zr + zl + zc;
    std::cout << "Zs = " << zs << "   |Zs| = " << std::fixed << std::setprecision(4) << zs.magnitude() << " ohm\n";

    std::cout << "\n--- parallel RLC (pairwise (Z1*Z2)/(Z1+Z2)) ---\n";
    Complex zrl = parallel(zr, zl);
    std::cout << "ZR || ZL        = " << zrl << '\n';
    Complex zp = parallel(zrl, zc);
    std::cout << "(ZR||ZL) || ZC  = " << zp << "   |Zp| = " << zp.magnitude() << " ohm\n";

    std::cout << "\n--- == and the constructors ---\n";
    std::cout << std::boolalpha << "Complex(40) == Complex(40, 0) : " << (Complex(40) == Complex(40, 0)) << '\n';
    std::cout << "default Complex()             : " << Complex() << '\n';
    std::cout << "Zs - Zs == 0                  : " << (zs - zs == Complex()) << '\n';
    std::cout << "(2+3j)*(4-1j)                 : " << Complex(2, 3) * Complex(4, -1) << "   (hand: 11 + j10)\n";
    std::cout << "(1+2j)/(3-4j)                 : " << Complex(1, 2) / Complex(3, -4) << "   (hand: -0.2 + j0.4)\n";

    std::cout << "\n--- division by a zero impedance ---\n";
    try {
        Complex bad = Complex(1, 1) / Complex(0, 0);
        std::cout << bad << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
    // ideal parallel LC at resonance: j100 and -j100 add up to zero, the parallel impedance is infinite
    try {
        Complex z = parallel(inductor(w, L), Complex(0, -100));
        std::cout << z << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "parallel(j100, -j100): " << e.what() << "  -> open circuit, impedance is infinite\n";
    }
}
