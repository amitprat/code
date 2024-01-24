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
            {"x", "xyz"}};

        for (auto context : contexts) {
            cout << "Input:" << context.first << ", " << context.second << endl;
            char different1 = '\0';
            auto res1 = obj.isOneEditDistance(context.first, context.second, different1);
            char different2 = '\0';
            auto res2 = obj.isOneEditDistance2(context.first, context.second, different2);
            cout << "Res1 " << res1 << ", Res2 " << res2 << endl;
            assert(res1 == res2);
            assert(different1 == different2);
            assert(obj.isOneEditDistance3(context.first, context.second) == obj.isOneEditDistance4(context.first, context.second));
        }
    }

    bool isOneEditDistance(string first, string second, char& different) {
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
            } else
                i++;
        }
        return flag;
    }

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
            } else
                i++, j++;
        }
        if (!flag && i + 1 == second.length()) {
            flag = true;
            different = second[j];
        }
        return flag;
    }

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

   private:
    bool isOneEditDistance(string s, string t) {
        int m = s.length(), n = t.length();
        if (m > n) return isOneEditDistance(t, s);
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
};