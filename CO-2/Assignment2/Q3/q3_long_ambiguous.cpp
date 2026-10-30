// Q3 - a weak spot of the redesign: a long argument matches neither overload exactly (SUPPOSED to fail)
double charge(int grams, bool express = false)    { return grams / 1000.0 * 50 + (express ? 40 : 0); }
double charge(double kg, bool express = false)    { return kg * 50 + (express ? 40 : 0); }

int main()
{
    long g = 2500;
    return (int)charge(g);       // long -> int and long -> double are both conversions
}
