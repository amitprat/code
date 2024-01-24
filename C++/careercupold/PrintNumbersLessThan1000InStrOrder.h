#include "../Header.h"

/*
Output top N positive integer in string comparison order. For example, let's say N=1000, then you need to output in string comparison order as below:
1, 10, 100, 1000, 101, 102, ... 109, 11, 110, ...
*/

void printNumbers(string prefix, int limit)
{
    if (stoi(prefix) > limit)
        return;
    cout << prefix << " ";
    for (int i = 0; i <= 9; i++)
    {
        printNumbers(prefix + std::to_string(i), limit);
    }
}

void printNumbers(int limit)
{
    for (int i = 1; i <= 9; i++)
    {
        printNumbers(std::to_string(i), limit);
    }
}

int main()
{
    printNumbers(1000);
    return 0;
}