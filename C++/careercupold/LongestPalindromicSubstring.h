#pragma once
#include "../Header.h"

class LongestPalindromicSubstring {
public:
	static void test() {
		LongestPalindromicSubstring obj;

		{
			string str = "forgeeksskeegfor";
			auto res = obj.longestPalSubstr(str);
			cout << format("Longest palindromic substring for str='{}' is '{}'", str, res) << endl;
		}

		{
			string str = "abcsdc";
			auto res = obj.longestPalSubstr(str);
			cout << format("Longest palindromic substring for str='{}' is '{}'", str, res) << endl;
		}

		{
			string str = "sdfacxcasvsa";
			auto res = obj.longestPalSubstr(str);
			cout << format("Longest palindromic substring for str='{}' is '{}'", str, res) << endl;
		}
	}

	string longestPalSubstr(string str) {
		string res1 = longestPalSubstrExpandAroundCenter(str);
		string res2 = longestPalSubstrDP(str);

		assert(res1 == res2);

		return res1;
	}

	string longestPalSubstrExpandAroundCenter(string str) {
		string res;
		int n = str.length();
		for (int i = 0; i < n; i++) {
			auto cur = expand(str, i, i, n);
			if (cur.length() > res.length()) res = cur;
		}

		for (int i = 0; i < n - 1; i++) {
			auto cur = expand(str, i, i + 1, n);
			if (cur.length() > res.length()) res = cur;
		}

		return res;
	}

	string expand(string& str, int l, int r, int n) {
		while (l >= 0 && r < n && str[l] == str[r]) {
			l--; r++;
		}
		return str.substr(l + 1, r - l - 1);
	}

	string longestPalSubstrDP(string str) {
		string longest = "";
		int n = str.length();
		vector<vector<bool>> table(n, vector<bool>(n, false));

		for (int i = 0; i < n; i++) {
			if (longest.length() < 1) longest = string(1, str[i]);
			table[i][i] = true;
		}
		for (int i = 0; i < n - 1; i++) {
			if (str[i] == str[i + 1]) {
				if (longest.length() < 2) longest = str[i] + str[i + 1];
				table[i][i + 1] = true;
			}
		}

		for (int p = 3; p <= n; p++) {
			for (int i = 0; i < n - p + 1; i++) {
				int j = i + p - 1;
				if (str[i] == str[j] && table[i + 1][j - 1]) {
					if (j - i + 1 > longest.length()) {
						longest = str.substr(i, j - i + 1);
					}
					table[i][j] = true;
				}
			}
		}

		return longest;
	}
};