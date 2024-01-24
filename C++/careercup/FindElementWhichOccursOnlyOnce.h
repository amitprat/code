#include "../Header.h"

/*
https://stackoverflow.com/questions/14100169/find-the-element-that-appears-once

You are given an array that contains integers. The integers content is such that every integer occurs 3 times in that array
 leaving one integer that appears only once.
Fastest way to find that single integer
-- using memory.
-- not using any external memory.

eg: [2,1,4,5,1,4,2,2,4,1]
*/

/*
Add the numbers bitwise mod 3. I guess too many people were just saying "XOR" without understanding properly.
*/

// If O(1) space constraint was not there,
//     you could've gone for a hashmap with values being the count of occurrences.

int getUniqueElement(int[] arr)
{
    int ones = 0; //At any point of time, this variable holds XOR of all the elements which have appeared "only" once.
    int twos = 0; //At any point of time, this variable holds XOR of all the elements which have appeared "only" twice.
    int not_threes;

    for (int x : arr)
    {
        twos |= ones & x; //add it to twos if it exists in ones
        ones ^= x;        //if it exists in ones, remove it, otherwise, add it

        // Next 3 lines of code just converts the common 1's between "ones" and "twos" to zero.

        not_threes = ~(ones & twos); //if x is in ones and twos, dont add it to Threes.
        ones &= not_threes;          //remove x from ones
        twos &= not_threes;          //remove x from twos
    }
    return ones;
}

// Mine
#include <bits/stdc++.h>
using namespace std;

int findUnique(vector<int> arr)
{
    int res = 0;
    for (int pos = 0; pos < 32; pos++)
    {
        int cur = 0;
        for (int elem : arr)
        {
            cur += (elem & (1 << pos)) ? 1 : 0;
        }
        if (cur % 3)
            res |= (1 << pos);
    }
    return res;
}

int main()
{
    vector<int> arr = {12, 1, 12, 3, 12, 1, 1, 2, 3, 3, 2, 5, 2};
    auto res = findUnique(arr);
    cout << res << endl;

    return 0;
}
