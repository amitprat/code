#include "../header.h"

/*
https://careercup.com/question?id=5164018295635968

Question was "Given a pattern and a string input - find if the string follows the same pattern and return 0 or 1.
Examples:
1) Pattern : "abba", input: "redbluebluered" should return 1.
2) Pattern: "aaaa", input: "asdasdasdasd" should return 1.
3) Pattern: "aabb", input: "xyzabcxzyabc" should return 0.


I can think of a brute-force solution for this question where we add the character in the pattern and n length of the string to a hashmap
and recurse over the pattern array and string. But is there anything more efficient? This was a pretty difficult question in my opinion.
*/

class PatternMatch {
   public:
    static void test() {
        PatternMatch obj;
        vector<pair<string, string>> inputs = {
            {"abba", "redbluebluered"},
            {"aaaa", "asdasdasdasd"},
            {"aabb", "xyzabcxyzabc"},
            {"abc", "redbluebluered"},
            {"acbae", "redbluegreenredyellow"},
            {"abcdefghijabcd", "abcdefghijabcd"}};
        for (auto input : inputs) {
            auto res = obj.isMatch(input.first, input.second);
            cout << input.first << " ~=" << input.second << " : " << res << endl;
        }
    }

   private:
    bool isMatch(string txt, string pat) {
        if (txt.empty() && pat.empty()) return true;
        if (txt.empty() || pat.empty()) return false;
        if (pat.size() == 1) return true;

        unordered_map<char, string> patMap;
        return isMatch(txt, 0, pat, 0, patMap);
    }

    bool isMatch(string txt, int idx1, string pat, int idx2, unordered_map<char, string>& patMap) {
        if (idx1 == txt.size() && idx2 == pat.size()) return true;
        if (idx1 == txt.size() || idx2 == pat.size()) return false;

        char ch = pat[idx2];
        if (patMap.find(ch) != patMap.end()) {
            auto old = patMap[ch];
            int i = 0;
            for (i = 0; i < old.size(); i++) {
                if (idx1 + i >= txt.size() || txt[idx1 + i] != old[i]) return false;
            }
            if (i != old.size()) return false;

            return isMatch(txt, idx1 + i, pat, idx2 + 1, patMap);
        } else {
            for (int i = idx1; i < txt.size(); i++) {
                string cur = txt.substr(idx1, i - idx1 + 1);
                patMap[ch] = cur;
                if (isMatch(txt, i + 1, pat, idx2 + 1, patMap)) return true;
                patMap.erase(ch);
            }
        }

        return false;
    }

   private:
    bool isMatch(string pattern, string text) {
        int i = 0, j = 0;
        unordered_map<char, string> map;
        return isMatch(map, i, j, pattern, text);
    }

    bool isMatch(unordered_map<char, string>& map, int i, int j, string pat, string txt) {
        if (i == pat.size() && j == txt.size()) {
            for (auto m : map) {
                cout << m.first << " " << m.second << endl;
            }
            return true;
        }
        if (i == pat.size() || j == txt.size()) return false;

        if (map.find(pat[i]) != map.end()) {
            string toMatch = map[pat[i]];
            string txtToMatch = txt.substr(j, toMatch.length());
            if (toMatch != txtToMatch) return false;
            return isMatch(map, i + 1, j += txtToMatch.length(), pat, txt);
        } else {
            for (int k = j; k < txt.length(); k++) {
                string txtToMatch = txt.substr(j, k - j + 1);
                map[pat[i]] = txtToMatch;
                if (isMatch(map, i + 1, j + txtToMatch.length(), pat, txt)) return true;
                map.erase(pat[i]);
            }
        }

        return false;
    }

   private:
    bool isMatch(string& str, string& pat) {
        if (str.empty() && pat.empty()) return true;
        if (str.empty() || pat.empty()) return false;

        unordered_map<char, string> map;
        return isMatch(str, 0, pat, 0, map);
    }

    bool isMatch(string& str, int i, string& pat, int j, unordered_map<char, string>& map) {
        if (i == str.length() && j == pat.length()) return true;
        if (i == str.length() || j == pat.length()) return false;

        auto ch = pat[j];
        if (map.find(ch) != map.end()) {
            auto oldStr = map[ch];
            auto curStr = str.substr(i, oldStr.length());
            if (oldStr != curStr) return false;

            return isMatch(str, i + oldStr.length(), pat, j + 1, map);
        }

        for (int k = 1; k <= str.length() - i; k++) {
            string potentialMatch = str.substr(i, k);
            map[ch] = potentialMatch;
            if (isMatch(str, i + k, pat, j + 1, map)) return true;
            map.erase(ch);
        }

        return false;
    }
};