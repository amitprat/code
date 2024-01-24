#include "../header.h"

/*
https://careercup.com/question?id=5705619461898240

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
*/

class NumberOfPossibleAlphabetCombination
{
public:
    static void test()
    {
        string str = "123";
        NumberOfPossibleAlphabetCombination obj;
        auto res = obj.getAlphabtetsString(str);
        cout << res << endl;
    }

private:
    vector<string> getAlphabtetsString(string str)
    {
        vector<string> result;

        getAlphabtetsString(str, 0, str.size(), "", result);
        return result;
    }

    void getAlphabtetsString(string str, int pos, int n, string cur, vector<string> &result)
    {
        if (pos == n)
        {
            result.push_back(cur);
            return;
        }
        if (pos > n)
            return;
        if (str[pos] == '0')
            return;

        char ch = ('A' + str[pos] - '1');
        getAlphabtetsString(str, pos + 1, n, cur + ch, result);

        int val = (str[pos] - '0') * 10 + (str[pos + 1] - '0');
        if (val <= 26)
        {
            ch = val + 'A' - 1;
            getAlphabtetsString(str, pos + 2, n, cur + ch, result);
        }
    }
};