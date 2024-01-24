#include "../header.h"

class SubstringSearch
{
public:
    static void test()
    {
        string txt = "ABABDABACDABABCABAB";
        string pat = "ABABCABAB";

        SubstringSearch obj;

        auto res = obj.isSubstring(txt, pat);
        cout << "Result: " << res << endl;
    }

    bool isSubstring(string &txt, string &pat)
    {
        bool res1 = naiveSubstringSearch(txt, pat);
        bool res2 = kmpSubstringSearch(txt, pat);

        assert(res1 == res2);

        return res1;
    }

private:
    // T = O(N*M)
    bool naiveSubstringSearch(string &txt, string &pat)
    {
        int l = txt.length();
        int m = pat.length();

        bool found = false;
        for (int i = 0; i <= l - m; i++)
        {
            int j = 0;
            for (; j < m; j++)
            {
                if (pat[j] != txt[i + j])
                    break;
            }
            if (j == m)
            {
                cout << "Pattern found at: " << i << endl;
                cout << "Substring: " << txt.substr(i, m) << endl;

                found = true;
            }
        }

        return found;
    }

private:
    // T = O(N+M), S=O(M)
    bool kmpSubstringSearch(string &txt, string &pat)
    {
        int l = txt.length();
        int m = pat.length();

        vector<int> lpsArr(m);
        computeLPSArray(lpsArr, pat, m);

        int i = 0, j = 0;
        bool found = false;
        while (i < l)
        {
            if (txt[i] == pat[j])
            {
                i++;
                j++;
            }
            if (j == m)
            {
                cout << "Pattern found at: " << i - m << endl;
                cout << "Substring: " << txt.substr(i - m, m) << endl;

                j = lpsArr[j - 1];
                found = true;
            }
            else if (i < l && txt[i] != pat[j])
            {
                if (j != 0)
                    j = lpsArr[j - 1];
                else
                    i += 1;
            }
        }

        return found;
    }

    void computeLPSArray(vector<int> &lpsArr, string &pat, int m)
    {
        int len = 0;
        lpsArr[len] = 0;

        int i = 1;
        while (i < m)
        {
            if (pat[len] == pat[i])
            {
                len++;
                lpsArr[i] = len;
                i++;
            }
            else
            {
                if (len > 0)
                    len = lpsArr[len - 1];
                else
                {
                    lpsArr[i] = 0;
                    i++;
                }
            }
        }
    }
};