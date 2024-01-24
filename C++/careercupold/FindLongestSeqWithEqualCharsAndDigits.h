#pragma once
#include "../Header.h"

class FindLongestSeq {
public:
	static void test() {
		FindLongestSeq obj;
		vector<string> a = { "a1b2","a","1","a1","a11","a11b","ab123c","213sdvS23vSvs123cscsCR1412323t1214rcR1241" };
		for (auto s : a) {
			cout << "Longest seq in " << s << " = " << obj.findLongestSeq(s) << endl;
		}
	}

	string findLongestSeq(string str) {
		vector<int> delta = findDeltas(str);
		unordered_map<int, int> map;
		pair<int, int> mx = { -1,-1 };
		map.insert({ 0,-1 });

		int len = 0;
		for (int i = 0; i < delta.size(); i++) {
			if (map.find(delta[i]) == map.end()) {
				map[delta[i]] = i;
			}
			else {
				auto start = map[delta[i]];
				auto end = i;
				if (end - start > len) {
					len = end - start;
					mx = { start, end };
				}
			}
		}
		if (mx.second - mx.first == 0) return "";
		return str.substr(mx.first + 1, mx.second - mx.first);
	}

	vector<int> findDeltas(string str) {
		vector<int> v(str.size());
		int delta = 0;
		int index = 0;
		for (auto ch : str) {
			if (isalpha(ch)) delta++;
			else delta--;
			v[index++] = delta;
		}
		return v;
	}
};