/*
Given a string S1, convert it to another string S2 (Anagram) by swapping only adjacent elements. Print all the intermediate strings formed.

eg: s1: abcde
s2: bcdae

output: bacde,bcade, bcdae.
*/

/*
label each character in s2 with1 to n,
s2: bcdae
n2:12345
convert s1 to a array of number according to the labels,
s1: abcde
n1: 41235

the next is to sort 41235 using bubble sort:
41235
14235
12435
12345
*/

#include "../Header.h"

int count(string &s1, string s2)
{
    int cnt = 0;

    int order[256] = {0};
    for (int i = 0; i < s2.length(); i++)
        order[s2[i]] = i;

    while (true)
    {
        bool swapped = false;
        for (int i = 0; i < s1.length() - 1; i++)
        {
            if (order[s1[i]] > order[s1[i + 1]])
            {
                swap(s1[i], s1[i + 1]);
                swapped = true;
                cnt++;
            }
        }
        if (!swapped)
            break;
    }
    return cnt;
}

int main()
{
    string s1 = "abcde";
    string s2 = "ecdab";

    int cnt = count(s1, s2);
    cout << cnt << endl;
    cout << s1 << endl;

    return 0;
}