/*
Given a length n, return the number of strings of length n that can be made up of the letters 'a', 'b', and 'c', where there can only be a maximum of 1 'b's and can only have up to two consecutive 'c's

Example:
findStrings(3) returns 19
since the possible combinations are: aaa,aab,aac,aba,abc,aca,acb,baa,bac,bca,caa,cab,cac,cba,cbc,acc,bcc,cca,ccb
and the invalid combinations are:
abb,bab,bba,bbb,bbc,bcb,cbb,ccc
*/

#include <bits/stdc++.h>
using namespace std;

void permute(string str, int bCount, int cCount, string result, int &cnt)
{
    if (result.length() == str.length())
    {
        cout << result << endl;
        cnt++;
        return;
    }

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'b' && bCount == 1)
            continue;
        if (str[i] == 'c' && cCount == 2)
            continue;
        auto newBCount = (str[i] == 'b') ? bCount + 1 : bCount;
        auto newCCount = (str[i] == 'c') ? cCount + 1 : 0;

        permute(str, newBCount, newCCount, result + str[i], cnt);
    }
}

int main()
{
    string str = "abc";
    int cnt = 0;
    permute(str, 0, 0, "", cnt);
    cout << cnt << endl;

    return 0;
}
