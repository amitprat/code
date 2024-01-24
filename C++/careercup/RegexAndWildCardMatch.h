#include "../header.h"

/*
https://careercup.com/question?id=6631993756352512
https://careercup.com/question?id=19587667

Given a regular expression with characters a-z, ' * ', ' . '
the task was to find if that string could match another string with characters from: a-z
where ' * ' can delete the character before it, and ' . ' could match whatever character. ' * ' always appear after a a-z character.
Example:
isMatch("a*", "") = true;
isMatch(".", "") = false;
isMatch("ab*", "a") = true;
isMatch("a.", "ab") = true;
isMatch("a", "a") = true;

private boolean isMatched(String regex, String str) {
    if (str.length() == 0) {
        // Match is true when regex is exhausted or it's last char is "*" - allowing optional str
        return regex.length() == 0 || regex.charAt(regex.length() - 1) == '*';
    }

    if (regex.length() == 0) {
        // Match is true only if str is fully consumed
        return str.length() == 0;
    }

    Character curReg = regex.charAt(0);
    Character nextReg = regex.length() >= 2 ? regex.charAt(1) : null;
    Character curStr = str.length() != 0 ? str.charAt(0) : null;

    if (nextReg == null || (nextReg != '*' && nextReg != '+')) {
        // This is a simple match - just take the first char from both regex and str and recurse IFF current match is detected
        return isCharMatched(curReg, curStr) && isMatched(regex.substring(1), str.substring(1));
    } else {
        if (nextReg == '*') {
            // The current regex char is followed by "*" - create 2 branches:
            // - one with unmodified regex and reduced str IFF current match detected - meaning to continue repetition if possible
            // - the other one with reduced regex and unmodified str - meaning to try out the optional nature of "*"
            return (isCharMatched(curReg, curStr) && isMatched(regex, str.substring(1)))
                    || isMatched(regex.substring(2), str);
        } else if (nextReg == '+') {
            // The current regex char is followed by "+" - reduce to 1 branch with "*" instead of "+"
            return isCharMatched(curReg, curStr) && isMatched(curReg + "*" + regex.substring(2), str.substring(1));
        } else {
            return false;
        }
    }
}

private boolean isCharMatched(Character regexCh, Character strCh) {
    return regexCh == strCh || (regexCh == '.' && strCh >= 'a' && strCh <='z');
}
*/
class RegexAndWildCardMatch {
   public:
    static void test() {
        RegexAndWildCardMatch obj;
        assert(obj.isRegexMatch("b", "a*") == false);
        assert(obj.isRegexMatch("", "a*") == true);
        assert(obj.isRegexMatch("", ".") == false);
        assert(obj.isRegexMatch("a", "ab*") == true);
        assert(obj.isRegexMatch("ab", "a.") == true);
        assert(obj.isRegexMatch("a", "a") == true);
        assert(obj.isRegexMatch("abccccde", "ab.*def*") == true);

        assert(obj.isWildMatch("b", "a*") == false);
        assert(obj.isWildMatch("baa", "?a*") == true);
        assert(obj.isWildMatch("bc", "*?") == true);
        assert(obj.isWildMatch("abcccc", "a?*") == true);
        assert(obj.isWildMatch("ab", "a?") == true);
        assert(obj.isWildMatch("a", "a") == true);
        assert(obj.isWildMatch("abccccdefff", "ab?*def*") == true);

        cout << "All matched" << endl;
    }

   public:
    bool isRegexMatch(string s1, string s2) {
        char *c1 = const_cast<char *>(s1.c_str());
        char *c2 = const_cast<char *>(s2.c_str());

        auto res1 = isRegexMatch1(c1, c2);
        auto res2 = isRegexMatch2(s1, s2);
        auto res3 = isRegexMatchDP(s1, s2);

        assert(res1 == res2);
        assert(res1 == res3);

        return res1;
    }

    bool isWildMatch(string s1, string s2) {
        char *c1 = const_cast<char *>(s1.c_str());
        char *c2 = const_cast<char *>(s2.c_str());

        auto res1 = wildCardMatch1(c1, c2);
        auto res2 = wildCardMatch2(s1, s2);
        auto res3 = wildCardMatchDP(s1, s2);

        assert(res1 == res2);
        assert(res1 == res3);

        return res1;
    }

