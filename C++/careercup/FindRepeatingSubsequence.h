#pragma once
#include "../Header.h"
/*
Given a string (1-d array) , find if there is any sub-sequence that repeats itself.
Here, sub-sequence can be a non-contiguous pattern, with the same relative order.

Eg:
1. abab <------yes, ab is repeated
2. abba <---- No, a and b follow different order
3. acbdaghfb <-------- yes there is a followed by b at two places
4. abcdacb <----- yes a followed by b twice

The above should be applicable to ANY TWO (or every two) characters in the string and optimum over time.
In the sense, it should be checked for every pair of characters in the string.

We can implement this as a variation of the longest common subsequence in O(n^2), using dynamic programming.
In the general problem, given two strings, 'a' and 'b', we find the longest common subsequence by computing
a matrix M of size len(a)* len(b) defined as follows: M[ i ][ j ] is the value of the longest common subsequence
between the strings "a0...ai" and "b0...bj".
In particular, if a[i]==b[j], then M[i][j]=max(1 + M[i-1][j-1], M[i - 1][j], M[i][j-1]),otherwise M[i][j]=max(M[i-1][j], M[i][j-1]).
The value of longest common subsequence is therefore M[len(a) -1][len(b) - 1].

Now we can modify the longest_common_subsequence(a, a) to find the value of the longest repeated subsequence in a by excluding
the cases when i == j, (which we know are always equal in this case).
*/
class FindRepeatingSubsequence {
   public:
    static void test() {
        FindRepeatingSubsequence obj;
        vector<string> inputs = {
            "abab", "abba", "acbdaghfb", "abcdacb"};
        for (const auto& input : inputs) {
            auto res = obj.isRepeatedSubsequence("abab");
            cout << format("input={} is repeated={}", input, res) << endl;
        }
    }

   public:
    bool isRepeatedSubsequence(const string& s1) {
        int n = s1.length();

        vector<vector<int>> memo(n + 1, vector<int>(n + 1));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0) {
                    memo[i][j] = 0;
                } else if (i != j && s1[i] == s1[j]) {
                    memo[i][j] = 1 + memo[i - 1][j - 1];
                } else {
                    memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
                }
            }
        }

        return memo[n - 1][n - 1] > 1;
    }
};