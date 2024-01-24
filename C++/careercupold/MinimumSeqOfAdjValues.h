#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5653018213089280

Determine minimum sequence of adjacent values in the input parameter array that is greater than input parameter sum.

Eg
Array 2,1,1,4,3,6. and Sum is 8
Answer is 2, because 3,6 is minimum sequence greater than 8.
*/
class MinimumSeqOfAdjValues
{
public:
	static void test()
	{
		MinimumSeqOfAdjValues obj;
		vector<int> arr = { 2,1,1,4,3,6 };

		{
			for (int sum = 1; sum <= 20; sum++) {
				auto res = obj.getMinSeq(arr, sum);
				auto res1 = obj.getMinSeq(arr, sum);

				assert(res.size() == res1.size());
				cout << format("Minimum length subsequence in {} with sum > {} is {}", to_string(arr), sum, to_string(res1)) << endl;
			}
		}
	}

	vector<int> getMinSeq(vector<int> arr, int sum)
	{
		int curSum = 0;
		int s = 0;
		int minLen = INT_MAX;
		pair<int, int> indices = { 0,-1 };
		vector<int> res;
		for (int e = 0; e < arr.size(); e++)
		{
			curSum += arr[e];
			if (curSum > sum) {
				while (s <= e && curSum - arr[s] > sum) {
					curSum -= arr[s++];
				}
				if (e - s + 1 < minLen)
				{
					minLen = e - s + 1;
					indices = { s, e };
				}
				curSum -= arr[s++];
			}
		}

		for (int i = indices.first; i <= indices.second; i++) res.push_back(arr[i]);
		return res;
	}

	vector<int> getMinSeq1(vector<int> arr, int sum)
	{
		int s = 0, e = 0, curSum = 0;
		int n = arr.size();
		pair<int, int> p = { 0,-1 };
		while (s <= e && e <= n) {
			if (curSum < sum) curSum += arr[e++];
			else curSum -= arr[s++];

			if (curSum > sum) {
				p = { s, e };
			}

			if (e >= n && curSum <= 0) break;
		}

		vector<int> res;
		for (auto i = p.first; i <= p.second; i++) res.push_back(arr[i]);

		return res;
	}
};