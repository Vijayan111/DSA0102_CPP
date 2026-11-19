// Q3: delete used where delete[] is needed
#include <iostream>
int main()
{
    char* row = new char[20];
    row[0] = 'X';
    std::cout << "row allocated with new[]\n";
    delete row;            // should be delete[] row
}
