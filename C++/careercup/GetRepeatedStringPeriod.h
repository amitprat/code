#pragma once
#include "../Header.h"

/*
Find whether string S is periodic.
Periodic indicates S = nP.
e.g.
S = "ababab", then n = 3, and P = "ab"
S = "xxxxxx", then n = 1, and P = "x"
S = "aabbaaabba", then n = 2, and P = "aabba"
follow up:
Given string S, find out the P (repetitive pattern) of S.
*/
class GetPeriod {
public:
	static void test() {
		vector<string> strs = { "waterwater", "ababab", "xxxxxx", "aabbaaabba", "abcd", "dbcasdssddbcasds" };
		GetPeriod obj;

		for (auto str : strs) {
			auto res = obj.isPeriod(str);
			cout << "Is string='" << str << "' periodic: " << res << endl;

			if (res) {
				auto p = obj.getPeriod(str);
				cout << "Period = " << p.first << ", " << p.second << endl;
			}
		}
	}

	bool isPeriod(string s) {
		string tmp = s + s;
		tmp = tmp.substr(1, tmp.length() - 2);
		return (tmp.find(s) != string::npos);
	}

	pair<string, int> getPeriod(string s) {
		int n = s.length();
		for (int len = 1; len <= n / 2; len++) {
			if (n % len == 0 && isRepeat(s, len, n)) {
				return { s.substr(0,len),n / len };
			}
		}
		return { "",-1 };
	}

	bool isRepeat(string s, int periodLen, int totalLen) {
		for (auto i = 0; i < periodLen; i++) {
			for (int j = periodLen + i; j < totalLen; j += periodLen) {
			    if (s[i] != s[j]) return false;
			}
		}
		return true;
	}
};

/*
boolean isPeriod(String s) {
		StringBuilder str = new StringBuilder(s   s);
		str.deleteCharAt(0);
		str.deleteCharAt(str.length() - 1);
		return strStr(str.toString(), s); //KMP strStr(T, S) to find if T has S in it.
	}

	//Solution to follow-up
	//This method looks for the repeating pattern in string
	private static String getPeriod(String string) { // O(n * n)
		//for every possible period size i, check if it's valid
		for (int i = 1; i <= string.length() / 2; i  ) {
			if (string.length() % i == 0) {
				String period = string.substring(0, i);
				int j = i;
				while(j + i <= string.length()) {
					if (period.equals(string.substring(j, j   i))) {
						j = j + i;
						if(j == string.length()) { //period valid through entire string
							return period;
						}
					} else {
						break;
					}
				}
			}

		}
		return null; //string is not periodic
	}
*/