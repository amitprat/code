#pragma once
#include "../Header.h"

/*
https://careercup.com/question?id=5705581721550848

You're given a dictionary of strings, and a key. Check if the key is composed of an arbitrary number of concatenations of strings from the dictionary. For example:

dictionary: "world", "hello", "super", "hell"
key: "helloworld" --> return true
key: "superman" --> return false
key: "hellohello" --> return true
*/
class WordBreak {
   public:
    static void test() {
        WordBreak obj;

        unordered_set<string> dict = {"jess", "looked", "Hello", "Are", "World", "just", "like", "You", "Here", "are", "some", "extra", "words", "tim", "her", "brother", "How"};
        vector<string> words = {"jesslookedjustliketimherbrother", "HelloHowAreYou", "HelloWhatAreYouUpto"};

        for (auto word : words) {
            bool exists1 = obj.wordBreakRecursive(word, dict);
            bool exists2 = obj.wordBreakDP(word, dict);
            bool exists3 = obj.wordBreakDP2(word, dict);
            vector<int> indices = obj.findWords(word, dict);
            bool exists4 = !indices.empty();

            assert(exists1 == exists2);
            assert(exists1 == exists3);
            assert(exists1 == exists4);

            cout << "\nFollowing is word break for word: " << word << endl;
            if (exists4) {
                int start = 0;
                for (auto i : indices) {
                    cout << word.substr(start, i - start) << " ";
                    start = i;
                }
            } else {
                cout << "No word break exists!";
            }
            cout << endl;
        }
    }

   private:
    // get the indices if word break exists
    vector<int> findWords(string str, unordered_set<string> dict) {
        vector<bool> seen(str.size() + 1, false);
        seen[0] = true;
        unordered_map<int, vector<int>> results;

        for (int i = 1; i <= str.size(); i++) {
            if (!seen[i] && contains(dict, str.substr(0, i))) {
                seen[i] = true;
                results.insert({i, {i}});
            }
            if (seen[i]) {
                auto cur = results[i];
                for (int j = i + 1; j <= str.size(); j++) {
                    if (!seen[j] && contains(dict, str.substr(i, j - i))) {
                        seen[j] = true;
                        auto tmp = cur;
                        tmp.push_back(j);
                        results.insert({j, tmp});
                    }
                }
            }
            if (seen[str.size()]) {
                return results[str.size()];
            }
        }

        if (!(seen[str.size()])) return {};

        return {};
    }

    bool contains(unordered_set<string> dict, string str) {
        return dict.find(str) != dict.end();
    }

    // check if word break exists
   private:
    bool wordBreakRecursive(string str, unordered_set<string> dict) {
        if (str.empty()) return true;

        for (int i = 1; i <= str.length(); i++) {
            string cur = str.substr(0, i);
            if ((dict.find(cur) != dict.end()) && wordBreakRecursive(str.substr(i), dict)) return true;
        }

        return false;
    }

   private:
    bool wordBreakDP(string str, unordered_set<string>& dict) {
        int n = str.length();
        vector<bool> table(n + 1, false);
        table[0] = true;

        for (int i = 1; i <= n; i++) {
            string first = str.substr(0, i);
            if (!table[i] && dict.find(first) != dict.end()) table[i] = true;

            if (table[i]) {
                for (int j = i + 1; j <= n; j++) {
                    string rest = str.substr(i, j - i);
                    if (!table[j] && dict.find(rest) != dict.end()) table[j] = true;
                }
            }

            if (table[n]) return true;
        }

        return false;
    }

   private:
    bool wordBreakDP2(string str, unordered_set<string>& dict) {
        int n = str.length();
        vector<bool> table(n + 1, false);
        table[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                string cur = str.substr(j, i - j);
                if (table[j] && dict.find(cur) != dict.end()) table[i] = true;
            }
        }

        return table[n];
    }
};