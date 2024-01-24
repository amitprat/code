/**************************************
* Check is word break is possible for a given string and dictionary of words
**************************************/
#pragma once
#include "../Header.h"

class WordBreak
{
private:
    unordered_set<string> dict;

public:
    struct Node
    {
        bool flag;
        vector<string> words;
    };
    WordBreak() {
        dict = { "i", "like", "sam", "sung", "samsung", "hello", "am", "a", "m", "t" ,"mobile", "ice","cream", "icecream", "man", "go", "mango","world" };
    }
    static void test()
    {
        WordBreak obj;
        vector<string> strs = { "","i", "ilike", "ilikesamsung", "hellowworld", "iamamit" };

        cout << "Break words using recursion: " << endl;
        for (auto& str : strs) {
            cout << "Is Word break possible for str = " << str << " : " << obj.wordBreakRecursion(str) << endl;
        }
        cout << endl;

        cout << "Break words using recursion with spaced words: " << endl;
        for (auto& str : strs) {
            vector<string> out;
            cout << "Is Word break possible for str = " << str << " : " << obj.wordBreakRecursion(str, out) << endl;
            cout << to_string(out) << endl;
        }
        cout << endl;


        cout << "Break words using DP: " << endl;
        for (auto& str : strs) {
            cout << "Is Word break possible for str = " << str << " : " << obj.wordBreakDP(str) << endl;
        }
        cout << endl;

        cout << "Break words using DP with spaced words: " << endl;
        for (auto& str : strs) {
            auto res = obj.wordBreakDPWithSpacedWords(str);
            cout << "Is Word break possible for str = " << str << " : " << res.flag << endl;
            if (res.flag) {
                for (auto& word : res.words) cout << word << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "Break words using DP with spaced words2: " << endl;
        for (auto& str : strs) {
            auto res = obj.wordBreakWithSpaceWords2(str);
            cout << "Is Word break possible for str = " << str << " : " << res << endl;
            cout << endl;
        }
        cout << endl;
    }

    bool wordBreakRecursion(string str)
    {
        if (str.empty()) return true;
        for (int i = 1; i <= str.size(); i++) {
            if (dict.find(str.substr(0, i)) != dict.end()) {
                if (wordBreakRecursion(str.substr(i))) return true;
            }
        }
        return false;
    }

    bool wordBreakRecursion(string str, vector<string>& result)
    {
        if (str.empty()) return true;
        for (int i = 1; i <= str.size(); i++) {
            string cur = str.substr(0, i);
            if (dict.find(cur) != dict.end() && wordBreakRecursion(str.substr(i), result)) {
                result.push_back(cur);
                return true;
            }
        }
        return false;
    }

    bool wordBreakDP(string str)
    {
        int n = str.length();
        bool* table = new bool[n + 1];
        table[0] = true;
        for (int i = 1; i <= n; i++) table[i] = false;

        for (int i = 1; i <= n; i++) {
            if (!table[i]) table[i] = (dict.find(str.substr(0, i)) != dict.end());
            if (table[i]) {
                for (int j = i; j <= n; j++) {
                    if (dict.find(str.substr(i, j - i)) != dict.end()) {
                        table[j] = true;
                    }
                }
            }
            if (table[n]) break;
        }

        return table[n];
    }

    Node wordBreakDPWithSpacedWords(string str)
    {
        int n = str.length();
        Node* table = new Node[n + 1];
        table[0] = { true, {} };
        for (int i = 1; i <= n; i++) table[i] = { false, {} };

        for (int i = 1; i <= n; i++) {
            if (!table[i].flag)
            {
                if ((dict.find(str.substr(0, i)) != dict.end())) {
                    table[i] = { true, {str.substr(0,i)} };
                }
            }
            if (table[i].flag) {
                for (int j = i; j <= n; j++) {
                    if (!table[j].flag && dict.find(str.substr(i, j - i)) != dict.end()) {
                        vector<string> old = table[i].words;
                        table[j].words.insert(table[j].words.begin(), old.begin(), old.end());
                        table[j].words.push_back(str.substr(i, j - 1));
                        table[j].flag = true;
                    }
                }
            }
            if (table[n].flag) break;
        }

        return table[n];
    }

    bool wordBreakWithSpaceWords2(string str)
    {
        int n = str.length();
        vector<vector<Point>> memo(n + 1);
        memo[0] = { {} };

        for (int i = 1; i <= n; i++) {
            string cur = str.substr(0, i);
            if (dict.find(cur) != dict.end()) {
                memo[i].push_back({ 0,i });
            }

            if (!memo[i].empty())
            {
                for (int j = i + 1; j <= n; j++)
                {
                    cur = str.substr(i, j - i);
                    if (dict.find(cur) != dict.end())
                    {
                        memo[j].push_back({ i,j - i });
                    }
                }
            }
        }

        if (!memo[n].empty()) {
            printPath(str, memo, n, {});
            return true;
        }

        return false;
    }

    void printPath(string str, vector<vector<Point>> memo, int n, vector<string> cur)
    {
        if (n == 0) {
            reverse(cur.begin(), cur.end());
            cout << cur << endl;
            return;
        }
        for (auto& p : memo[n])
        {
            cur.push_back(str.substr(p.x, p.y));
            printPath(str, memo, n - p.y, cur);
            cur.pop_back();
        }
    }
};