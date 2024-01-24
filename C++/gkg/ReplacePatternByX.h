#include "../Header.h"

class ReplacePattern
{
public:
    void replace(string &str, string pat, string rep)
    {
        int i = 0, j = 0, k = 0;
        while (j < str.size())
        {
            str[i] = str[j];
            if (str[j] == pat[k])
                k++;
            if (k == pat.length())
            {
                i -= (pat.length() - 1);
                if (i == 0 || str[i - 1] != 'X')
                    str[i] = 'X';
                else
                    i--;
                k = 0;
            }

            i++;
            j++;
        }
        cout << i << endl;
        str.erase(i);
    }

    void replace1(string &str, string pat, string rep)
    {
        int pos = 0;
        while ((pos = str.find(pat)) != string::npos)
        {
            str.replace(pos, pat.size(), rep);
        }
        pos = 0;
        string dup = rep + rep;
        while ((pos = str.find(dup)) != string::npos)
            str.replace(pos, dup.size(), rep);
    }

    static void test()
    {
        ReplacePattern obj;
        string str = "ababcdab";
        string pat = "ab";
        string rep = "X";

        obj.replace1(str, pat, rep);

        cout << str << endl;
    }
};