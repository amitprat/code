#include "../header.h"

class IsStringRepeated
{
public:
    static void test()
    {
        IsStringRepeated obj;
        vector<string> strs = {
            "abcabcabc",
            "abcdabababababab"};

        for (auto &str : strs)
        {
            auto res = obj.IsRepeated(str);
            if (res.first)
                cout << str << " is "
                     << "repeated, "
                     << "repeated string: " << res.second << endl;
            else
                cout << str << "isn't repeated" << endl;
        }
    }

private:
    pair<bool, string> IsRepeated(string &str)
    {
        int n = str.length();
        for (int i = 1; i <= n / 2; i++)
        {
            if (n % i == 0)
            {
                string pat = str.substr(0, i);
                if (IsRepeated(str, pat))
                    return {true, pat};
            }
        }

        return {false, ""};
    }

    bool IsRepeated(string &txt, string &pat)
    {
        int n = txt.length();
        int m = pat.length();

        for (int i = 0; i <= n - m;)
        {
            int j = 0;
            for (; j < m; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j != m)
                return false;

            i += m;
        }

        return true;
    }
};