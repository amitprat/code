#pragma once
#include "../Header.h"

/*
An array consist of elements whose difference is positive or negative 1. I have to find the given elements without using linear search.
Say
Int arr[]={1,2,3,4,3,4,5,6,7

To find : 6
*/

/*
The answer is skipping. If you're starting at 1, and you're looking for 6, then you know that the best case scenario is the next five values
increase by one each. So you skip 5 and check that value. You repeat the same step. It turns out the value at that position is 4.
The best case scenario is the next two values increase by one each. So you jump two positions and there's your number.

The key is to figure out at each position how far the goal value is from that position's value and jump ahead by as many steps.
*/

class FindElementInArray {
public:
	static void test() {
		vector<int> arr = { 1,2,3,4,3,4,5,6,7 };

		searchElement(arr, 4);
		searchElement(arr, 5);
		searchElement(arr, 6);
		searchElement(arr, 7);

		for (int i = 0; i < 10; i++) {
			cout << format("Element={} found at index={}", i, searchElement2(arr, i)) << endl;
		}
	}

	static void searchElement(vector<int>& arr, int x)
	{
		int s = arr[0];
		int l = x - s;
		int r = arr.size() - 1;
		while (l <= r) {
			if (arr[l] == x) {
				cout << x << " found at index " << l << endl;
				return;
			}
			else {
				l += (x - arr[l]);
			}
		}

		cout << "Element not found!" << endl;
	}

	static int searchElement2(vector<int>& arr, int x) {
		int l = 0, n = arr.size();
		while (l >= 0 && l < n) {
			if (arr[l] == x) return l;
			l += (x - arr[l]);
		}

		return -1;
	}
};