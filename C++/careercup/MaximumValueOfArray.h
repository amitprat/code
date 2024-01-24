#pragma once
#include "../Header.h"

/*
Your input is a double array, and you can use *, +, -, and () parenthesis anywhere to create and output the maximum possible value.

Ex:
input is {3,4,5,1} --> output: 72
input is {1,1,1,5} --> output: 15

Follow up, if there are numbers <0
*/
class MaxValueOfArray {
public:
	static void test() {
		MaxValueOfArray obj;

		{
			vector<int> arr = { 3,4,5,1 };
			cout << format("Maximum value of array {} is {}", to_string(arr), obj.maxValue(arr)) << endl;
		}

		{
			vector<int> arr = { 1,1,1,5 };
			cout << format("Maximum value of array {} is {}", to_string(arr), obj.maxValue(arr)) << endl;
		}
	}

	double maxValue(vector<int> arr) {
		vector<vector<double>> memo(arr.size(), vector<double>(arr.size(), INT_MIN));
		return maxValue(arr, 0, arr.size() - 1, memo);
	}

	double maxValue(vector<int> arr, int s, int e, vector<vector<double>>& memo) {
		if (memo[s][e] != INT_MIN) return memo[s][e];
		if (s == e) return arr[s];

		double mx = INT_MIN;
		for (int k = s; k < e; k++) {
			double left = maxValue(arr, s, k, memo);
			double right = maxValue(arr, k + 1, e, memo);
			for (auto ch : { '+','-','*' }) {
				double res = apply(left, right, ch);
				mx = max(mx, res);
			}
		}
		memo[s][e] = mx;
		return mx;
	}

private:
	double apply(double left, double right, char ch) {
		switch (ch) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		}
		return 0;
	}
};

/*
My solution N^3 top down dynamic programming approach but I believe there is an O(n) algorithm that solves it.

public static long max(int[] nums) {
	Long[][] memo = new Long[nums.length][nums.length];
	return max(nums, 0, nums.length - 1, memo);
}

public static long max(int[] nums, int i, int j, Long[][] memo) {
	if (memo[i][j] != null) return memo[i][j];
	if (i == j) {
		return nums[i];
	}

	long max = Integer.MIN_VALUE;
	for (int k = i; k < j; k++) {
		long left = max(nums, i, k, memo);
		long right = max(nums, k + 1, j, memo);

		for (char c : "*-+".toCharArray()) {
			long res = apply(c, left, right);
			max = Math.max(max, res);
		}
	}
	memo[i][j] = max;

	return max;
}
*/