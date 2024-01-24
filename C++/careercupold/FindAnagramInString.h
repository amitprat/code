#pragma once
#include "../Header.h"

/*
* Given two strings a and b, find whether any anagram of string a is a sub-string of string b. For eg:
if a = xyz and b = afdgzyxksldfm then the program should return true.
*/
class FindAnagram {
public:
	static void test() {
		FindAnagram obj;
		{
			string a = "xyz";
			string b = "afdgzyxksldfm";
			cout << "Does exist? " << obj.exits(a, b) << endl;
		}

		{
			string a = "xyzm";
			string b = "afdgzyxksldfm";
			cout << "Does exist? " << obj.exits(a, b) << endl;
		}
	}

	bool exits(string a, string b) {
		if (a.size() > b.size()) return false;
		int freqMapA[256] = { 0 };
		int freqMapB[256] = { 0 };
		for (int i = 0; i < a.size(); i++) {
			freqMapA[a[i]]++;
		}

		int curCount = 0;
		int start = 0;
		bool found = false;
		for (int j = 0; j < b.size(); j++) {
			char ch = b[j];
			freqMapB[ch]++;
			if (freqMapB[ch] <= freqMapA[ch]) curCount++;

			if (curCount == a.size()) {
				cout << "Found at index {" << (j - a.size() + 1) << "," << j << "}" << endl;
				found = true;
			}

			if (j >= a.size() - 1) {
				if (freqMapB[b[j - a.size() + 1]] <= freqMapA[b[j - a.size() + 1]]) curCount--;
				freqMapB[b[j - a.size() + 1]]--;
			}
		}

		return found;
	}
};


/*
bool hasAnagramSubstring(const string& src, const string& target)
{
	if(target.size() > src.size()) return false;

	int srcLen = src.size(), targetLen = target.size();
	int targetCount[128] = {0}, count[128] = {0}, i, j;
	//initialize
	for(i = 0; i < target.size(); ++i){
		++targetCount[target[i]];
		++count[src[i]];
	}
	//loop
	i = 0;
	while(true){
		//check if substring is an anagram
		for(j = 0; j < targetLen; ++j){
			if(count[target[j]] != targetCount[target[j]]) break;
		}
		if(j == targetLen) return true;
		//slide window
		if(i + 1 + targetLen > srcLen) break;
		--count[src[i]];
		++count[src[i + targetLen]];
		++i;
	}

	return false;
}
*/