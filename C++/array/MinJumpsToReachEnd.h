#pragma once
#include "../header.h"
using namespace std;

/*
https://www.careercup.com/question?id=24669663

given an input array of integers where each integer represent the maximum amount of jump a frog can take.Frog has to reach the end of the array in minimum number of jumps.
Example:[1 5 4 6 9 3 0 0 1 3] answer is 3 for this.
[2 8 3 6 9 3 0 0 1 3] answer is 2 for this.
Any DP solution for this?
*/

class MinJumpsToReachEnd {
public:
	static void test() {
		MinJumpsToReachEnd obj;
		vector<int> nums = { 2,3,2,1,4 };

		auto res1 = obj.minJumpsRec(nums);
		auto res2 = obj.minJumpsDP(nums);
		auto res3 = obj.minJumpsDP2(nums);
		auto res4 = obj.minJumpsGreedy(nums);
		auto res5 = obj.minJumpsRecUsingMemo(nums);

		assert(res1 == res2);
		assert(res1 == res3);
		assert(res1 == res4);
		assert(res1 == res5);

		cout << format("Minimum jumps to reach end of array, arr={}, jumps={}", to_string(nums), res1) << endl;
	}

	int minJumpsRec(vector<int> arr) {
		return minJumpsRec(arr, 0, arr.size());
	}

	int minJumpsRec(vector<int> arr, int index, int n) {
		if (index >= n - 1) return 0; // means, we can reach end so return 0

		// minimize number of jumps to reach end from current index
		int jumps = INT_MAX;
		for (int i = 1; i <= arr[index]; i++) {
			int cur = minJumpsRec(arr, index + i, n);
			jumps = min(jumps, 1 + cur);
		}

		return jumps;
	}

	int minJumpsDP(vector<int> arr) {
		int n = arr.size();
		vector<int> memo(n, INT_MAX);
		memo[0] = 0;

		// minimize jumps from each position to all reachable positions.
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j <= i + arr[i] && j < n; j++) {
				if (memo[i] != INT_MAX && 1 + memo[i] < memo[j])
					memo[j] = 1 + memo[i];
			}
		}

		return memo[n - 1] == INT_MAX ? -1 : memo[n - 1];
	}

	int minJumpsDP2(vector<int> arr) {
		int n = arr.size();
		vector<int> memo(n);
		memo[0] = 0;

		// minimize to jumps to reach pos 'i' from all previous elements
		for (int i = 1; i < n; i++) {
			memo[i] = INT_MAX;
			for (int j = 0; j < i; j++) {
				if (i <= j + arr[j] && memo[j] != INT_MAX) {
					memo[i] = min(memo[i], 1 + memo[j]);
				}
			}
		}

		return memo[n - 1] == INT_MAX ? -1 : memo[n - 1];
	}

	int minJumpsGreedy(vector<int>& nums) {
		int jumps = 0, curEnd = 0, curFarthest = 0;

		for (int i = 0; i < nums.size() - 1; i++) {
			curFarthest = max(curFarthest, i + nums[i]);
			if (curEnd == i) {
				jumps++;
				curEnd = curFarthest;
			}
		}

		return curEnd >= nums.size() - 1 ? jumps : -1;
	}

	int minJumpsRecUsingMemo(vector<int>& nums) {
		vector<int> memo(nums.size(), INT_MAX);

		minJumpsRecUsingMemo(nums, 0, memo);

		return memo[0];
	}

	int minJumpsRecUsingMemo(vector<int>& nums, int index, vector<int>& memo) {
		if (index >= nums.size()) return INT_MAX;
		if (index == nums.size() - 1) return 0;

		if (memo[index] != INT_MAX) return memo[index];
		for (int i = 1; i <= nums[index]; i++) {
			int tmp = 1 + minJumpsRecUsingMemo(nums, index + i, memo);
			memo[index] = min(memo[index], tmp);
		}

		return memo[index];
	}
};