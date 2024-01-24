#pragma once
#include "../Header.h"

/*
https://www.geeksforgeeks.org/painters-partition-problem-set-2/

We have to paint n boards of length {A1, A2, .. An}. There are k painters available and each takes 1 unit time to paint 1 unit of
board. The problem is to find the minimum time to get this job done under the constraints that any painter will only paint continuous
sections of boards, say board {2, 3, 4} or only board {1} or nothing but not board {2, 4, 5}.


Input : k = 2, A = {10, 10, 10, 10}
Output : 20.
Here we can divide the boards into 2
equal sized partitions, so each painter
gets 20 units of board and the total
time taken is 20.

Input : k = 2, A = {10, 20, 30, 40}
Output : 60.
Here we can divide first 3 boards for
one painter and the last board for
second painter.
*/

class PainterPartitionProblem {
public:
	static void test() {
		PainterPartitionProblem obj;

		{
			int k = 3;
			vector<int> arr = { 10, 20, 60, 50, 30, 40 };
			int res = obj.partitionDP(arr, k);
			int res1 = obj.partition(arr, 0, arr.size() - 1, k);

			assert(res == res1);

			cout << format("Minimum time taken to paint the board={} using k={} workers is time={}", to_string(arr), k, res) << endl;
		}

		{
			int k = 2;
			vector<int> arr = { 10, 10, 10, 10 };
			int res = obj.partitionDP(arr, k);
			int res1 = obj.partition(arr, 0, arr.size() - 1, k);

			assert(res == res1);
			cout << format("Minimum time taken to paint the board={} using k={} workers is time={}", to_string(arr), k, res) << endl;
		}

		{
			int k = 3;
			vector<int> arr = { 10, 20, 30, 40 };
			int res = obj.partitionDP(arr, k);
			int res1 = obj.partition(arr, 0, arr.size() - 1, k);

			assert(res == res1);
			cout << format("Minimum time taken to paint the board={} using k={} workers is time={}", to_string(arr), k, res) << endl;
		}
	}

	int partition(vector<int>& arr, int l, int r, int k)
	{
		if (k == 1) return accumulate(arr.begin() + l, arr.begin() + r + 1, 0);
		if (l == r) return arr[l];

		int result = INT_MAX;
		for (int i = l; i <= r; i++) {
			int cur = max(partition(arr, l, i, k - 1), accumulate(arr.begin() + i + 1, arr.begin() + r + 1, 0));
			result = min(result, cur);
		}

		return result;
	}

	int partitionDP(vector<int>& arr, int k)
	{
		int n = arr.size();
		vector<vector<int>> table(k + 1, vector<int>(n + 1, 0));

		// for k=1
		for (int j = 1; j <= n; j++) table[1][j] = accumulate(arr.begin(), arr.begin() + j, 0);

		// for n=1
		for (int i = 1; i <= k; i++) table[i][1] = arr[0];

		for (int i = 2; i <= k; i++) {
			for (int j = 2; j <= n; j++) {
				int best = INT_MAX;
				for (int p = 1; p <= j; p++) {
					int cur = max(table[i - 1][p], accumulate(arr.begin() + p, arr.begin() + j, 0));
					best = min(best, cur);
				}
				table[i][j] = best;
			}
		}

		return table[k][n];
	}
};