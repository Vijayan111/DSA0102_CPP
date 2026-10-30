// Q2 - Examination Marks Register: returning references
#include <iostream>

// returns a reference to the highest mark itself (not a copy)
int& highest(int marks[], int n)
{
    int idx = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[idx]) idx = i;
    return marks[idx];
}

// read-only view of the highest mark
const int& highestConst(const int marks[], int n)
{
    int idx = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[idx]) idx = i;
    return marks[idx];
}

// plain copy of the highest mark
int highestCopy(const int marks[], int n)
{
    int idx = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[idx]) idx = i;
    return marks[idx];
}

void print(const char* label, const int marks[], int n)
{
    std::cout << label;
    for (int i = 0; i < n; ++i) std::cout << marks[i] << ' ';
    std::cout << '\n';
}

int main()
{
    int marks[5] = {72, 85, 91, 64, 88};
    print("Before                  : ", marks, 5);

    highest(marks, 5) += 2;                       // moderation applied straight to the array element
    print("after highest() += 2    : ", marks, 5);

    highest(marks, 5) = 95;                       // function call on the left of =
    print("after highest() = 95    : ", marks, 5);

    int copy = highestCopy(marks, 5);             // returning a copy
    copy += 2;
    std::cout << "copy changed to " << copy << ", array still : ";
    print("", marks, 5);

    const int& r = highestConst(marks, 5);        // const reference: can read, cannot write
    std::cout << "const reference reads : " << r << '\n';
    // highestConst(marks, 5) += 2;   // error: assignment of read-only location (see q2_const_error.cpp)
}
