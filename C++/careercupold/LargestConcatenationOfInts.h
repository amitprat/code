#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=7781671
Given an integer array, sort the integer array such that the concatenated integer of the result array is max. e.g. [4, 94, 9, 14, 1] will be sorted to
[9,94,4,14,1] where the result integer is 9944141

Psuedo Algorithm:
quick sort the input BUT
  while comparing two inputs A and B
  instead of doing the regular A > B, DO THIS
	  if(ToInt('AB') > ToInt('BA')) return 1
			 else -1;
*/

class LargestConcatenationOfInts
{
public:
	static void test() {
		vector<int> arr = { 4, 94, 9, 14, 1 };
		sort(arr.begin(), arr.end(), [](const auto& f, const auto& s) {
			return stoi(to_string(f) + to_string(s)) > stoi(to_string(s) + to_string(f));
			});

		cout << to_string(arr) << endl;
	}
};