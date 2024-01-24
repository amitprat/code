#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5675048708866048

Print the level of friendship.

Given a person and list of his friends, print all his friends by level of association.

The text file will be like one below

A: B,C,D
D: B,E,F
E: C,F,G

If the input is A, the out put should be:

Level 1 - B,C,D
Level 2 - E,F
Level 3 - G
*/
class PrintLevelOfFriendship
{
	unordered_map<string, vector<string>> friendshipMap;
public:
	static void test() {
		PrintLevelOfFriendship obj;
		obj.preprocess();

		{
			string str = "hello how are you";
			stringstream ss(str);
			string word;
			while (ss >> word) { cout << word << endl; }
		}

		{
			string str = "hello, how, are, you";
			stringstream ss(str);
			string word;
			char delim = ',';

			while (getline(ss, word, delim)) {
				cout << word << " ";
			}
			cout << endl;
		}


		{
			auto res = obj.split("", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split("a", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split("ab", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split(", :", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split("abc::: ,", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split("::: , adssdf ::::, ", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split("a:b,c:d,e,f:::f,e", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}
		{
			auto res = obj.split("a, ::: , adssdf ::::, a:b,c:d,e,f:::f,e", { ",", " ", ":" });
			cout << to_string(res) << endl;
		}

		obj.printLevels("A");
	}

	void preprocess() {
		ifstream is("C:\\Users\\amisi\\source\\repos\\CodeProject\\CodeProject\\careercup\\friendshipfile.txt");
		string line;
		while (getline(is, line)) {
			pair<string, vector<string>> friendship = parseFriendship(line);
			for (auto v : friendship.second) friendshipMap[friendship.first].push_back(v);
		}
	}

	void printLevels(string input) {
		queue<string> q;
		unordered_set<string> visited;
		for (auto& n : friendshipMap[input]) {
			q.push(n);
			visited.insert(n);
		}

		int level = 1;
		while (!q.empty()) {
			cout << "Level " << level << ": ";
			int sz = q.size();
			while (sz--) {
				auto f = q.front(); q.pop();
				cout << f << " ";

				for (auto& n : friendshipMap[f]) {
					if (visited.find(n) == visited.end()) {
						q.push(n);
						visited.insert(n);
					}
				}
			}
			level++;
			cout << endl;
		}
	}

	static pair<string, vector<string>> parseFriendship(string line)
	{
		stringstream ss(line);
		string part1, part2;
		ss >> part1 >> part2;
		part1 = trim(part1);
		vector<string> part2Splits = split(part2, { " ","," });
		part2Splits = trim(part2Splits);

		return { part1, part2Splits };
	}

	static vector<string> trim(vector<string>& strs) {
		vector<string> result;
		for (auto& str : strs) {
			result.push_back(trim(str));
		}

		return result;
	}

	static string trim(string str) {
		int i = 0;
		while (i < str.length() && (isspace(str[i]) || str[i] == ':')) {
			str.erase(str.begin() + i); i++;
		}

		i = str.length() - 1;
		while (i >= 0 && (isspace(str[i]) || str[i] == ':')) {
			str.erase(str.begin() + i); i--;
		}

		return str;
	}

	static vector<string> split(string strs, vector<string> delims) {
		vector<string> result;
		result.push_back(strs);

		for (auto& delim : delims) {
			vector<string> newResult;
			for (auto& cur : result) {
				auto parts = splitStr(cur, delim);
				newResult.insert(newResult.end(), parts.begin(), parts.end());
			}
			result = newResult;
		}
		return result;
	}

	static vector<string> splitStr(string str, string delim) {
		auto start = 0;
		auto pos = string::npos;
		auto len = str.length();

		vector<string> result;
		do {
			pos = str.find(delim, start);
			auto end = (pos == string::npos) ? len : pos;
			if (end > start) result.push_back(str.substr(start, end - start));
			start = pos + 1;
		} while (pos != string::npos);

		return result;
	}
};