#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=23823662


Given an equation in the form 2^i * 3^j * 5^k * 7^l where i,j,k,l >=0 are integers.write a program to generate numbers from that equation in sorted order efficiently.

for example numbers from that equation will be in the order 2,3,5,6,7,8,9.....and so on..
*/
class PrintMultiplesOfUglyNumbers
{
public:
	static void test()
	{
		cout << "Ugly numbers till 0: " << endl;
		{
			auto res1 = printAllMultiples(0);
			//auto res2 = printAllMultiplesSpaceOptimized(0);
			auto res3 = printAllMultiples_careercup(0);

			//assert(res1 == res2);
			assert(res1 == res3);

			cout << to_string(res1) << endl;
		}
		cout << endl;

		cout << "Ugly numbers till 1: " << endl;
		{
			auto res1 = printAllMultiples(1);
			//auto res2 = printAllMultiplesSpaceOptimized(1);
			auto res3 = printAllMultiples_careercup(1);

			//assert(res1 == res2);
			assert(res1 == res3);

			cout << to_string(res1) << endl;
		}
		cout << endl;

		cout << "Ugly numbers till 2: " << endl;
		{
			auto res1 = printAllMultiples(2);
			//auto res2 = printAllMultiplesSpaceOptimized(2);
			auto res3 = printAllMultiples_careercup(2);

			//assert(res1 == res2);
			assert(res1 == res3);

			cout << to_string(res1) << endl;
		}
		cout << endl;

		cout << "Ugly numbers till 10: " << endl;
		{
			auto res1 = printAllMultiples(10);
			//auto res2 = printAllMultiplesSpaceOptimized(10);
			auto res3 = printAllMultiples_careercup(10);

			//assert(res1 == res2);
			assert(res1 == res3);

			cout << to_string(res1) << endl;
		}
		cout << endl;

		cout << "Ugly numbers till 20: " << endl;
		{
			auto res1 = printAllMultiples(20);
			//auto res2 = printAllMultiplesSpaceOptimized(20);
			auto res3 = printAllMultiples_careercup(20);

			//assert(res1 == res2);
			assert(res1 == res3);

			cout << to_string(res1) << endl;
		}
		cout << endl;
	}

	static vector<int> printAllMultiples(int n)
	{
		if (n == 0) return {};

		vector<int> result(n);
		result[0] = 1;
		int i2 = 0, i3 = 0, i5 = 0, i7 = 0;
		for (int i = 1; i < n; i++) {
			int minMultiple = min(min(2 * result[i2], 3 * result[i3]), min(5 * result[i5], 7 * result[i7]));
			result[i] = minMultiple;
			if (minMultiple == 2 * result[i2]) i2++;
			if (minMultiple == 3 * result[i3]) i3++;
			if (minMultiple == 5 * result[i5]) i5++;
			if (minMultiple == 7 * result[i7]) i7++;
		}

		return result;
	}

	// this doesn't work
	static vector<int> printAllMultiplesSpaceOptimized(int n)
	{
		if (n == 0) return {};

		vector<int> result;
		result.push_back(1);
		int i2 = 1, i3 = 1, i5 = 1, i7 = 1;
		for (int i = 1; i < n; i++) {
			int minMultiple = min(min(2 * i2, 3 * i3), min(5 * i5, 7 * i7));
			if (minMultiple == 2 * i2) i2 = 2 * i2;
			if (minMultiple == 3 * i3) i3 = 3 * i3;
			if (minMultiple == 5 * i5) i5 = 5 * i5;
			if (minMultiple == 7 * i7) i7 = 7 * i7;
			result.push_back(minMultiple);
		}

		return result;
	}

	static vector<int> printAllMultiples_careercup(int n)
	{
		if (n == 0) return {};

		unsigned* ugly = (unsigned*)malloc(n * sizeof(unsigned*));
		unsigned next_multiple_2 = 2;
		unsigned next_multiple_3 = 3;
		unsigned next_multiple_5 = 5;
		unsigned next_multiple_7 = 7;
		unsigned i2 = 0, i3 = 0, i5 = 0, i7 = 0;
		ugly[0] = 1;

		for (int i = 1; i < n; i++)
		{
			unsigned next_ugly_no = min4(next_multiple_2, next_multiple_3, next_multiple_5, next_multiple_7);
			*(ugly + i) = next_ugly_no;

			if (next_ugly_no == next_multiple_2)
			{
				i2 = i2 + 1;
				next_multiple_2 = ugly[i2] * 2;
			}
			if (next_ugly_no == next_multiple_3)
			{
				i3 = i3 + 1;
				next_multiple_3 = ugly[i3] * 3;
			}
			if (next_ugly_no == next_multiple_5)
			{
				i5 = i5 + 1;
				next_multiple_5 = ugly[i5] * 5;
			}
			if (next_ugly_no == next_multiple_7)
			{
				i7 = i7 + 1;
				next_multiple_7 = ugly[i7] * 7;
			}
		}

		vector<int> result;
		for (int i = 0; i < n; i++) result.push_back(ugly[i]);
		return result;
	}

	static int min4(int a, int b, int c, int d)
	{
		return min(a, min(b, min(c, d)));
	}

	static bool equal(vector<int>& a, vector<int>& b) {
		if (a.size() != b.size()) return false;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) return false;
		}
		return true;
	}
};