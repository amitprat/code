/*
https://careercup.com/question?id=5389078581215232

Given two strings a and b, find whether any anagram of string a is a sub-string of string b. For eg:
if a = xyz and b = afdgzyxksldfm then the program should return true.

It is a trick question. First of all, one must realize that solutions like "produce all anagrams..." / search for each in string2 are damn slow, even if we use Boyer-More / Robin Karp and all good stuff. So just forget about this path. Instead, there is a linear solution.

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
#include "../header.h"

class AnagramSubstrSearch {
   public:
    static void test() {
        AnagramSubstrSearch obj;
        vector<pair<string, string>> tests = {
            {"abcde", "bcd"},
            {"aaaaaa", "aa"},
            {"abcdefghcde", "cde"}};

        for (auto test : tests) {
            cout << "Processing: {" << test.first << ", " << test.second << "} : ";
            auto res = obj.substringSearch(test.first, test.second);
            cout << "Found substr = " << test.second << " at {";
            for (auto pos : res) cout << "{" << pos.first << "," << pos.second << "}, ";
            cout << "}" << endl;
        }
    }

   private:
    vector<pair<int, int>> substringSearch(string txt, string pat) {
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
            txtFreq[txt[i - m]]--;
            if (i < n) txtFreq[txt[i]]++;
        }

        return res;
    }

    bool match(int patFreq[], int txtFreq[]) {
        for (int i = 0; i < 256; i++)
            if (txtFreq[i] != patFreq[i]) return false;
        return true;
    }

   private:
    bool isAnagramPresent(string& s, string& p) {
        int m = p.length();
        int patCount[256] = {0};
        int txtCount[256] = {0};
        for (auto ch : p) patCount[ch]++;

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
};