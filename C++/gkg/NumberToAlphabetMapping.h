#pragma once
#include "../Header.h"

/*
Given a mapping of alphabets to integers as follows:

1 = A
2 = B
3 = C
...
26 = Z

Given any combination of the mapping numbers as string, return the number of ways in which the input string can be split into sub-strings and represented as character strings. For e.g. given
"111" -> "AAA", "AK", "KA" -> 3
Valid combinations are ({1,1,1}, {1,11},{11,1}) = 3
"11" -> "AA", "K" -> 2
Valid combinations are ({1,1},{11}) = 2
"123" -> "ABC", "LC", "AW" -> 3
Valid combinations are ({1,2,3},{1,23},{12,3}) = 3

You don't have to return all the mappings, only the number of valid mappings.

this is pretty easy if you think in terms of Dp approach.
Lets say we have String as "1" so our output will be 1 because we only form 'A'
but if we add 2 to the existing string "12" then output is "AB" and "L" so if you see
the logic is when you add a character to an existing string the number of combinations increase by combining last 2 digits
in dp it can be formulized As
d[i]=dp[i-1]+dp[i-2](if the last 2 digits combined is smaller than 27)
else dp[i]=dp[i-1];
code is as below
*/
char get(char ch1, char ch2 = '$') {
    int n = (ch1 - '0');
    if (ch2 != '$') n = n * 10 + (ch2 - '0');
    if (n >= 1 && n <= 26) return ('A' + (n - 1));
    return '$';
}

void print(string str, int index, string prefix) {
    if (index == str.length()) {
        cout << prefix << endl;
        return;
    }

    char ch = get(str[index]);
    if (ch != '$')
        print(str, index + 1, prefix + ch);

    if (index < str.length() - 1) {
        ch = get(str[index], str[index + 1]);
        if (ch != '$')
            print(str, index + 2, prefix + ch);
    }
}

void printDP(string str) {
    vector<vector<string>> result(str.length() + 1);
    int dp[str.length() + 1];
    dp[0] = 1;
    dp[1] = 1;
    result[0].push_back("");
    result[1].push_back(string(1, get(str[0])));
    for (int i = 2; i <= str.length(); i++) {
        dp[i] = 0;

        char ch = get(str[i - 1]);
        if (ch != '$') {
            dp[i] = dp[i - 1];
            for (auto s : result[i - 1]) result[i].push_back(s + ch);
        }

        ch = get(str[i - 2], str[i - 1]);
        if (ch != '$') {
            dp[i] += dp[i - 2];
            for (auto s : result[i - 2]) result[i].push_back(s + ch);
        }
    }
    cout << dp[str.length()] << endl;
    for (auto s : result[str.length()]) cout << s << " ";
    cout << endl;
}

int main()
{
    string str = "121";
    print(str, 0, "");
    printDP(str);

    return 0;
}