#pragma once
#include "../header.h"

/*
Problem: Word Break (Dictionary Decomposition)
--------------------------------------------------
Given a dictionary of strings and a key, determine whether the key can be segmented into a space-separated
sequence of one or more dictionary words.

Examples:
  dictionary: {"world", "hello", "super", "hell"}
  key: "helloworld"    -> true
  key: "superman"      -> false
  key: "hellohello"    -> true
--------------------------------------------------
Reference: https://careercup.com/question?id=5705581721550848
*/

class WordBreak {
   public:
    static void test() {
        WordBreak obj;

        unordered_set<string> dict = {"jess", "looked", "Hello", "Are", "World", "just", "like", "You", "Here", "are", "some", "extra", "words", "tim", "her", "brother", "How", "hello", "world", "hell"};
        vector<string> words = {
            "jesslookedjustliketimherbrother",  // true
            "HelloHowAreYou",                   // true
            "HelloWhatAreYouUpto",              // false
            "hellohello",                       // true
            "helloworld",                       // true
            "superman",                         // false
            "",                                 // true (empty string)
            "unknownword"                       // false (unbreakable)
        };

        for (const auto& word : words) {
            bool exists1 = obj.wordBreakRecursive(word, dict);
            bool exists2 = obj.wordBreakDP(word, dict);
            bool exists3 = obj.wordBreakDP2(word, dict);
            vector<int> indices = obj.findWords(word, dict);
            bool exists4 = !indices.empty() || word.empty();

            assert(exists1 == exists2);
            assert(exists1 == exists3);
            assert(exists1 == exists4);

            cout << "\nFollowing is word break for word: " << word << endl;
            if (exists4 && !word.empty()) {
                int start = 0;
                for (int i : indices) {
                    cout << word.substr(start, i - start) << " ";
                    start = i;
                }
            } else {
                cout << (word.empty() ? "Empty word is trivially breakable." : "No word break exists!");
            }
            cout << endl;

            int res = obj.minimumWordBreaksDP(word, dict);
            cout << format("Minimum word breaks for \"{0}\" are {1}.", word, res) << endl;
        }
    }

   private:
    /**
     * Find valid break indices using DP.
     * Time: O(n^2), Space: O(n^2)
     */
    vector<int> findWords(const string& str, const unordered_set<string>& dict) {
        int n = str.size();
        vector<bool> seen(n + 1, false);
        unordered_map<int, vector<int>> results;
        seen[0] = true;

        for (int i = 1; i <= n; ++i) {
            if (!seen[i] && dict.count(str.substr(0, i))) {
                seen[i] = true;
                results[i] = {i};
            }
            if (seen[i]) {
                auto cur = results[i];
                for (int j = i + 1; j <= n; ++j) {
                    if (!seen[j] && dict.count(str.substr(i, j - i))) {
                        seen[j] = true;
                        auto tmp = cur;
                        tmp.push_back(j);
                        results[j] = tmp;
                    }
                }
            }
        }
        return seen[n] ? results[n] : vector<int>{};
    }

    /**
     * Find valid break indices using DP.
     * Time: O(n^2), Space: O(n + k) where k = number of splits
     */
    static bool findWords2(const unordered_set<string>& dict, const string& input, vector<string>& path) {
        int n = static_cast<int>(input.size());
        vector<bool> dp(n + 1, false);
        vector<int> prev(n + 1, -1);
        dp[0] = true;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                string word = input.substr(j, i - j);
                if (dp[j] && dict.count(word)) {
                    dp[i] = true;
                    prev[i] = j;
                    break;
                }
            }
        }

        if (!dp[n]) return false;

        // Recover path from backtracking
        for (int at = n; at > 0; at = prev[at]) {
            path.push_back(input.substr(prev[at], at - prev[at]));
        }
        std::reverse(path.begin(), path.end());

        return true;
    }

    /**
     * Recursive approach (naive).
     * Time: Exponential, Space: O(n) recursive stack
     */
    bool wordBreakRecursive(const string& str, const unordered_set<string>& dict) {
        if (str.empty()) return true;
        for (int i = 1; i <= str.length(); ++i) {
            if (dict.count(str.substr(0, i)) && wordBreakRecursive(str.substr(i), dict)) return true;
        }
        return false;
    }

    /**
     * DP top-down (build table for reachability).
     * Time: O(n^2), Space: O(n)
     */
    bool wordBreakDP(const string& str, const unordered_set<string>& dict) {
        int n = str.length();
        vector<bool> table(n + 1, false);
        table[0] = true;

        for (int i = 1; i <= n; ++i) {
            if (!table[i] && dict.count(str.substr(0, i))) {
                table[i] = true;
            }
            if (table[i]) {
                for (int j = i + 1; j <= n; ++j) {
                    if (!table[j] && dict.count(str.substr(i, j - i))) {
                        table[j] = true;
                    }
                }
            }
            if (table[n]) return true;
        }
        return table[n];
    }

    /**
     * Optimized DP version.
     * Time: O(n^2), Space: O(n)
     */
    bool wordBreakDP2(const string& str, const unordered_set<string>& dict) {
        int n = str.length();
        vector<bool> table(n + 1, false);
        table[0] = true;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (table[j] && dict.count(str.substr(j, i - j))) {
                    table[i] = true;
                    break;
                }
            }
        }
        return table[n];
    }

    /**
     * Minimum word breaks using DP.
     * Time: O(n^2), Space: O(n)
     */
    int minimumWordBreaksDP(const string& str, const unordered_set<string>& dict) {
        int n = str.length();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] != INT_MAX && dict.count(str.substr(j, i - j))) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n] == INT_MAX ? -1 : dp[n];
    }
};
