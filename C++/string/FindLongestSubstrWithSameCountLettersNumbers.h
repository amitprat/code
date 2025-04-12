#pragma once
#include "../header.h"
using namespace std;

class FindLongestSubstrWithSameCountLettersNumbers {
   public:
    static void test() {
        FindLongestSubstrWithSameCountLettersNumbers obj;
        vector<string> strs = {"", "a", "1", "11", "aa", "1a1", "a11a", "1aa1", "a111a", "1asd1s", "asdasd12312131a", "1a1"};
        for (auto& str : strs) {
            auto res = obj.findLongestStr(str);
            auto res1 = obj.findBruteForce(str);

            cout << format("Longest substring with same count of characters and digits in string='{}' is '{}'", str, res) << endl;
        }
    }

   public:
    string findLongestStr(string str) {
        unordered_map<int, int> lastIndexMap;
        pair<int, int> strWithLength = {0, -1};
        int diff = 0;
        lastIndexMap[diff] = -1;

        for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i]))
                diff++;
            else if (isalpha(str[i]))
                diff--;

            if (lastIndexMap.find(diff) == lastIndexMap.end()) {
                lastIndexMap[diff] = i;
            } else {
                auto s = lastIndexMap[diff] + 1;
                if (i - s + 1 > strWithLength.second) {
                    strWithLength = {s, i - s + 1};
                }
            }
        }

        if (strWithLength.second >= strWithLength.first) {
            return str.substr(strWithLength.first, strWithLength.second);
        }

        return string();
    }

   public:
    string findBruteForce(string str) {
        int maxLength = 0;
        pair<int, int> strWithMaxLength;
        for (int j = str.length() - 1; j >= 1; j--) {
            for (int i = 0; i < j; i++) {
                if (equal(str, i, j) && j - i + 1 > maxLength) {
                    maxLength = j - i + 1;
                    strWithMaxLength = {i, j};
                }
            }
        }

        if (maxLength > 0) return str.substr(strWithMaxLength.first, strWithMaxLength.second - strWithMaxLength.first + 1);

        return string();
    }

    bool equal(string str, int s, int e) {
        int cnt = 0;
        for (int i = s; i <= e; i++) {
            if (isdigit(str[i]))
                cnt++;
            else if (isalpha(str[i]))
                cnt--;
        }

        return cnt == 0;
    }
};