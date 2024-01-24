#pragma once
#include "../Header.h"

class Decode {
public:
	static void test() {
		Decode obj;
		string input = "1123";
		auto res = obj.decode(input);
		print("Result", res);
	}

	vector<string> decode(string input) {
		vector<string> result;
		decode(input, 0, "", result);

		return result;
	}

	void decode(string input, int pos, string prefix, vector<string>& result) {
		if (pos == input.size()) { result.push_back(prefix); return; }
		if (input[pos] == '0') return;

		decode(input, pos + 1, prefix + trans(input.substr(pos, 1)), result);
		if (pos < input.size() - 1 && (input[pos] == '1' || (input[pos] == '2' && input[pos + 1] <= '6'))) {
			decode(input, pos + 2, prefix + trans(input.substr(pos, 2)), result);
		}
	}

	string trans(string in) {
		int val = stoi(in);
		char ch = 'a' + val - 1;
		return string(1, ch);
	}
};