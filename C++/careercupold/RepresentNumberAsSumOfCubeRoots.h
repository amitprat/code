#pragma once
#include "../Header.h"

// https://www.careercup.com/question?id=5647694703886336
/*
Write a function that would print all positive numbers smaller than n that can be expressed as the sum of two cubes in two different ways. Bonus: calculate the complexity of that function.

For example, 1729 is one such number because 1729 = 1^3 + 12^3 = 9^3 + 10^3.
*/
class RepresentNumberAsSumOfCubeRoots
{
public:
	static void test()
	{
		RepresentNumberAsSumOfCubeRoots obj;

		vector<int> nums = { 1729, 1944, 9, 3528 };

		for (auto num : nums) {
			cout << format("Print all combinations of cuberoot to make the target number = {}", num) << endl;
			obj.calculateAllCubeRootSum(num);
			cout << endl;

			cout << "Cuberoot pair sum" << endl;
			auto res = obj.calculateCubePairSum(num);
			for (auto e : res)
				cout << format("[{}^3 + {}^3] = {}", e.first, e.second, num) << endl;
			cout << endl;
		}

		int n = 2000;
		cout << format("print all positive numbers smaller than n={} that can be expressed as the sum of two cubes", n) << endl;
		obj.printAllPositiveNumbersSmallestThanNExpressedAsPairSum(n);
	}
private:
	void printAllPositiveNumbersSmallestThanNExpressedAsPairSum(int n) {
		for (int i = 1; i < n; i++) {
			auto res = calculateCubePairSum(i);
			if (res.empty()) continue;

			for (auto e : res)
				cout << format("[{}^3 + {}^3] = {}", e.first, e.second, i) << endl;
		}
	}

	vector<pair<int, int>> calculateCubePairSum(int n) {
		int cuberoot = cbrt(n);
		int* a = new int[cuberoot+1];

		// construct array
		for (int i = 0; i <= cuberoot; i++) {
			a[i] = (i + 1) * (i + 1) * (i + 1);
		}

		vector<pair<int, int>> result;
		int fwd = 0;
		int bck = cuberoot;
		while (fwd < bck) {
			if (a[fwd] + a[bck] < n)
				fwd++;
			else if (a[fwd] + a[bck] > n)
				bck--;
			else {
				result.push_back({ cbrt(a[fwd]), cbrt(a[bck]) });
				fwd++;
				bck--;
			}
		}

		return result;
	}

	void calculateAllCubeRootSum(int n)
	{
		int m = cbrt(n);
		vector<int> cubeRoots;
		for (int i = 0; i <= m; i++) cubeRoots.push_back(pow(i, 3));

		vector<string> result;
		calculateAllCubeRootSum(cubeRoots, m, n, result);
	}

	void calculateAllCubeRootSum(vector<int> cubeRoots, int index, int total, vector<string> result)
	{
		if (total == 0) {
			cout << to_string(result) << endl;
			return;
		}
		if (total < 0 || index < 0) return;

		calculateAllCubeRootSum(cubeRoots, index - 1, total, result);
		result.push_back(to_string((int)cbrt(cubeRoots[index])) + "^3");
		calculateAllCubeRootSum(cubeRoots, index - 1, total - cubeRoots[index], result);
		result.pop_back();
	}
};
