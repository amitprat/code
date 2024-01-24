#pragma once
#include "../Header.h"

class RegexMatch {
public:
    static void test() {
        RegexMatch obj;
        assert(obj.isMatch("", "a*") == true);
        assert(obj.isMatch("", ".") == false);
        assert(obj.isMatch("a", "ab*") == true);
        assert(obj.isMatch("ab", "a.") == true);
        assert(obj.isMatch("a", "a") == true);
    }

    bool isMatch(string txt, string pat) {
        return isMatch(txt, pat, txt.size(), pat.size());
    }

private:
    bool isMatch(string txt, string pat, int n, int m) {
        if (n == 0 && m == 0) return true;
        if (n < 0 || m == 0) return false;
        if (n > 0 && (txt[n - 1] == pat[m - 1])) return true;

        if (pat[m - 1] == '*')
            return isMatch(txt, pat, n - 1, m) || isMatch(txt, pat, n, m - 2);
        if (pat[m - 1] == '.' || (n > 0 && txt[n - 1] == pat[m - 1]))
            return isMatch(txt, pat, n - 1, m - 1);

        return false;
    }
};