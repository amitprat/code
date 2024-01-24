#pragma once
#include "../Header.h"

class WordBreak {
public:
    static void test() {
        WordBreak obj;

        cout << "Break of first Word::" << endl;
        {
            string str = "jesslookedjustliketimherbrother";
            unordered_set<string> dict = { "jess", "looked", "Hello", "World", "just", "like", "Here", "are","some", "extra", "words","tim", "her", "brother" };
            vector<int> indices = obj.findWords(str, dict);
            int start = 0;
            for (auto i : indices) {
                cout << str.substr(start, i - start) << " ";
                start = i;
            }
        }
        cout << endl << endl;

        cout << "Break of second Word::" << endl;
        {
            string str = "HelloHowAreYou";
            unordered_set<string> dict = { "jess", "looked", "Hello","Are", "World", "just", "like","You", "Here", "are","some", "extra", "words","tim", "her", "brother","How" };
            vector<int> indices = obj.findWords(str, dict);
            int start = 0;
            for (auto i : indices) {
                cout << str.substr(start, i - start) << " ";
                start = i;
            }
        }
        cout << endl << endl;

        cout << "Break of second Word::" << endl;
        {
            string str = "HelloWhatAreYouUpto";
            unordered_set<string> dict = { "jess", "looked", "Hello","Are", "World", "just", "like","You", "Here", "are","some", "extra", "words","tim", "her", "brother","How" };
            vector<int> indices = obj.findWords(str, dict);
            int start = 0;
            for (auto i : indices) {
                cout << str.substr(start, i - start) << " ";
                start = i;
            }
        }
        cout << endl << endl;
    }

    vector<int> findWords(string str, unordered_set<string> dict) {
        vector<bool> seen(str.size() + 1, false);
        seen[0] = true;
        unordered_map<int, vector<int>> results;

        for (int i = 1; i <= str.size(); i++) {
            if (!seen[i] && contains(dict, str.substr(0, i))) {
                seen[i] = true;
                results.insert({ i, {i} });
            }
            if (seen[i]) {
                auto cur = results[i];
                for (int j = i + 1; j <= str.size(); j++) {
                    if (!seen[j] && contains(dict, str.substr(i, j - i))) {
                        seen[j] = true;
                        auto tmp = cur;
                        tmp.push_back(j);
                        results.insert({ j,tmp });
                    }
                }
            }
            if (seen[str.size()]) { return results[str.size()]; }
        }
        if (!(seen[str.size()])) { cout << "Not Found!!"; return {}; }
    }

    bool contains(unordered_set<string> dict, string str) {
        return dict.find(str) != dict.end();
    }
};