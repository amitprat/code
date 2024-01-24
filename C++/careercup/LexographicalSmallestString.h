#pragma once
#include "../Header.h"

class LexographicalSmallestString
{
public:
	static void test()
	{
		{
			string str = "cbacdcbc";
			auto res = smallest(str);
			cout << format("Lexographical smallest string for {} is {}", str, res) << endl;
		}

		{
			string str = "cbacadfadsdfsdfdcbsfasfacadfafd";
			auto res = smallest(str);
			cout << format("Lexographical smallest string for {} is {}", str, res) << endl;
		}
	}

	static string smallest(string str)
	{
		int n = str.length();
		vector<int> lastIndex(26, -1); // <character to last index of it in string> mapping
		vector<int> next(n); // <character to next index of it in string> mapping
		for (int i = n - 1; i >= 0; i--) {
			int cur = str[i] - 'a';
			next[i] = lastIndex[cur]; // next index for this character at this position
			lastIndex[cur] = i; // last index for this character at this position
		}

		string res;
		vector<bool> visited(26, false);
		for (int i = 0; i < n; i++) {
			int idx = str[i] - 'a';
			if (visited[idx]) continue; // if this character already included in result, exclude it

			if (next[idx] == -1) { // if this is last index for this character, include it and mark it as visited.
				res += str[i];
				visited[idx] = true;
			}
			else {
				// otherwise, look for next smallest character right to it until end or this character is only character. Include the smallest character.
				char smallest = str[i];
				int j = i + 1;
				while (j < n) {
					if (visited[idx]) continue;

					if (str[j] < smallest) smallest = str[j];
					if (next[j] == -1) break; // this is last index for this character so break here, we must include this
					j++;
				}

				if (str[i] <= smallest) {
					res += str[i];
					visited[idx] = true;
				}
			}
		}

		return res;
	}
};