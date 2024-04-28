#pragma once
#include "../header.h"

class FindCommonElementsAcrossMultipleArrays {
   public:
    static void test() {
        FindCommonElementsAcrossMultipleArrays obj;

        vector<int> v1 = {1, 2, 3, 4, 5};
        vector<int> v2 = {2, 4, 5, 8, 10};
        vector<int> v3 = {3, 5, 7, 9, 11};

        auto res = obj.findCommons(v1, v2, v3);

        cout << "Input: " << endl;
        cout << v1 << endl;
        cout << v2 << endl;
        cout << v3 << endl;

        cout << "Output: " << res << endl;
    }

   public:
    vector<int> findCommons(vector<int> v1, vector<int> v2, vector<int> v3) {
        vector<int> res;
        unordered_map<int, unordered_set<int>> m;
        for (auto i : v1) m[i].insert(0);
        for (auto i : v2) m[i].insert(1);
        for (auto i : v3) m[i].insert(2);

        for (auto i : m) {
            if (i.second.size() == 3) res.push_back(i.first);
        }

        return res;
    }
};