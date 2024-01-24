#include "../Header.h"

/*
https://www.careercup.com/question?id=23823662

Given an equation in the form 2^i * 3^j * 5^k * 7^l where i,j,k,l >=0 are integers.write a program to generate numbers 
from that equation in sorted order efficiently.

for example numbers from that equation will be in the order 2,3,5,6,7,8,9.....and so on..
*/

/*
These are basically referred to as ugly numbers . Here is the code for it:
a. Take variables for multiples of 2,3,5,7.
b. Everytime find a minimum of the multiple.
c. Store 1 in the first index as it is multiple of all.
d. Find the minimum of all the multiples of 2,3,5,7. Whenever that minimum is equal to any of the multiples. 
Store that multiple in the indexes assigned for 2,3,5,7 and also multiply that element with the number to get 
the next higher multiple in next iteration.
*/

int minimum(vector<int> &v, int c2, int c3, int c5, int c7)
{
    int mn = v[c2] * 2;
    if (v[c3] * 3 < mn)
        mn = v[c3] * 3;
    if (v[c5] * 5 < mn)
        mn = v[c5] * 5;
    if (v[c7] * 7 < mn)
        mn = v[c7] * 7;

    return mn;
}
vector<int> printMultiples(int n)
{
    vector<int> result;
    result.push_back(1);

    int c2 = 0, c3 = 0, c5 = 0, c7 = 0;

    while (result.size() < n)
    {
        auto cur = minimum(result, c2, c3, c5, c7);
        if (cur == 2 * result[c2])
            c2++;
        if (cur == 3 * result[c3])
            c3++;
        if (cur == 5 * result[c5])
            c5++;
        if (cur == 7 * result[c7])
            c7++;

        result.push_back(cur);
    }

    return result;
}
void test()
{
    int n = 100;
    auto res = printMultiples(100);
    for (auto i : res)
        cout << i << " ";
    cout << endl;
}