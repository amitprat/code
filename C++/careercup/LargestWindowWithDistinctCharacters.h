#include "../Header.h"

/*
In a string detect the smallest window length with highest number of distinct characters. For eg.
A = “aabcbcdbca”, then ans would be 4 as of “dbca”
*/

pair<int, int> longestWindow(string str)
{
    unordered_map<char, int> map;
    pair<int, int> res = {0, 0};
    int s = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (map.find(str[i]) != map.end())
        {
            // update max
            if (i - s > res.second - res.first + 1)
            {
                res = {s, i - 1};
            }

            // erase all characters before lastIndex
            while (s <= map[str[i]])
                map.erase(str[s++]);
        }
        map[str[i]] = i;
        cout << s << " " << i << endl;
    }

    // update last character
    if (str.length() - s > res.second - res.first + 1)
    {
        res = {s, str.length() - 1};
    }

    return res;
}

int test()
{
    string str = "aabcbcdbcadcdfagd";
    pair<int, int> res = longestWindow(str);

    cout << "{" << res.first << "," << res.second << "}"
         << ":" << str.substr(res.first, res.second - res.first + 1) << endl;

    return 0;
}
