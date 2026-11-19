// Q7 alternative: the same calculator with std::complex<double>
#include <complex>
#include <iostream>

using Z = std::complex<double>;

Z parallel(Z a, Z b) { return (a * b) / (a + b); }

int main()
{
    const double w = 1000.0, R = 40.0, L = 0.1, C = 1.0 / (w * 70.0);
    Z zr(R, 0), zl(0, w * L), zc(0, -1.0 / (w * C));
    Z zs = zr + zl + zc;
    Z zp = parallel(parallel(zr, zl), zc);
    std::cout << "series   Zs = " << zs << "  |Zs| = " << std::abs(zs) << '\n';
    std::cout << "parallel Zp = " << zp << "  |Zp| = " << std::abs(zp) << '\n';
    std::cout << "(1+1j)/(0+0j)         = " << Z(1, 1) / Z(0, 0) << "   (no exception)\n";
    std::cout << "parallel(j100, -j100) = " << parallel(Z(0, 100), Z(0, -100)) << "   (no exception)\n";
}
