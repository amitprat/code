#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=5389078581215232

Given two strings a and b, find whether any anagram of string a is a sub-string of string b. For eg:
if a = xyz and b = afdgzyxksldfm then the program should return true.

It is a trick question. First of all, one must realize that solutions like "produce all anagrams..." / search for each in string2 are damn slow,
 even if we use Boyer-More / Robin Karp and all good stuff. So just forget about this path. Instead, there is a linear solution.

Notice that if any contiguous part of s2 contains contains all characters from s1 and in the same amount, it is an anagram of s1 by definition.

So here is the algo:
Walk s2,
  while current letter is in s1: count it
  otherwise (letter not in s1): it cannot belong to an anagram,
  so we have what we have ("if solution_found..." - great)
  otherwise start over ("h2 = {}") hoping for the best.

Output:
Processing: {abcde, bcd} : Found substr = bcd at {{1,3}, }
Processing: {aaaaaa, aa} : Found substr = aa at {{0,1}, {1,2}, {2,3}, {3,4}, {4,5}, }
Processing: {abcdefghcde, cde} : Found substr = cde at {{2,4}, {8,10}, }
*/

class AnagramSubstringSearch {
   public:
    static void test() {
        AnagramSubstringSearch obj;
        vector<pair<string, string>> tests = {
            {"abcde", "bcd"},
            {"aaaaaa", "aa"},
            {"abcdefghcde", "cde"},
            {"afdgzyxksldfm", "xyz"}};

        for (auto test : tests) {
            cout << "Processing: {" << test.first << ", " << test.second << "} : ";

            vector<pair<int, int>> positions;
            auto found = obj.isAnagramSubstring(test.first, test.second, positions);

            if (found) {
                cout << "Found substr = " << test.second << " at : " << positions << endl;
            }
        }
    }

   public:
    bool isAnagramSubstring(string txt, string pat, vector<pair<int, int>>& positions) {
        vector<pair<int, int>> firstResult = isAnagramSubstring1(txt, pat);
        if (firstResult.size() == 0) return false;
        positions = firstResult;

        return true;
    }

   private:
    vector<pair<int, int>> isAnagramSubstring1(string txt, string pat) {
        vector<pair<int, int>> res;
        int m = pat.length();
        int n = txt.length();
        int patFreq[256] = {0};
        int txtFreq[256] = {0};

        for (int i = 0; i < m; i++) {
            patFreq[pat[i]]++;
            txtFreq[txt[i]]++;
        }

        for (int i = m; i <= n; i++) {
            if (match(patFreq, txtFreq)) res.push_back({i - m, i - 1});

            txtFreq[txt[i - m]]--;         // move left pointer
            if (i < n) txtFreq[txt[i]]++;  // move right pointer
        }

        return res;
    }

    bool match(int patFreq[], int txtFreq[]) {
        for (int i = 0; i < 256; i++)
            if (txtFreq[i] != patFreq[i]) return false;
        return true;
    }

   private:
    bool isAnagramSubstring2(string& s, string& p) {
        int m = p.length();
        int patCount[256] = {0};
        int txtCount[256] = {0};
        for (auto ch : p) patCount[ch]++;

        int start = 0;
        int curCount = 0;
        for (auto& ch : s) {
            txtCount[ch]++;
            while (txtCount[ch] > patCount[ch]) {
                if (txtCount[s[start]] <= patCount[s[start]]) curCount--;

                txtCount[s[start]]--;
                start++;
            }
            curCount++;

            if (curCount == m) return true;
        }

        return false;
    }

   private:
    bool isAnagramSubstring3(string a, string b, string& anagram, int& pos) {
        int aFreq[26] = {0};
        int bFreq[26] = {0};

        int l1 = a.length();
        for (int i = 0; i < l1; i++) {
            char ch1 = a[i];
            char ch2 = b[i];

            aFreq[ch1 - 'a']++;
            bFreq[ch2 - 'a']++;
        }

        int l2 = b.length();
        for (int i = l1; i <= l2; i++) {
            if (same(aFreq, bFreq)) {
                pos = i - l1;
                anagram = b.substr(pos, l1);
                return true;
            }

            if (i < l2) {
                char ch = b[i];
                bFreq[ch - 'a']++;
                bFreq[b[i - l1] - 'a']--;
            }
        }

        return false;
    }

