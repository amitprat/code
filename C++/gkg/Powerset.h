#pragma once
#include "../Header.h"

class Powerset {
public:
    static void test() {
        Powerset obj;
        vector<int> s = { 1,2,2 };
        obj.powersetBinaryWithDups(s);
    }

    void powersetRecursion(vector<int> s) {
        powersetRecursion(s, 0, {});
    }

    void powersetRecursionWithDups(vector<int> s) {
        powersetRecursionWithDups(s, 0, {});
    }

    void powersetBinary(vector<int> s) {
        int cnt = pow(2, s.size());
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < s.size(); j++) {
                if (i & (1 << j)) cout << s[j] << " ";
            }
            cout << endl;
        }
    }

    void powersetBinaryWithDups(vector<int> s) {
        int cnt = pow(2, s.size());
        unordered_set<string> set;
        for (int i = 0; i < cnt; i++) {
            string str;
            for (int j = 0; j < s.size(); j++) {
                if (i & (1 << j)) str += to_string(s[j]) + " ";
            }
            set.insert(str);
        }
        for (auto s : set) cout << s << endl;
        cout << endl;
    }
private:
    void powersetRecursion(vector<int> s, int i, vector<int> cur) {
        if (i == s.size()) {
            print(cur);
            return;
        }

        powersetRecursion(s, i + 1, cur);
        cur.push_back(s[i]);
        powersetRecursion(s, i + 1, cur);
    }

    void powersetRecursionWithDups(vector<int> s, int i, vector<int> cur) {
        if (i == s.size()) {
            print(cur);
            return;
        }
        cur.push_back(s[i]);
        powersetRecursionWithDups(s, i + 1, cur);
        cur.pop_back();

        while (i < s.size() - 1 && s[i] == s[i + 1]) {
            i++;
        }
        powersetRecursionWithDups(s, i + 1, cur);
    }
};