#pragma once
#include "../header.h"

class StringWithConcatOfOtherWords {
   public:
    static void test() {
        StringWithConcatOfOtherWords obj;
        string s = "barfoothefoobarman";
        vector<string> words = {"foo", "bar"};

        auto res = obj.findSubstring(s, words);
        println("Result = {0}", res);
    }

   public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.empty()) return result;

        unordered_map<string, int> wordsCnt;
        int sz = words[0].size();

        for (const auto& word : words) wordsCnt[word]++;

        for (unsigned int offset = 0; offset < sz; ++offset) {
            unordered_map<string, int> patCnt;
            int i = offset, j = offset;
            int size = 0;

            while (j < s.length()) {
                auto cur = s.substr(j, sz);
                j += sz;
                patCnt[cur]++;
                size++;

                while (patCnt[cur] > wordsCnt[cur]) {
                    patCnt[s.substr(i, sz)]--;
                    i += sz;
                    size--;
                }

                if (size == words.size()) {
                    result.push_back(i);
                }
            }
        }

        return result;
    }
};