    bool same(int aFreq[], int bFreq[]) {
        for (int i = 0; i < 26; i++) {
            if (aFreq[i] != bFreq[i])
                return false;
        }

        return true;
    }

   private:
    bool isAnagramSubstring4(string a, string b, string& anagram, int& pos) {
        int l1 = a.length();
        int l2 = b.length();
        if (l2 < l1)
            return false;

        int aFreq[26] = {0};
        for (int i = 0; i < l1; i++) {
            char ch1 = a[i];
            aFreq[ch1 - 'a']++;
        }

        int bFreq[26] = {0};
        int cnt = 0;
        for (int i = 0; i < l2; i++) {
            char ch = b[i];
            bFreq[ch - 'a']++;
            if (bFreq[ch - 'a'] <= aFreq[ch - 'a'])
                cnt++;

            if (cnt == l1) {
                anagram = b.substr(i - l1 + 1, l1);
                pos = i - l1 + 1;
                return true;
            }

            // move left pointer
            if (i >= l1) {
                ch = b[i - l1 + 1];
                bFreq[ch - '0']--;
            }
        }

        return false;
    }

   private:
    bool isAnagramSubstring5(string a, string b) {
        int* aCount = new int[256];
        int* bCount = new int[256];
        memset(aCount, 0, sizeof(int) * 256);
        memset(bCount, 0, sizeof(int) * 256);

        for (int i = 0; i < b.size(); i++) {
            aCount[a[i]]++;
            bCount[b[i]]++;
        }
        int cnt = 0;

        for (int i = b.size(); i < a.size(); i++) {
            if (isSame(aCount, bCount)) {
                cout << "Found at index = " << (i - b.size()) << " to " << i - 1 << endl;
                return true;
            }
            int oldIndex = i - b.size();
            aCount[a[oldIndex]]--;
            aCount[a[i]]++;
        }

        if (isSame(aCount, bCount)) {
            cout << "Found at index = " << (a.size() - b.size()) << " to " << a.size() - 1 << endl;
            return true;
        }

        return false;
    }

    bool isSame(int a[], int b[]) {
        for (int i = 0; i < 256; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

   private:
    bool isAnagramSubstring6(string src, string dst) {
        int* srcCount = new int[256];
        int* dstCount = new int[256];
        memset(srcCount, 0, sizeof(int) * 256);
        memset(dstCount, 0, sizeof(int) * 256);

        int count = 0;
        for (int i = 0; i < dst.size(); i++) dstCount[dst[i]]++;
        for (int i = 0; i < dst.size() - 1; i++) {
            srcCount[src[i]]++;
            if (srcCount[src[i]] <= dstCount[src[i]]) count++;
        }
        for (int i = dst.size() - 1; i < src.size(); i++) {
            srcCount[src[i]]++;
            if (srcCount[src[i]] <= dstCount[src[i]]) count++;
            if (count == dst.size()) {
                cout << "Found at index = from " << (i - dst.size() + 1) << " to " << i << endl;
                return true;
            }
            srcCount[src[i - dst.size() + 1]]--;
        }
        return false;
    }

   private:
    bool isAnagramSubstring7(string src, string pat) {
        vector<int> srcCnt(256, 0);
        vector<int> patCnt(256, 0);
        int cnt = 0;
        int n = src.length(), m = pat.length();

        for (int i = 0; i < m; i++) patCnt[pat[i]]++;

        bool found = false;
        int i = 0;
        for (int j = 0; j < n; j++) {
            srcCnt[src[j]]++;
            if (srcCnt[src[j]] <= patCnt[src[j]]) cnt++;

            if (cnt == m) {
                while (i <= j && srcCnt[src[i]] > patCnt[src[i]]) i++;
                if (j - i + 1 == m) {
                    cout << "Anagram found at " << i << " to " << j << " = " << src.substr(i, j - i + 1) << endl;
                    found = true;
                }
                cnt--;
                srcCnt[src[i]]--;
                i++;
            }
        }

        return found;
    }
};