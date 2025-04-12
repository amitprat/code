#pragma once
#include "../header.h"

class ListAnagrams {
   public:
    static void test(vector<string> v) {
        ListAnagrams obj;
        cout << "Input: ";
        for (auto i : v) cout << i << " ";
        cout << "Output: ";
        auto res = obj.listAnagrams(v);
        for (auto i : res) {
            cout << "[";
            for (auto j : i.second) cout << j << " ";
            cout << "] ";
        }
        cout << endl;
    }

    unordered_map<string, list<string>> listAnagrams(vector<string>& strs) {
        unordered_map<string, list<string>> res;
        for (auto& str : strs) {
            auto cur = str;
            sort(cur.begin(), cur.end());
            res[cur].push_back(str);
        }

        return res;
    }
};