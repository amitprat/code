#pragma once
#include "../header.h"
using namespace std;

class FindInsertPositionInSortedArray {
public:
	static void test() {
		FindInsertPositionInSortedArray obj;
		vector<pair<vector<int>, int>> tests = {
			{{},5},
			{{1},1},
			{{1},0},
			{{1},2},
			{{1,3,5,6}, 5},
			{{1,3,5,6}, 2},
			{{1,3,5,6}, 7},
			{{1,3,5,6}, 0},
			{{3,3,3,3}, 3}
		};
		for (auto& test : tests) {
			cout << "Insert Position: " << obj.findInsertPosition2(test.first, test.second) << endl;
			cout << "Insert Position: " << obj.findInsertPosition3(test.first, test.second) << endl;
			cout << endl << endl;
		}
	}

	// first the index of last element which is less than or equal to target
	// if we find such position then insert at +1 position otherwise at current position
	int findInsertPosition(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int m = (l + r + 1) / 2;
			if (target <= nums[m]) r = m - 1;
			else l = m;
		}
		return nums[l] < target ? l + 1 : l;
	}

	// look for first greater element
	// if there is none, then we need to insert at +1 position
	int findInsertPosition2(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		if (r == -1) return l;

		while (l < r) {
			int m = (l + r) / 2;
			if (target >= nums[m]) l = m + 1;
			else r = m;
		}
		return nums[l] > target ? l : l + 1;
	}

	int findInsertPosition3(vector<int>& arr, int e) {
		int l = 0, r = arr.size() - 1;
		if (r == -1) return l;

		while (l < r) {
			int m = (l + r) / 2;
			if (e >= arr[m]) l = m + 1;
			else r = m;
		}

		return arr[l] <= e ? (l + 1) : l;
	}
};