#pragma once
#include "../Header.h"

//Recursive Solution : Slow

bool isMatch_regex(string s, string p, int idxS, int idxP) {
    if (idxP < 0) {
        // pattern is empty, true if string is empty else false
        return idxS < 0;
    }
    if (idxS < 0) {
        // If ip string is empty, need to check if the if pattern has characters in it
        bool res = false;
        if (p[idxP] == '*') {
            res = isMatch_regex(s, p, idxS, idxP - 2);
        }
        return res;
    }

    // If the last char matches, or pattern has '.', then there is
    // solution for this subproblem, need to evaluate for other
    // subproblems.
    if (s[idxS] == p[idxP] || p[idxP] == '.') {
        return isMatch_regex(s, p, idxS - 1, idxP - 1);
    }

    bool answer = false;
    if (p[idxP] == '*') {
        // If the last char is '*', then the last before char of p should match with last char of S,
        // if so exclude that char and proceed further
        if (s[idxS] == p[idxP - 1] || p[idxP - 1] == '.') {
            answer = isMatch_regex(s, p, idxS - 1, idxP);
        }

        answer = answer || isMatch_regex(s, p, idxS, idxP - 2);
    }
    return answer;
}

bool isMatch(string s, string p) {
    return isMatch_regex(s, p, s.length() - 1, p.length() - 1);
}

//Bottom Up Solution : Fast 4ms

bool isMatch(string s, string p) {
    // DP Table to store the intermediate results and +1 to store the results for empty string
    int dp[s.length() + 1][p.length() + 1];

    // if both ip str and pattern is empty
    dp[0][0] = true;

    // If pattern is empty, then all rows for which the chars are not empty are false
    for (int row = 0; row < s.length(); row++) {
        dp[row + 1][0] = false;
    }

    // If the ip string is rempty
    for (int col = 0; col < p.length(); col++)
    {
        dp[0][col + 1] = p[col] == '*' ? dp[0][col - 2 + 1] : false;
    }

    /*
     * follow the conditions of top down where if the characters are matching or if pattern char is '.',
     * then  solution  = dp [n-1][m-1]
     * If the pattern char is '*' then
     * check s[idxS] == p[idxP - 1] || p[idxP - 1] == '.' then
     *       solution  = dp[n-1][m] || dp[n][m-2]
     * else
     *       solution = dp[n][m-2]
     * If the last char doesn't match, then it should be false
    */
    for (int row = 1; row <= s.length(); row++) {
        for (int col = 1; col <= p.length(); col++) {
            // Chars doesn't match need to keep false
            bool answer = false;
            if (s[row - 1] == p[col - 1] || p[col - 1] == '.') {
                answer = dp[row - 1][col - 1];
            }
            else if (p[col - 1] == '*') {
                if (s[row - 1] == p[col - 2] || p[col - 2] == '.') {
                    answer = dp[row - 1][col];
                }
                answer = answer || dp[row][col - 2];
            }
            dp[row][col] = answer;
        }
    }
    return dp[s.length()][p.length()];
}