#pragma once
#include "../Header.h"

class PatternMatch {
public:
    static void test() {
        string pat = "abab";
        string txt = "redbluebluered";

        auto res = isMatch(txt, pat);

        cout << "Is Match ? " << res << endl;
    }

    static bool isMatch(string txt, string pat) {
        if (txt.empty() && pat.empty()) return true;
        if (txt.empty() || pat.empty()) return false;
        if (pat.size() == 1) return true;

        unordered_map<char, string> patMap;
        return isMatch(txt, 0, pat, 0, patMap);
    }

    static bool isMatch(string txt, int idx1, string pat, int idx2, unordered_map<char, string>& patMap) {
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
        }
        else {
            for (int i = idx1; i < txt.size(); i++) {
                string cur = txt.substr(idx1, i - idx1 + 1);
                patMap[ch] = cur;
                if (isMatch(txt, i + 1, pat, idx2 + 1, patMap)) return true;
                patMap.erase(ch);
            }
        }

        return false;
    }
};