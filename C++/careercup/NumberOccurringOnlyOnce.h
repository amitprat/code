#pragma once
#include "../Header.h"

class NumberOccurringOnlyOnce {
public:
	static void test() {
		cout << "Find the number which occurs only once and all the other number occurs exactly 3 times" << endl;
		{
			int arr[] = { 2,1,4,5,1,4,2,2,4,1 };
			int n = sizeof(arr) / sizeof(int);

			int res = numberOccurringOnlyOnceUsingMod3(arr, n);
			int res1 = numberOccurringOnlyOnceUsingBitwiseOper(arr, n);
			int res2 = numberOccurringOnlyOnceUsingBitwiseAddMod3(arr, n);

			assert(res == res1);
			assert(res == res2);

			cout << format("Number occursing only once in {} is {}", to_string(arr, n), res) << endl;
		}

		{
			int arr[] = { 1,2,3,1,3,3,1 };
			int n = sizeof(arr) / sizeof(int);

			int res = numberOccurringOnlyOnceUsingMod3(arr, n);
			int res1 = numberOccurringOnlyOnceUsingBitwiseOper(arr, n);
			int res2 = numberOccurringOnlyOnceUsingBitwiseAddMod3(arr, n);

			assert(res == res1);
			assert(res == res2);

			cout << format("Number occursing only once in {} is {}", to_string(arr, n), res) << endl;
		}

		{
			int arr[] = { 1,1,1,2,2,2,3 };
			int n = sizeof(arr) / sizeof(int);

			int res = numberOccurringOnlyOnceUsingMod3(arr, n);
			int res1 = numberOccurringOnlyOnceUsingBitwiseOper(arr, n);
			int res2 = numberOccurringOnlyOnceUsingBitwiseAddMod3(arr, n);

			assert(res == res1);
			assert(res == res2);

			cout << format("Number occursing only once in {} is {}", to_string(arr, n), res) << endl;
		}

		{
			int arr[] = { 7,1,2,3,2,3,2,1,1,4,3,7,7 };
			int n = sizeof(arr) / sizeof(int);

			int res = numberOccurringOnlyOnceUsingMod3(arr, n);
			int res1 = numberOccurringOnlyOnceUsingBitwiseOper(arr, n);
			int res2 = numberOccurringOnlyOnceUsingBitwiseAddMod3(arr, n);

			assert(res == res1);
			assert(res == res2);

			cout << format("Number occursing only once in {} is {}", to_string(arr, n), res) << endl;
		}
	}

	static int numberOccurringOnlyOnceUsingMod3(int arr[], int n) {
		vector<int> mod3Res;
		for (int i = 0; i < n; i++) {
			vector<int> mod3Val = toMod3(arr[i]);
			mod3Res = addMod3(mod3Res, mod3Val);
		}
		std::reverse(mod3Res.begin(), mod3Res.end());
		int mod10Res = toMod10(mod3Res);

		return mod10Res;
	}

	static vector<int> addMod3(vector<int> num1, vector<int> num2) {
		int i = 0, j = 0;
		vector<int> result;
		while (i < num1.size() || j < num2.size()) {
			if (i == num1.size()) {
				result.push_back(num2[j++] % 3);
			}
			else if (j == num2.size()) {
				result.push_back(num1[i++] % 3);
			}
			else {
				result.push_back((num1[i++] + num2[j++]) % 3);
			}
		}

		return result;
	}

	static int toMod10(vector<int> num) {
		int result = 0;
		for (auto i : num) {
			result = result * 3 + i;
		}
		return result;
	}

	static vector<int> toMod3(int num) {
		vector<int> result;
		while (num) {
			result.push_back(num % 3);
			num /= 3;
		}
		return result;
	}

	static int numberOccurringOnlyOnceUsingBitwiseAddMod3(int arr[], int n)
	{
		int bitsize = 0;
		for (int i = 0; i < n; i++) {
			bitsize = max(bitsize, (int)log2(arr[i]) + 1);
		}
		auto res = addBitwiseMod3(arr, n, bitsize);

		return res;
	}

	static int addBitwiseMod3(int arr[], int n, int bitsize) {
		if (bitsize == 0) return 0;
		int cur = addBitwiseMod3(arr, n, bitsize - 1);

		int s = 0;
		for (int j = 0; j < n; j++) {
			int v = (arr[j] >> bitsize - 1) & 1;
			s = (s + v) % 3;
		}
		cur = s * pow(2, bitsize - 1) + cur;

		return cur;
	}

	static int numberOccurringOnlyOnceUsingBitwiseOper(int arr[], int n)
	{
		int ones = 0;
		int twos = 0;
		for (int i = 0; i < n; i++)
		{
			int x = arr[i];
			twos |= ones & x;
			ones ^= x;
			int not_threes = ~(ones & twos);
			ones &= not_threes;
			twos &= not_threes;
		}

		return ones;
	}
};