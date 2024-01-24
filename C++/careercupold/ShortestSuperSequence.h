#pragma once
#include "../Header.h"

/*
* https://www.geeksforgeeks.org/shortest-common-supersequence/
Given two strings str1 and str2, the task is to find the length of the shortest string that has both str1 and str2 as subsequences.

Examples :

Input:   str1 = "geek",  str2 = "eke"
Output: 5
Explanation:
String "geeke" has both string "geek"
and "eke" as subsequences.

Input:   str1 = "AGGTAB",  str2 = "GXTXAYB"
Output:  9
Explanation:
String "AGXGTXAYB" has both string
"AGGTAB" and "GXTXAYB" as subsequences.
*/

class ShortestSuperSequence {
public:
	static void test() {
		string X = "AGGTB";
		string Y = "GXTXAYB";

		int l1 = shortestSuperSequenceUsingLCS(X, Y);
		int l2 = shortestSuperSequence(X, Y);

		assert(l1 == l2);

		cout << "Shortest sequence length = " << l1 << endl;

		SuperSequence1 objl;
		SuperSequence2 obj2;

		cout << objl.shotestCommonSubsequence(X, Y) << endl;
		cout << obj2.shotestCommonSubsequence(X, Y) << endl;
	}

	static int shortestSuperSequenceUsingLCS(string a, string b) {
		int l1 = lcs(a, b, a.length(), b.length());
		int l2 = lcsDP(a, b, a.length(), b.length());

		assert(l1 == l2);

		return (a.length() + b.length() - l1);
	}

	static int shortestSuperSequence(string a, string b) {
		int l1 = shortestSuperSequenceRec(a, b, a.length(), b.length());
		int l2 = shortestSuperSequenceDP(a, b, a.length(), b.length());

		assert(l1 == l2);

		return l1;
	}

	static int shortestSuperSequenceRec(string a, string b, int n, int m) {
		if (n == 0) return m;
		if (m == 0) return n;

		if (a[n - 1] == b[m - 1]) return 1 + shortestSuperSequenceRec(a, b, n - 1, m - 1);

		return 1 + min(shortestSuperSequenceRec(a, b, n - 1, m), shortestSuperSequenceRec(a, b, n, m - 1));
	}

	static int shortestSuperSequenceDP(string a, string b, int n, int m) {
		vector<vector<int>> memo(n + 1, vector<int>(m + 1));

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				if (i == 0) memo[i][j] = j;
				else if (j == 0) memo[i][j] = i;
				else if (a[i - 1] == b[j - 1]) memo[i][j] = 1 + memo[i - 1][j - 1];
				else memo[i][j] = 1 + min(memo[i - 1][j], memo[i][j - 1]);
			}
		}

		return memo[n][m];
	}

	static int lcs(string a, string b, int n, int m) {
		if (n == 0 || m == 0) return 0;

		if (a[n - 1] == b[m - 1]) return 1 + lcs(a, b, n - 1, m - 1);

		return max(lcs(a, b, n - 1, m), lcs(a, b, n, m - 1));
	}

	static int lcsDP(string a, string b, int n, int m) {
		vector<vector<int>> memo(n + 1, vector<int>(m + 1));

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				if (i == 0 || j == 0) memo[i][j] = 0;
				else if (a[i - 1] == b[j - 1]) memo[i][j] = 1 + memo[i - 1][j - 1];
				else memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
			}
		}

		return memo[n][m];
	}

	class SuperSequence1 {
	public:
		int shotestCommonSubsequence(string& str1, string& str2) {
			int l = lcs(str1, str2);

			return str1.size() + str2.size() - l;
		}

		int lcs(string& s1, string& s2) {
			int l1 = lcsUsingRec(s1, s1.length(), s2, s2.length());
			int l2 = lcsUsingDP(s1, s2);
			assert(l1 == l2);

			return l1;
		}

		int lcsUsingRec(string& s1, int l1, string& s2, int l2) {
			if (l1 == 0 || l2 == 0) return 0;
			if (s1[l1 - 1] == s2[l2 - 1]) return 1 + lcsUsingRec(s1, l1 - 1, s2, l2 - 1);

			return max(lcsUsingRec(s1, l1 - 1, s2, l2), lcsUsingRec(s1, l1, s2, l2 - 1));
		}

		int lcsUsingDP(string& s1, string& s2) {
			int l1 = s1.length();
			int l2 = s2.length();

			vector<vector<int>> memo(l1 + 1, vector<int>(l2 + 1));

			for (int i = 0; i <= l1; i++) {
				for (int j = 0; j <= l2; j++) {
					if (i == 0 || j == 0) memo[i][j] = 0;
					else if (s1[i - 1] == s2[j - 1]) memo[i][j] = 1 + memo[i - 1][j - 1];
					else memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
				}
			}

			return memo[l1][l2];
		}
	};

	class SuperSequence2 {
	public:
		int shotestCommonSubsequence(string& s1, string& s2) {
			int l1 = shotestCommonSubsequenceRec(s1, s1.length(), s2, s2.length());
			int l2 = shotestCommonSubsequenceDP(s1, s2);

			assert(l1 == l2);

			return l1;
		}

		int shotestCommonSubsequenceRec(string& s1, int l1, string& s2, int l2) {
			if (l1 == 0 || l2 == 0) return (l1 == 0) ? l2 : l1;

			if (s1[l1 - 1] == s2[l2 - 1]) return 1 + shotestCommonSubsequenceRec(s1, l1 - 1, s2, l2 - 1);
			return 1 + min(shotestCommonSubsequenceRec(s1, l1 - 1, s2, l2), shotestCommonSubsequenceRec(s1, l1, s2, l2 - 1));
		}

		int shotestCommonSubsequenceDP(string& s1, string& s2) {
			int l1 = s1.length(), l2 = s2.length();
			vector<vector<int>> memo(l1 + 1, vector<int>(l2 + 1));

			for (int i = 0; i <= l1; i++) {
				for (int j = 0; j <= l2; j++) {
					if (i == 0) memo[i][j] = j;
					else if (j == 0) memo[i][j] = i;
					else if (s1[i - 1] == s2[j - 1]) memo[i][j] = 1 + memo[i - 1][j - 1];
					else memo[i][j] = 1 + min(memo[i - 1][j], memo[i][j - 1]);
				}
			}

			return memo[l1][l2];
		}
	};
};