#pragma once
#include "../header.h"

class LongestSubstringWithKRepeatingCharacters {
   public:
    static void test() {
        LongestSubstringWithKRepeatingCharacters obj;

        string str = "cbdbdcbdbcaa";
        int k = 3;
        string res = obj.longestSubstrWithKRepeatingCharacters(str, k);

        cout << format("Longest substring with k={} repeating characters is {}", k, res) << endl;
    }

   public:
    string longestSubstrWithKRepeatingCharacters(string str, int k) {
        unordered_map<char, int> map;
        int i = 0, j = 0;
        int mxLen = 0;
        pair<int, int> mxPair;
        int cnt = 0;

        while (j < str.length()) {
            map[str[j]]++;
            if (map[str[j]] == 2) cnt++;

            if(cnt > k)
            {
                if (cnt == k && j - i + 1 > mxLen) {
                    // cout << i << " " << j - 1 << endl;
                    mxLen = j - i + 1;
                    mxPair = {i, j};
                }

                while (i <= j && cnt > k) {
                    if (map[str[i]] == 2) cnt--;
                    map[str[i]]--;

                    i++;
                }
            }

            j++;
        }

        return str.substr(mxPair.first, mxPair.second - mxPair.first + 1);
    }
};
