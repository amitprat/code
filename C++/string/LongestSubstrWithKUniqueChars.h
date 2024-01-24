#include "../header.h"

class LongestSubstrWithKUniqueChars {
   public:
    static void test() {
        LongestSubstrWithKUniqueChars obj;
        vector<pair<pair<string, int>, string>> tests{
            {{"", 2}, ""},
            {{"a", 1}, "a"},
            {{"ab", 1}, "a"},
            {{"ab", 2}, "ab"},
            {{"aaaaaaab", 2}, "aaaaaaab"},
            {{"abbbbbbb", 2}, "abbbbbbb"},
            {{"caaaaaaab", 2}, "caaaaaaa"},
            {{"caaaaaaab", 1}, "aaaaaaa"},
            {{"abcbbbbcccbdddadacb", 3}, "bcbbbbcccbddd"},
            {{"abcbbbbcccbcbaadacb", 3}, "abcbbbbcccbcbaa"},
            {{"abcbbbbcccbdddadacb", 1}, "bbbb"},
            {{"abcbbbbcccbcbaadacb", 2}, "bcbbbbcccbcb"},
            {{"abcbbbbcccbcbaadacb", 4}, "abcbbbbcccbcbaadacb"}};

        for (auto& test : tests) {
            auto res = obj.longestSubstring(test.first.first, test.first.second);
            cout << format("Longest substring in str={} with k={} unique characters is {}", test.first.first, test.first.second, res) << endl;
            assert(test.second == res);
        }
    }

    string longest(string str, int k) {
        unordered_map<char, int> map;
        vector<int> positions;
        int start = 0;
        int startPositionOffset = 0;
        string res;
        for (int index = 0; index < str.length(); index++) {
            char curChar = str[index];
            if (map.find(curChar) == map.end()) {
                positions.push_back(index);
                map[curChar] = positions.size() - 1;
            } else {
                auto posIndex = map[curChar];
                positions[posIndex] = index;
            }

            if (map.size() > k) {
                if (index - start > res.length()) res = str.substr(start, index - start);
                auto startChar = str[positions[startPositionOffset]];
                map.erase(startChar);
                start = positions[startPositionOffset++] + 1;
            }
        }

        if (map.size() == k) {
            if (str.length() - start > res.length()) res = str.substr(start);
        }

        return res;
    }

   private:
    string longestSubstring(const string& str, int k) {
        unordered_map<char, int> freqMap;
        string mxStr;

        int i = 0, j = 0;
        while (j < str.length()) {
            char ch = str[j];
            freqMap[ch]++;

            while (freqMap.size() > k) {
                char pre = str[i];
                freqMap[pre]--;
                if (freqMap[pre] <= 0) freqMap.erase(pre);
                i++;
            }

            if (mxStr.length() == 0 || mxStr.length() < j - i + 1) {
                mxStr = str.substr(i, j - i + 1);
            }

            j++;
        }

        return mxStr;
    }
};