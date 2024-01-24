#include "../Header.h"

class Permutation
{
    string str;
    int len;
    int start;

public:
    static void test()
    {
        Permutation p("abc");
        while (p.hasNext())
        {
            cout << p.next() << endl;
        }
    }
    Permutation(string str)
    {
        this->str = str;
        sort(this->str.begin(), this->str.end());
        len = str.length();
    }

    bool hasNext()
    {
        for (start = len - 2; start >= 0 && str[start] >= str[start + 1]; start--)
            ;
        return start >= 0;
    }
    string next()
    {
        int j = start + 1;
        for (int k = j + 1; k < len; k++)
        {
            if (str[k] <= str[j] && str[k] >= str[start])
                j = k;
        }
        swap(str[start], str[j]);
        std::reverse(str.begin() + start + 1, str.end());

        return str;
    }
};