#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5725584103571456

Given a number "n", find the least number of perfect square numbers sum needed to get "n"

Example:
n=12, return 3 (4 + 4 + 4) = (2^2 + 2^2 + 2^2) NOT (3^2 + 1 + 1 + 1)
n = 6, return 3 (4 + 1 + 1) = (2^2 + 1^2 + 1^2)
*/
class LeastNumberOfPerfectSquaresToReachN
{
public:
	static void test() {
		{
			int n = 12;
			int res = leastNumberOfPerfectSquares2(n);
			cout << format("Least of perfect squares={} to reach to {}", res, n) << endl;
		}

		{
			int n = 6;
			int res = leastNumberOfPerfectSquares2(n);
			cout << format("Least of perfect squares={} to reach to {}", res, n) << endl;
		}

		{
			int n = 12;
			auto res = leastNumberOfPerfectSquaresWithValues(n);
			cout << res.to_string() << endl;
		}

		{
			int n = 6;
			auto res = leastNumberOfPerfectSquaresWithValues(n);
			cout << res.to_string() << endl;
		}
	}

	static int leastNumberOfPerfectSquares(int n)
	{
		int* table = new int[n + 1];

		// for k = 1
		for (int i = 0; i <= n; i++) table[i] = i;

		// for k >= 2
		for (int k = 2; k * k <= n; k++)
		{
			int  p = pow(k, 2);
			for (int j = p; j <= n; j++) {
				table[j] = min(table[j], table[j - p] + 1);
			}
		}

		return table[n];
	}

	static int leastNumberOfPerfectSquares2(int n) {
		vector<int> table(n + 1);
		for (int i = 0; i <= n; i++) table[i] = i;

		for (int i = 2; i * i <= n; i++) {
			int p = pow(i, 2);
			for (int j = p; j <= n; j++) {
				table[j] = min(table[j], 1 + table[j - p]);
			}
		}

		return table[n];
	}

	struct PerfectSquare {
		int cnt = 0;
		vector<vector<int>> perfSquares;
		PerfectSquare() {}
		PerfectSquare(int cnt, int elem) : cnt(cnt) {
			perfSquares.push_back({ });
			for (int i = 0; i < cnt; i++) perfSquares.back().push_back(elem);
		}

		bool operator <=(const PerfectSquare& other)
		{
			return this->cnt <= other.cnt;
		}

		void update(int cnt, vector<vector<int>> perfSq, int newPerfSq)
		{
			this->cnt = cnt;
			for (auto old : perfSq)
			{
				old.push_back(newPerfSq);
				perfSquares.push_back(old);
			}
		}

		string to_string() {
			stringstream ss;
			ss << "Cnt: " << cnt << endl;
			for (auto e : perfSquares) {
				for (auto i : e) ss << i << " ";
				ss << endl;
			}

			ss << endl;

			return ss.str();
		}
	};

	static PerfectSquare leastNumberOfPerfectSquaresWithValues(int n)
	{
		vector<PerfectSquare> perfectSquares(n + 1);

		// for k = 1
		for (int i = 0; i <= n; i++) perfectSquares[i] = PerfectSquare(i, 1);

		// for k >= 2
		for (int k = 2; k * k <= n; k++)
		{
			int  p = pow(k, 2);
			for (int j = p; j <= n; j++) {
				if (perfectSquares[j - p].cnt + 1 < perfectSquares[j].cnt)
				{
					perfectSquares[j].update(perfectSquares[j - p].cnt + 1, perfectSquares[j - p].perfSquares, p);
				}
			}
		}

		return perfectSquares[n];
	}
};