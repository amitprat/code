#pragma once
#include "../Header.h"

class RemoveBAndAC
{
public:
	static void test() {
		string s = "reababcct";

		string res1 = remove(s);
		string res2 = remove1(s);

		assert(res1 == res2);

		cout << res1 << endl;
	}

	static string remove(string str)
	{
		int i = 0;
		for (int j = 0; j < str.length(); j++) {
			if (str[j] == 'b') continue;
			else if (i > 0 && str[i - 1] == 'a' && str[j] == 'c') i -= 1;
			else str[i++] = str[j];
		}
		str.erase(str.begin() + i, str.end());

		return str;
	}

	static string remove1(string str)
	{
		stack<char> st;
		for (auto ch : str) {
			if (ch == 'b') continue;
			if (!st.empty() && st.top() == 'a' && ch == 'c') st.pop();
			else st.push(ch);
		}
		string res;
		while (!st.empty()) { res.push_back(st.top()); st.pop(); }
		reverse(res.begin(), res.end());

		return res;
	}
};