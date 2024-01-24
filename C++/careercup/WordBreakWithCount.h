#pragma once
#include "../Header.h"

class WordBreakWithCount
{
public:
	static void test() {
		unordered_map<string, int> words;
		words.insert({ "abc",3 });
		words.insert({ "ab",2 });
		words.insert({ "abca",1 });

		string input = "abcababab";
		bool res = canWordBreakRec(words, input);
		cout << "Can break? " << res << endl;
	}

	static bool canWordBreakRec(unordered_map<string, int> dictionary, string input)
	{
		if (input.empty()) return true;
		int n = input.size();

		bool* table = new bool[n + 1];
		memset(table, false, sizeof(bool) * (n + 1));
		table[0] = true;

		return canWordBreak(dictionary, input, table, n);
	}

	static bool canWordBreak(unordered_map<string, int> dictionary, string input, bool* table, int n)
	{
		if (input.empty()) return true;

		for (int i = 1; i <= n; i++) {
			string cur = input.substr(0, i);
			if (dictionary[cur] > 0) {
				dictionary[cur]--;
				if (canWordBreak(dictionary, input.substr(i), table, n)) return true;
				dictionary[cur]++;
			}
		}

		return false;
	}

	static bool canWordBreak(unordered_map<string, int> dictionary, string input) {
		int n = input.size();
		bool* table = new bool[n + 1];
		memset(table, false, (n + 1) * sizeof(bool));
		table[0] = true;

		for (int i = 1; i <= n; i++) {
			string cur = input.substr(0, i);
			if (dictionary[cur] > 0) {
				dictionary[cur]--;
				table[i] = true;
			}
			if (!table[i]) continue;

			for (int j = i + 1; j <= n; j++) {
				string cur = input.substr(i, j - i);
				if (dictionary[cur] > 0) {
					dictionary[cur]--;
					table[j] = true;
				}
			}
			if (table[n]) return true;
		}
		cout << "Debug Info: " << endl;
		for (int i = 0; i <= n; i++) cout << table[i] << " ";
		cout << endl;
		return false;
	}
};