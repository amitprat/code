#pragma once

#include <iostream>

using namespace std;

class FindMatch
{
public:
    static void main()
    {
        FindMatch obj;
        cout << "Hello World";
        string s1 = "ABCSCABCDFDKABCDJFJLDFDNCNMDKCACNF";
        string s2 = "ABC";
        bool res = obj.isSubstr(s1, s2);
        cout << "result = " << res << endl;
        cout << "final = " << s1 << endl;
    }

    bool match(string first, string second, int start, int m)
    {
        for (int i = 0; i < m; i++) if (first[start + i] != second[i]) return false;
        return true;
    }
    bool isSubstr(string& first, string second)
    {
        int n = first.length();
        int m = second.length();
        bool res = false;
        int j = 0;
        for (int i = 0; i < n;)
        {
            if (match(first, second, i, m)) {
                i += m;
                res = true;
            }
            else {
                first[j] = first[i];
                i++;
                j++;
            }
        }
        first = first.substr(0, j);

        return res;
    }
};