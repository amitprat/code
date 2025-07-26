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
            {"barfoothefoobarman", {"foo", "bar"}, {0, 9}},
            {"catbatatecatatebat", {"cat", "ate", "bat"}, {0, 3, 9}},
            {"abcdababcd", {"ab", "ab", "cd"}, {0, 2, 4}},
            {"abcdababcd", {"ab", "ab"}, {4}}};
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

   public:
    vector<int> findSubstring2(string s, vector<string>& words) {
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

   public:
    vector<int> findSubstring(string str, vector<string>& words) {
        vector<int> result;
        if (words.empty()) return result;

        unordered_map<string, int> strsCnt;
        unordered_map<string, int> wordsCnt;

        for (auto& word : words) wordsCnt[word]++;
        int wordLen = words[0].size();

        int curCnt = 0;
        for (int s = 0, e = 0; e < str.length(); e += wordLen) {
            auto part = str.substr(e, wordLen);
            strsCnt[part]++;
            if (strsCnt[part] <= wordsCnt[part]) curCnt++;

            if (curCnt == words.size()) {
                auto startWord = str.substr(s, wordLen);
                while (strsCnt[startWord] > wordsCnt[startWord]) {
                    s += wordLen;
                    strsCnt[startWord]--;
                    startWord = str.substr(s, wordLen);
                }

                result.push_back(s);
                cout << startWord << endl;
                strsCnt[startWord]--;
                s += wordLen;
                curCnt--;
            }
        }

        return result;
    }
};