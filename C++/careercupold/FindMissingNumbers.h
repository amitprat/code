#pragma once
#include "../Header.h"

class FindMissingNumbers
{
public:
	static void test() {
		{
			vector<int> nums = { 1,4,6,7,8,20,50,99 };
			printMissingNumbers(nums);
		}
	}

	static void printMissingNumbers(vector<int> nums) {
		vector<int> range = { 0,99 };

		for (auto num : nums) {
			auto start = range[0];
			auto end = num - 1;

			if (start <= end) {
				cout << start;
				if (start != end) {
					cout << ", " << end;
				}
				cout << endl;
			}

			range[0] = num + 1;
		}

		if (range[0] <= range[1]) {
			cout << range[0];
			if (range[0] != range[1]) {
				cout << ", " << range[1];
			}
			cout << endl;
		}
	}
};