   private:
    bool isRegexMatch1(char *t, char *p) {
        if (!*p) return (*t == '\0');

        if (*(p + 1) != '*')
            return (*p == *t || (*p == '.' && *t != '\0')) && isRegexMatch1(t + 1, p + 1);
        if (*p == *t || (*p == '.' && *t != '\0'))
            return isRegexMatch1(t, p + 2) || isRegexMatch1(t + 1, p);
        return isRegexMatch1(t, p + 2);
    }

   private:
    bool isRegexMatch2(string txt, string pat) {
        return isRegexMatch2(txt, pat, txt.length(), pat.length());
    }

    bool isRegexMatch2(string txt, string pat, int n, int m) {
        if (m == 0) return n == 0;
        if (n == 0) return pat[m - 1] == '*' && isRegexMatch2(txt, pat, n, m - 2);

        if (txt[n - 1] == pat[m - 1] || pat[m - 1] == '.') return isRegexMatch2(txt, pat, n - 1, m - 1);
        if (pat[m - 1] == '*') {
            return isRegexMatch2(txt, pat, n, m - 2) ||
                   (m > 2 && (txt[n - 1] == pat[m - 2] || pat[m - 2] == '.')) && isRegexMatch2(txt, pat, n - 1, m);
        }
        return false;
    }

   private:
    bool isRegexMatchDP(string txt, string pat) {
        int n = txt.length();
        int m = pat.length();
        vector<vector<bool>> table(n + 1, vector<bool>(m + 1));

        table[0][0] = true;
        for (int i = 1; i <= n; i++) table[i][0] = false;  // when pat is empty

        table[0][1] = false;                                                           // if txt is empty and pat is only 1 char, then it should be false.
        for (int j = 2; j <= m; j++) table[0][j] = (pat[j - 1] == '*' && pat[j - 2]);  // if pattern is like a* then, we can remove both to match.

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '.')
                    table[i][j] = table[i - 1][j - 1];
                else if (j >= 2 && pat[j - 1] == '*')
                    table[i][j] = table[i][j - 2] || (table[i - 1][j] && (txt[i - 1] == pat[j - 2] || pat[j - 2] == '.'));
                else
                    table[i][j] = false;
            }
        }

        return table[n][m];
    }

   private:
    bool wildCardMatch1(char *t, char *p) {
        if (!*t && !*p) return true;
        if (!*t && *p == '*' && *(p + 1) != '\0') return false;
        if (*p == *t || *p == '?') return wildCardMatch1(t + 1, p + 1);
        if (*p == '*')
            return wildCardMatch1(t, p + 1) || wildCardMatch1(t + 1, p);
        return false;
    }

   private:
    bool wildCardMatch2(string txt, string pat) {
        return wildCardMatch2(txt, pat, txt.length(), pat.length());
    }
    bool wildCardMatch2(string txt, string pat, int n, int m) {
        if (m == 0) return n == 0;
        if (n == 0) return pat[m - 1] == '*' && wildCardMatch2(txt, pat, n, m - 1);
        if (txt[n - 1] == pat[m - 1] || pat[m - 1] == '?')
            return wildCardMatch2(txt, pat, n - 1, m - 1);
        else if (pat[m - 1] == '*')
            return wildCardMatch2(txt, pat, n - 1, m) || wildCardMatch2(txt, pat, n, m - 1);
        else
            return false;
    }

   private:
    bool wildCardMatchDP(string txt, string pat) {
        int n = txt.length();
        int m = pat.length();

        vector<vector<bool>> table(n + 1, vector<bool>(m + 1));

        table[0][0] = true;
        for (int i = 1; i <= n; i++) table[i][0] = false;                                        // when pattern is empty
        for (int j = 1; j <= m; j++) table[0][j] = pat[j - 1] == '*' ? table[0][j - 1] : false;  // when text is empty

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (pat[j - 1] == '?' || txt[i - 1] == pat[j - 1])
                    table[i][j] = table[i - 1][j - 1];
                else if (pat[j - 1] == '*')
                    table[i][j] = table[i][j - 1] || table[i - 1][j];
                else
                    table[i][j] = false;
            }
        }

        return table[n][m];
    }
};