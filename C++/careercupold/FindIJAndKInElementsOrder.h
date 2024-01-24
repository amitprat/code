#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=14960662
*
* Given a array of integers , find 3 indexes i,j,k such that, i<j<k and a[i] < a[j] < a[k]. Best possible is a O(n) algorithm.
*
* This question is answered in the Amazon questions

a[i]<a[j]<a[k] s.t i<j<k
From the original array build two arrays.
i) LMin[i] contains index of the min element seen so far from the left including a[i].
ii) RMax[i] contains index of the max element seen so far from the right including a[i].
consider the following array:
a =4,7,5,1,3,8,9,6,2
LMin=0,0,0,3,3,3,3,3,3
RMax=6,6,6,6,6,6,6,7,8


Now for i=1 to n if a[LMin[i]] < a[i] < a[RMax[i] print LMin[i],a[i],RMax[i]
Time complexity: O(n)
Space Complexity: O(n)

Good solution.
One small correction.
>>print LMin[i],a[i],RMax[i]
should be
print LMin[i],i,RMax[i]
*/
class FindIJAndKInElementsOrder
{
public:
	static void test() {
		printOrder1();
		printOrder2();
		printOrder3();
	}

	static void printOrder1()
	{
		vector<int> arr = { 4, 7, 5, 1, 3, 8, 9, 6, 2 };
		int n = arr.size();
		vector<int> left(arr.size());
		vector<int> right(arr.size());

		left[0] = arr[0];
		for (int i = 1; i < arr.size(); i++) left[i] = min(left[i - 1], arr[i]);

		right[n - 1] = arr[n - 1];
		for (int i = arr.size() - 2; i >= 0; i--) right[i] = max(right[i + 1], arr[i]);

		for (int i = 1; i < n - 1; i++) {
			if (left[i] < arr[i] && arr[i] < right[i]) {
				cout << left[i] << ", " << arr[i] << ", " << right[i] << endl;
			}
		}
		cout << endl << endl;
	}

	static void printOrder2()
	{
		vector<int> arr = { 4, 7, 5, 1, 3, 8, 9, 6, 2 };
		int n = arr.size();
		vector<int> left(arr.size());
		int rightMax = arr[n - 1];

		left[0] = arr[0];
		for (int i = 1; i < arr.size(); i++) left[i] = min(left[i - 1], arr[i]);

		for (int i = n - 2; i >= 0; i--) {
			if (left[i] < arr[i] && arr[i] < rightMax) {
				cout << left[i] << ", " << arr[i] << ", " << rightMax << endl;
			}
			rightMax = max(rightMax, arr[i]);
		}

		cout << endl << endl;
	}

	static void printOrder3()
	{
		vector<int> arr = { 4, 7, 5, 1, 3, 8, 9, 6, 2 };
		int n = arr.size();
		vector<int> left(arr.size());
		int rightMax = n - 1;

		left[0] = 0;
		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] < arr[left[i - 1]]) left[i] = i;
		}

		for (int i = n - 2; i >= 0; i--) {
			if (arr[left[i]] < arr[i] && arr[i] < arr[rightMax]) {
				cout << left[i] << ", " << i << ", " << rightMax << endl;
				cout << arr[left[i]] << ", " << arr[i] << ", " << arr[rightMax] << endl;
			}
			if (arr[i] > arr[i + 1]) rightMax = i;
		}

		cout << endl << endl;
	}
};