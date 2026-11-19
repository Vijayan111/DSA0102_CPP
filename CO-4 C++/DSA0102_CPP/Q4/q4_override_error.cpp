// Q4.4 - 'override' makes the compiler catch a hidden (non-virtual) function (this file is SUPPOSED to fail)
struct Account {
    double rate() const { return 3.5; }          // not virtual
    virtual ~Account() = default;
};
struct SeniorAccount : Account {
    double rate() const override { return 4.0; } // error: does not override anything
};
int main() { SeniorAccount s; return (int)s.rate() - 4; }
