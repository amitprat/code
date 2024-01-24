#pragma once
#include "../Header.h"
using namespace std;

class FindLongestSubstrWithSameCountLettersNumbers
{
public:
    static void test()
    {
        FindLongestSubstrWithSameCountLettersNumbers obj;
        vector<string> strs = { "", "a", "1", "11", "aa", "1a1", "a11a", "1aa1", "a111a", "1asd1s", "asdasd12312131a","1a1" };
        for (auto& str : strs) {
            auto res = obj.find(str);
            auto res1 = obj.find1(str);

            cout << format("Longest substring with same count of characters and digits in string='{}' is '{}'", str, res) << endl;
        }
    }

    string find1(string str)
    {
        unordered_map<int, int> map;
        pair<int, int> res = { 0,-1 };
        int diff = 0;
        map[diff] = -1;

        for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i])) diff++;
            else if (isalpha(str[i])) diff--;

            if (map.find(diff) == map.end()) {
                map[diff] = i;
            }
            else {
                auto s = map[diff] + 1;
                if (i - s + 1 > res.second) {
                    res = { s, i - s + 1 };
                }
            }
        }

        if (res.second >= res.first) return str.substr(res.first, res.second);
        else return string();
    }

    string find(string str)
    {
        int mx = 0;
        pair<int, int> res;
        for (int j = str.length() - 1; j >= 1; j--) {
            for (int i = 0; i < j; i++) {
                if (equal(str, i, j) && j - i + 1 > mx) { mx = j - i + 1; res = { i,j }; }
            }
        }

        if (mx > 0) return str.substr(res.first, res.second - res.first + 1);
        return string();
    }

    bool equal(string str, int s, int e) {
        int cnt = 0;
        for (int i = s; i <= e; i++) {
            if (str[i] >= '0' && str[i] <= '9') cnt++;
            else cnt--;
        }

        return cnt == 0;
    }
};