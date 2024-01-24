#pragma once
#include "../Header.h"

/*
Given s string, Find max size of a sub-string, in which no duplicate chars present.
*/
class MaxSizeSubstringWithRepeat {
public:
	static void test() {
		MaxSizeSubstringWithRepeat obj;
		string str = "abcabcabaabcabcabaabccfdsaewercfdsaewerabaaabcabaabccfdsaewerbccfdsaewer";
		auto res = obj.maxStr(str);

		cout << "Max string = " << res << endl;
	}

	string maxStr(string str) {
		int indices[256];
		for (int i = 0; i < 256; i++) indices[i] = -1;

		string mxStr;
		int start = 0;
		for (int cur = 0; cur < str.length(); cur++) {
			char ch = str[cur];
			if (indices[ch] >= 0) {
				int old = indices[ch];
				if (cur - start > mxStr.size()) mxStr = str.substr(start, cur - start);
				for (; start <= old; start++) indices[str[start]] = -1;
			}
			indices[ch] = cur;
		}

		return mxStr;
	}
};

/*
public static String longestSubstringUnrepeatedChar(String inputString) {
		String longestSoFar = "";
		String longestSubstringResult = "";
		if (inputString.isEmpty()) {
			return "";
		}
		if (inputString.length() == 1) {
			return inputString;
		}
		Map<Character, Integer> map = new HashMap<Character, Integer>();
		for (int i = 0; i < inputString.length(); i++) {
			char currentCharacter = inputString.charAt(i);
			if (longestSoFar.indexOf(currentCharacter) == -1) {
				if (!map.containsKey(currentCharacter)) {
					map.put(currentCharacter, i);
				}
				longestSoFar = longestSoFar + currentCharacter;
			} else {
				longestSoFar = inputString.substring(map.get(currentCharacter) + 1, i + 1);
				map.put(currentCharacter, i);
			}
			if (longestSoFar.length() > longestSubstringResult.length()) {
				longestSubstringResult = longestSoFar;
			}
		}
		return longestSubstringResult;
	}
*/