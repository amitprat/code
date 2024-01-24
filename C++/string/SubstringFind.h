#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

class SubstringFind {
public:
    static void test() {
        SubstringFind obj;
        vector<pair<string, vector<string>>> tests = {
            {"barfoothefoobarman", {"foo","bar"}},
            {"wordgoodbestware",{"ware","good","best","word"}}
        };

        for (auto test : tests) {
            auto res = obj.findSubstring(test.first, test.second);
            cout << "[";
            for (auto i : res) cout << i << ", ";
            cout << "]" << endl;
        }
    }

    vector<int> findSubstring(string s, vector<string>& words) {
        if (s.length() == 0 || words.size() == 0) return {};

        vector<int> v;
        int l = words.size();
        int mask = (1 << l) - 1;

        unordered_set<string> set;
        for (auto word : words) set.insert(word);
        int cur = 0;
        int offset = words[0].size();
        int start = l - 1;
        for (int i = 0; i <= s.length(); i += offset) {
            string tmp = s.substr(i, offset);
            if (set.find(tmp) != set.end()) {
                cur |= (1 << start);
                start--;
            }
            else {
                if (!(cur ^ mask)) v.push_back(i - l * offset);
                cur = 0;
                start = l - 1;
            }
        }

        return v;
    }
};