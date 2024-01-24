#pragma once
#include "../header.h"

class SubstringWithConcatenationOfWords {
private:
    struct TestInput {
        string S;
        vector<string> L;
        vector<int> out;
    };

public:
    static void test() {
        SubstringWithConcatenationOfWords obj;
        vector<TestInput> tests = {
            {"barfoothefoobarman", {"foo", "bar"}, {0,9}},
            {"catbatatecatatebat", {"cat", "ate", "bat"},{0,3,9}},
            {"abcdababcd", {"ab", "ab", "cd"},{0,2,4}},
            {"abcdababcd", {"ab", "ab"},{4}}
        };
        for (auto& test : tests) {
            auto res = obj.getPositions(test.S, test.L);
            cout << to_string(res) << endl;
            assert(res == test.out);
        }
    }

    vector<int> getPositions(string S, vector<string> L) {
        vector<int> result;
        if (S.empty() || L.empty()) return result;
        int w = L[0].size();
        int n = L.size();
        int m = S.length();

        unordered_map<string, int> map;
        for (auto& word : L) map[word]++;

        for (int i = 0; i <= m - w * n; i++) {
            unordered_map<string, int> tmp(map);
            int j = i, count = n;
            while (j < i + w * n) {
                string cur = S.substr(j, w);
                if (map.find(cur) == map.end() || tmp[cur] == 0) break;
                tmp[cur]--;
                count--;
                j += w;
            }
            if (count == 0) result.push_back(i);
        }

        return result;
    }
};