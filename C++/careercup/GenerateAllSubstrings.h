#pragma once
#include "../Header.h"

class GenerateAllSubstrings
{
public:
	static void test()
	{
		cout << "generateAllSubstrings using recursion: ";
		string str = "abc";
		generateAllSubstrings("", str);
		cout << endl;

		cout << "generateAllSubstrings using bits: ";
		generateAllSubstrings(str);
		cout << endl;

		cout << "generateAllPermutations: ";
		generateAllPermutations(str);
		cout << endl;
	}

	static void generateAllSubstrings(string prefix, string str)
	{
		if (str.empty()) {
			if (!prefix.empty()) cout << prefix << " ";
			return;
		}

		generateAllSubstrings(prefix, str.substr(1));
		generateAllSubstrings(prefix + str[0], str.substr(1));
	}

	static void generateAllSubstrings(string str)
	{
		int n = str.length();
		int sz = pow(2, n);

		for (int i = 0; i < sz; i++) {
			string cur;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) cur += str[j];
			}
			cout << cur << " ";
		}
	}

	static void generateAllPermutations(string str, int index = 0)
	{
		if (index == str.length()) {
			cout << str << " ";
			return;
		}

		for (int i = index; i < str.length(); i++) {
			swap(str[i], str[index]);
			generateAllPermutations(str, index + 1);
			swap(str[i], str[index]);
		}
	}
};