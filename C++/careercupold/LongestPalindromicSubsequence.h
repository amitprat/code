#pragma once
#include "../Header.h"

class LongestPalindromicSubsequence {
public:
	static void test() {
		LongestPalindromicSubsequence obj;

		{
			string str = "a";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}

		{
			string str = "aba";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}

		{
			string str = "abba";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}

		{
			string str = "abcba";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}

		{
			string str = "abcdasdafxcfdsg";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}

		{
			string str = "iafn asdaad sdf";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}

		{
			string str = "GEEKS FOR GEEKS";
			auto res = obj.lps(str);
			cout << format("Longest palindromic subsequence in '{}' is '{}'", str, res) << endl;
		}
	}

	string lps(string seq) {
		int l1 = lpsDP(seq);
		int l2 = lpsRec(seq, 0, seq.length() - 1);

		string res1 = lpsRecStr(seq, 0, seq.length() - 1);
		string res2 = lpsStrDP(seq);

		assert(l1 == l2);
		assert(res1 == res2);
		assert(l1 == res1.length());
		assert(l2 == res2.length());

		return res1;
	}

	int lpsRec(string str, int l, int r) {
		if (l > r) return 0;
		if (l == r) return 1;

		if (str[l] == str[r]) {
			return 2 + lpsRec(str, l + 1, r - 1);
		}
		else {
			return max(lpsRec(str, l + 1, r), lpsRec(str, l, r - 1));
		}
	}

	string lpsRecStr(string str, int l, int r) {
		if (l > r) return "";
		if (l == r) return str.substr(l, r - l + 1);

		if (str[l] == str[r]) {
			return str[l] + lpsRecStr(str, l + 1, r - 1) + str[r];
		}
		else {
			string ls = lpsRecStr(str, l + 1, r);
			string rs = lpsRecStr(str, l, r - 1);

			return ls.length() > rs.length() ? ls : rs;
		}
	}

	int lpsDP(string str) {
		int n = str.length();
		vector<vector<int>> memo(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++) memo[i][i] = 1;

		for (int p = 2; p <= n; p++) {
			for (int i = 0; i < n - p + 1; i++) {
				int j = i + p - 1;
				if (str[i] == str[j]) {
					if (p == 2) memo[i][j] = 2;
					else memo[i][j] = 2 + memo[i + 1][j - 1];
				}
				else {
					memo[i][j] = max(memo[i + 1][j], memo[i][j - 1]);
				}
			}
		}

		return memo[0][n - 1];
	}

	string lpsStrDP(string str) {
		int n = str.length();
		vector<vector<int>> memo(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++) memo[i][i] = 1;

		for (int p = 2; p <= n; p++) {
			for (int i = 0; i < n - p + 1; i++) {
				int j = i + p - 1;
				if (str[i] == str[j]) {
					if (p == 2) memo[i][j] = 2;
					else memo[i][j] = 2 + memo[i + 1][j - 1];
				}
				else {
					memo[i][j] = max(memo[i + 1][j], memo[i][j - 1]);
				}
			}
		}

		string left, right;
		int l = 0, r = n - 1;
		while (l <= r) {
			if (l == r) left += str[l++];
			else if (str[l] == str[r]) {
				left += str[l++]; right = str[r--] + right;
			}
			else if (memo[l + 1][r] > memo[l][r - 1]) l++;
			else r--;
		}

		return left + right;
	}
};