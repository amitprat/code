#pragma once
#include "../Header.h"

class PrintCombinations
{
public:
	static void test() {
		vector<vector<string>> sets = { {"quick", "slow"}, {"brown", "red"}, {"fox", "dog"} };
		int n = sets.size();

		printCombination(sets, 0, n, {});
	}

	static void printCombination(vector<vector<string>> sets, int index, int n, vector<string> curRes)
	{
		if (index == n) {
			cout << to_string(curRes) << endl;
			return;
		}

		for (int j = 0; j < sets[index].size(); j++) {
			curRes.push_back(sets[index][j]);
			printCombination(sets, index + 1, n, curRes);
			curRes.pop_back();
		}
	}
};