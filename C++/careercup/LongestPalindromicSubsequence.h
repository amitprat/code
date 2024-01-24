#include "../header.h"

class LongestPalindromicSubsequence {
   public:
    static void test() {
        LongestPalindromicSubsequence obj;
        string s = "GEEKSFORGEEKS";

        vector<string> inputs = {"a", "GEEKSFORGEEKS", "aba", "abba", "abcba", "abcdasdafxcfdsg", "iafn asdaad sdf", "GEEKS FOR GEEKS"};
        for (auto s : inputs) {
            int l = obj.longestPalinSubsequence(s);
            cout << format("Longest palindromic subsequence in str={} is {}.", s, l) << endl;
        }
    }

    int longestPalinSubsequence(string s) {
        int l1 = longestPalinRec(s);
        int l2 = longestPalinUsingMemo(s);
        int l3 = longestPalinSubseqUsingDP1(s);
        int l4 = longestPalinSubseqUsingLCSDP(s);
        int l5 = longestPalinSubseqUsingDP3(s);

        assert(l1 == l2);
        assert(l1 == l3);
        assert(l1 == l4);
        assert(l1 == l5);

        string s1 = longestPalinRec2(s);
        string s2 = longestPalinSubseqUsingDP2(s);
        string s3 = getLongestPalindromicSubsequence(s);

        assert(s1 == s2);
        // assert(s1 == s3);

        cout << "Longest palindromic subsequence: " << s1 << endl;

        return l1;
    }

   private:
    int longestPalinRec(string s) {
        return longestPalinRec(s, 0, s.length() - 1);
    }

    int longestPalinRec(string& s, int l, int r) {
        if (l > r) return 0;
        if (l == r) return 1;

        if (s[l] == s[r]) return 2 + longestPalinRec(s, l + 1, r - 1);
        return max(longestPalinRec(s, l + 1, r), longestPalinRec(s, l, r - 1));
    }

   private:
    string longestPalinRec2(string s) {
        return longestPalinRec2(s, 0, s.length() - 1);
    }
    string longestPalinRec2(string str, int l, int r) {
        if (l > r) return "";
        if (l == r) return str.substr(l, r - l + 1);

        if (str[l] == str[r]) {
            return str[l] + longestPalinRec2(str, l + 1, r - 1) + str[r];
        } else {
            string ls = longestPalinRec2(str, l + 1, r);
            string rs = longestPalinRec2(str, l, r - 1);

            return ls.length() > rs.length() ? ls : rs;
        }
    }

   private:
    int longestPalinUsingMemo(string& s) {
        int n = s.length();
        vector<vector<int>> table(n, vector<int>(n, -1));

        return longestPalinUsingMemo(s, 0, n - 1, table);
    }

    int longestPalinUsingMemo(string& s, int l, int r, vector<vector<int>>& table) {
        if (l > r) return 0;
        if (l == r) return 1;
        if (table[l][r] != -1) return table[l][r];

        if (s[l] == s[r])
            table[l][r] = 2 + longestPalinUsingMemo(s, l + 1, r - 1, table);
        else
            table[l][r] = max(longestPalinUsingMemo(s, l + 1, r, table), longestPalinUsingMemo(s, l, r - 1, table));

        return table[l][r];
    }

   private:
    int longestPalinSubseqUsingDP1(string& s) {
        int n = s.length();
        vector<vector<int>> table(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) table[i][i] = 1;

        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n - l + 1; i++) {
                int j = i + l - 1;
                if (l == 2 && s[i] == s[j])
                    table[i][j] = 2;
                else if (s[i] == s[j])
                    table[i][j] = table[i + 1][j - 1] + 2;
                else
                    table[i][j] = max(table[i + 1][j], table[i][j - 1]);
            }
        }

        return table[0][n - 1];
    }

   private:
    int longestPalinSubseqUsingDP3(string str) {
        int n = str.length();
        vector<vector<int>> table(n, vector<int>(n, 0));

        for (int k = 1; k <= n; k++) {
            for (int i = 0; i < n - k + 1; i++) {
                int j = i + k - 1;
                if (i == j)
                    table[i][j] = 1;  // palin size=1
                else if (i + 1 == j && str[i] == str[j])
                    table[i][j] = 2;  // palin size=2
                else if (str[i] == str[j])
                    table[i][j] = max(table[i][j], 2 + table[i + 1][j - 1]);
                else
                    table[i][j] = max(table[i + 1][j], table[i][j - 1]);
            }
        }

        cout << to_string(table) << endl;

        return table[0][n - 1];
    }

   private:
    string longestPalinSubseqUsingDP2(string str) {
        int n = str.length();
        vector<vector<int>> memo(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) memo[i][i] = 1;

        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n - l + 1; i++) {
                int j = i + l - 1;
                if (l == 2 && str[i] == str[j])
                    memo[i][j] = 2;
                else if (str[i] == str[j])
                    memo[i][j] = 2 + memo[i + 1][j - 1];
                else
                    memo[i][j] = max(memo[i + 1][j], memo[i][j - 1]);
            }
        }

        string left, right;
        int l = 0, r = n - 1;
        while (l <= r) {
            if (l == r)
                left += str[l++];
            else if (str[l] == str[r]) {
                left += str[l++];
                right = str[r--] + right;
            } else if (memo[l + 1][r] > memo[l][r - 1])
                l++;
            else
                r--;
        }

        return left + right;
    }

   private:
    int longestPalinSubseqUsingLCSDP(string& s1) {
        int n = s1.length();
        string s2 = s1;
        reverse(s2.begin(), s2.end());
        vector<vector<int>> table(n + 1, vector<int>(n + 1));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else if (s1[i - 1] == s2[j - 1])
                    table[i][j] = 1 + table[i - 1][j - 1];
                else
                    table[i][j] = max(table[i - 1][j], table[i][j - 1]);
            }
        }

        return table[n][n];
    }

   private:
    string getLongestPalindromicSubsequence(string& s1) {
        string s2(s1.rbegin(), s1.rend());
        int n = s1.length();
        vector<vector<int>> table(n + 1, vector<int>(n + 1));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else if (s1[i - 1] == s2[j - 1])
                    table[i][j] = 1 + table[i - 1][j - 1];
                else
                    table[i][j] = max(table[i - 1][j], table[i][j - 1]);
            }
        }

        string result;
        for (int i = n, j = n; i > 0 && j > 0;) {
            if (s1[i - 1] == s2[j - 1]) {
                result += s1[i - 1];
                i--, j--;
            } else if (table[i - 1][j] > table[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        reverse(result.begin(), result.end());

        return result;
    }
};
