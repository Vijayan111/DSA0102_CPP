// Complex - complex numbers for AC impedance calculations
#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}                          // default: 0 + 0j
    Complex(double r) : re(r), im(0) {}                  // from real part (a resistor): R + 0j
    Complex(double r, double i) : re(r), im(i) {}        // from real and imaginary parts

    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }     // |Z| = sqrt(re^2 + im^2)

    friend Complex operator+(const Complex& a, const Complex& b) { return Complex(a.re + b.re, a.im + b.im); }
    friend Complex operator-(const Complex& a, const Complex& b) { return Complex(a.re - b.re, a.im - b.im); }
    friend Complex operator*(const Complex& a, const Complex& b)
    {
        return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
    }
    friend Complex operator/(const Complex& a, const Complex& b)
    {
        double den = b.re * b.re + b.im * b.im;                 // |b|^2
        if (den == 0.0)
            throw std::domain_error("division by a zero impedance");
        return Complex((a.re * b.re + a.im * b.im) / den, (a.im * b.re - a.re * b.im) / den);
    }

    // equal when both parts agree to within 1e-9 (floating point results are never exact)
    friend bool operator==(const Complex& a, const Complex& b)
    {
        return std::fabs(a.re - b.re) < 1e-9 && std::fabs(a.im - b.im) < 1e-9;
    }
    friend bool operator!=(const Complex& a, const Complex& b) { return !(a == b); }

    friend std::ostream& operator<<(std::ostream& os, const Complex& z)
    {
        std::ios::fmtflags f = os.flags();
        std::streamsize p = os.precision(4);
        os << std::fixed << z.re << (z.im < 0 ? " - j" : " + j") << std::fabs(z.im);
        os.flags(f);
        os.precision(p);
        return os;
    }
};

// helpers for the circuit calculator
inline Complex resistor(double R) { return Complex(R); }                              // R + 0j
inline Complex inductor(double w, double L) { return Complex(0, w * L); }             // 0 + j w L
inline Complex capacitor(double w, double C) { return Complex(0, -1.0 / (w * C)); }   // 0 - j / (w C)
inline Complex parallel(const Complex& z1, const Complex& z2) { return (z1 * z2) / (z1 + z2); }
