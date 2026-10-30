// Q2 - trying to modify through a const reference (this file is SUPPOSED to fail)
const int& highestConst(const int marks[], int n)
{
    int idx = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[idx]) idx = i;
    return marks[idx];
}

int main()
{
    int marks[3] = {10, 30, 20};
    highestConst(marks, 3) += 2;
}
