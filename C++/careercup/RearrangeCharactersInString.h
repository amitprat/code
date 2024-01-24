#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5693863291256832

Rearrange characters in a string so that no character repeats twice.

Input: aaabc
Output: abaca

Input: aa
Output: No valid output

Input: aaaabc
Output: No valid output
*/
class RearrangeCharactersInString
{
public:
	static void test() {
		vector<string> inputs = { "aaabc","aa","aaaabc","bdaaa" };

		for (auto& input : inputs) {
			auto output = rearrangeCharacters(input);
			cout << format("Input={}, Output={}", input, output) << endl;
		}
	}

	static string rearrangeCharacters(string input)
	{
		int n = input.size();
		string output;
		unordered_map<char, int> freq;
		for (auto ch : input) freq[ch]++;

		priority_queue<pair<int, char>> pq;
		for (auto e : freq) {
			if (e.second > (n + 1) / 2) return "Invalid input";
			pq.push({ e.second,e.first });
		}

		while (!pq.empty()) {
			auto first = pq.top(); pq.pop();
			output += first.second;
			first.first--;

			if (!pq.empty()) {
				auto second = pq.top(); pq.pop();
				output += second.second;
				second.first--;
				if (second.first > 0) pq.push({ second.first, second.second });
			}

			if (first.first > 0) pq.push({ first.first, first.second });
		}

		return output;
	}
};