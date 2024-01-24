#pragma once
#include "../Header.h"
#include "Trie.h"

class LongestWordMadeOfOthers {
public:
	static void test() {
		LongestWordMadeOfOthers obj;
		{
			vector<string> words = { "geeks", "for", "geeksfor", "geeksforgeeks" };
			cout << "Longest Word = " << obj.longestWordMadeFromOthers(words) << endl;
		}

		{
			vector<string> words = { "Hey", "you", "stop", "right", "there" };
			cout << "Longest Word = " << obj.longestWordMadeFromOthers(words) << endl;
		}

		{
			vector<string> words = { "Hey", "you", "stop", "right", "there", "Heytherehowareyou", "Heythere", "Heyyouthere" };
			cout << "Longest Word = " << obj.longestWordMadeFromOthers(words) << endl;
		}

		{
			vector<string> words = { "cat", "hat", "mat", "catmat","bat","batmatcat","catratmatbat","catmatcatmat","catmatratmapcatmat","map" };
			cout << "Longest Word = " << obj.longestWordMadeFromOthers(words) << endl;
		}

		{
			vector<string> words = { "cat", "hat", "mat", "catmat","bat","batmatcat","catratmatbat","rat","catmatcatmat","catmatratmapcatmat","map" };
			cout << "Longest Word = " << obj.longestWordMadeFromOthers(words) << endl;
		}
	}

	string longestWordMadeFromOthers(vector<string> words) {
		auto res1 = longestWordMadeFromOthersWithoutMemoization(words);
		auto res2 = longestWordMadeFromOthersWithMemoization(words);
		auto res3 = longestWordMadeFromOthersWithTrie(words);

		assert(res1 == res2);
		assert(res1 == res3);

		return res1;
	}

	string longestWordMadeFromOthersWithoutMemoization(vector<string> words) {
		unordered_set<string> dict;
		for (auto word : words) dict.insert(word);

		sort(words.begin(), words.end(), [](const auto& f, const auto& s) {return f.size() > s.size(); });

		for (auto word : words) {
			dict.erase(word);
			if (canBuildFromOtherWordsWithoutMemoization(word, dict)) return word;
			dict.insert(word);
		}

		return "";
	}

	bool canBuildFromOtherWordsWithoutMemoization(string word, unordered_set<string> dict) {
		if (dict.find(word) != dict.end()) return true;
		for (int i = 1; i <= word.length(); i++) {
			string left = word.substr(0, i);
			if (dict.find(left) != dict.end() && canBuildFromOtherWordsWithoutMemoization(word.substr(i), dict)) {
				return true;
			}
		}
		return false;
	}

	string longestWordMadeFromOthersWithMemoization(vector<string> words) {
		unordered_set<string> dict;
		for (auto word : words) dict.insert(word);

		sort(words.begin(), words.end(), [](const auto& f, const auto& s) {return f.size() > s.size(); });

		for (auto word : words) {
			dict.erase(word);
			if (canBuildFromOtherWordsWithMemoization(word, dict)) return word;
			dict.insert(word);
		}

		return "";
	}

	bool canBuildFromOtherWordsWithMemoization(string word, unordered_set<string>& dict) {
		if (dict.find(word) != dict.end()) return true;

		for (int i = 1; i <= word.length(); i++) {
			string left = word.substr(0, i);
			if (dict.find(left) != dict.end() && canBuildFromOtherWordsWithMemoization(word.substr(i), dict)) {
				dict.insert(word.substr(i));
				return true;
			}
		}

		return false;
	}

	string longestWordMadeFromOthersWithTrie(vector<string> words) {
		Trie trie;

		for (auto word : words) {
			trie.insert(word);
		}

		sort(words.begin(), words.end(), [](auto f, auto s) {return f.length() > s.length(); });

		for (auto word : words) {
			trie.remove(word);

			if (exists(trie, word)) return word;

			trie.insert(word);
		}

		return "";
	}

	bool exists(Trie& trie, string word) {
		if (word.empty()) return true;
		for (int i = 1; i <= word.length(); i++) {
			auto left = word.substr(0, i);
			auto right = word.substr(i);

			if (trie.contains(left) && exists(trie, right)) return true;
		}

		return false;
	}
};