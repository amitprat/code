#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=5092486548553728
Given two strings, return boolean True/False, if they are only one edit apart.Edit can be insert/delete/update of only one character in the string. Eg:

-True
xyz,xz
xyz, xyk
xy, xyz

-False
xyz, xyz
xyz,xzy
x, xyz
*/

class OneEditDistance {
   public:
    static void test() {
        OneEditDistance obj;
        vector<pair<string, string>> contexts = {
            {"geek", "geeks"},
            {"cat", "cut"},
            {"sunday", "unday"},
            {"xyz", "xz"},
            {"xyz", "xyk"},
            {"xy", "xyz"},
            {"xyz", "xyz"},
            {"xyz", "xzy"},
            {"x", "xyz"},
            {"", "a"},
            {"a", ""},
            {"ab", "ac"},
            {"abc", "ac"}};

        for (auto& [s1, s2] : contexts) {
            cout << "Input: " << s1 << ", " << s2 << endl;
            char diff1 = '\0', diff2 = '\0';
            bool r1 = obj.isOneEditDistance1(s1, s2, diff1);
            bool r2 = obj.isOneEditDistance2(s1, s2, diff2);
            bool r3 = obj.isOneEditDistance3(s1, s2);
            bool r4 = obj.isOneEditDistance4(s1, s2);
            bool r5 = obj.isOneEditDistance5(s1, s2);
            bool r6 = obj.isOneEditDistance6(s1, s2);
            cout << "Res1: " << r1 << ", Res2: " << r2 << ", Res3: " << r3 << ", Res4: " << r4 << endl;
            assert(r1 == r2);
            assert(diff1 == diff2);
            assert(r3 == r4);
            assert(r4 == r5);
            assert(r5 == r6);
        }
    }

   public:
    // Incorrect: <Remove or fix it>
    bool isOneEditDistance0(string& first, string& second) {
        int n = first.length();
        int m = second.length();

        if (abs(n - m) > 1) return false;

        if (n != m) {
            if (n < m)
                return second.contains(first);
            else
                return first.contains(second);
        }

        int diff = 0;
        for (int i = 0; i < n; i++) {
            if (first[i] != second[i]) diff++;
        }

        return diff == 1;
    }

   public:
    bool isOneEditDistance1(string& first, string& second, char& different) {
        different = '$';
        bool flag = false;

        if (first.length() > second.length()) swap(first, second);
        if (second.size() - first.size() > 1) return false;

        for (int i = 0, j = 0; i < first.length() || j < second.length(); j++) {
            if (i == first.length() || first[i] != second[j]) {
                if (flag)
                    return false;
                else
                    flag = true;

                different = second[j];
                if (first.length() == second.length()) i++;
            } else {
                i++;
            }
        }

        return flag;
    }

   public:
    bool isOneEditDistance2(string first, string second, char& different) {
        different = '$';
        bool flag = false;

        if (first.length() > second.length()) swap(first, second);
        if (second.size() - first.size() > 1) return false;

        int i = 0, j = 0;
        while (i < first.size()) {
            if (first[i] != second[j]) {
                if (flag) return false;

                different = second[j];
                j++;
                if (first.length() == second.length()) i++;
                flag = true;
            } else {
                i++, j++;
            }
        }

        if (!flag && i + 1 == second.length()) {
            flag = true;
            different = second[j];
        }

        return flag;
    }

   public:
    bool isOneEditDistance3(string& first, string& second) {
        int n = first.length();
        int m = second.length();
        if (abs(n - m) > 1) return false;

        if (n > m) {
            swap(first, second);
            swap(n, m);
        }

        int i = 0;
        while (i < n) {
            if (first[i] != second[i]) {
                if (n < m)
                    return first.substr(i) == second.substr(i + 1);
                else
                    return first.substr(i + 1) == second.substr(i + 1);
            }

            i++;
        }

        return n != m;
    }

   public:
    bool isOneEditDistance4(string& first, string& second) {
        int n = first.length();
        int m = second.length();

        int diff = 0;
        for (int i = 0, j = 0; i < n || j < m; i++, j++) {
            if (i >= n || j >= m) {
                diff++;
                continue;
            }
            if (first[i] != second[j]) {
                diff++;
                if (n < m)
                    i--;
                else if (m < n)
                    j--;
            }
        }

        return diff == 1;
    }

   public:
    bool isOneEditDistance5(string s, string t) {
        int m = s.length(), n = t.length();
        if (m > n) return isOneEditDistance5(t, s);
        if (n - m > 1) return false;

        for (int i = 0; i < m; i++) {
            if (s[i] != t[i]) {
                if (m == n)
                    s[i] = t[i];
                else
                    s.insert(i, 1, t[i]);

                return s == t;
            }
        }

        return (m + 1 == n);
    }

   public:
    bool isOneEditDistance6(const string& s1, const string& s2) {
        int n = s1.length();
        int m = s2.length();
        if (abs(n - m) > 1) return false;
        if (n > m) isOneEditDistance6(s2, s1);

        bool diffseen = false;
        for (int i = 0, j = 0; i < n && j < m; i++, j++) {
            if (s1[i] != s2[j]) {
                if (diffseen) return false;
                diffseen = true;

                if (n != m) i--;
            }
        }

        return diffseen || (n < m);
    }
};