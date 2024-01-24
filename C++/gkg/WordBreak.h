#pragma once
#include "../Header.h"

class WordBreak {
public:
    static void test() {
        WordBreak obj;
        unordered_set<string> dict = { "mobile", "samsung", "sam",
                                        "sung", "man", "mango",
                                        "icecream", "and", "go",
                                        "i", "like", "ice", "cream","smart","phone","mobile" };

        string word = "ilikesamsungsmartmobilephone";
        vector<vector<string>> result;
        auto res = obj.wordBreakDP1(word, dict, result);
        cout << "Has word break? " << res << endl;
        if (res) {
            cout << to_string(result) << endl;
        }
    }

    bool wordBreakRec(string word, unordered_set<string>& dict, vector<vector<string>>& result) {
        return wordBreakRec(word, dict, result, {});
    }

    bool wordBreakDP(string word, unordered_set<string>& dict, vector<vector<string>>& result) {
        bool* dp = new bool[word.size() + 1];
        memset(dp, false, (word.size() + 1) * sizeof(bool));
        dp[0] = true;
        bool exists = false;

        for (int i = 1; i <= word.size(); i++) {
            if (!dp[i])
                dp[i] = (dict.find(word.substr(0, i)) != dict.end());
            if (dp[i]) {
                for (int j = i + 1; j <= word.size(); j++) {
                    if (!dp[j]) {
                        dp[j] = (dict.find(word.substr(i, j - i)) != dict.end());
                    }
                }
            }
            if (dp[word.size()]) {
                exists = true;
                populateResult(dp, word, result);
                for (int j = i + 1; j <= word.size(); j++) dp[j] = false;
            }
        }
        return exists;
    }

    bool wordBreakDP1(string word, unordered_set<string>& dict, vector<vector<string>>& result) {
        int n = word.size();
        unordered_map<int, vector<vector<string>>> memo;
        memo[0].push_back({ "" });
        bool exitst = false;

        for (int i = 1; i <= n; i++) {
            //if (memo[i].empty()) {
            if (dict.find(word.substr(0, i)) != dict.end()) {
                memo[i].push_back({ word.substr(0,i) });
            }
            //}

            if (!memo[i].empty()) {
                for (int j = i + 1; j <= n; j++) {
                    //if (memo[j].empty()) {
                    if (dict.find(word.substr(i, j - i)) != dict.end()) {
                        auto prev = memo[i];
                        for (auto w : prev) {
                            w.push_back(word.substr(i, j - i));
                            memo[j].push_back(w);
                        }
                    }
                    //}
                }
            }

            if (!memo[n].empty()) {
                exitst = true;
            }
        }
        result = memo[n];
        return exitst;
    }

private:
    bool wordBreakRec(string word, unordered_set<string>& dict, vector<vector<string>>& result,
        vector<string> cur) {
        if (word.empty()) { result.push_back(cur); return true; }

        bool res = false;
        for (int i = 1; i <= word.size(); i++) {
            string first = word.substr(0, i);
            string second = word.substr(i);
            if (dict.find(first) != dict.end()) {
                cur.push_back(first);
                res |= wordBreakRec(second, dict, result, cur);
                cur.pop_back();
            }
        }

        return res;
    }

    void populateResult(bool dp[], string word, vector<vector<string>>& result) {
        vector<string> res;
        int start = 0;
        for (int i = 1; i <= word.size(); i++) {
            if (dp[i]) {
                res.push_back(word.substr(start, i - start));
                start = i;
            }
        }
        result.push_back(res);
    }
};