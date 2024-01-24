#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5078393905217536


There is an array of 3-tuple, in the form of (a, 1, 5). The first element in the tuple is the id, the second and third elements
are both integers, and the third is always larger than or equal to the second. Assume that the array is sorted based on the second
element of the tuple. Write a function that breaks each of the 3-tuple into two 2-tuples like (a, 1) and (a, 5), and sort them
according to the integer.

E.g. given (a, 1, 5), (b, 2, 4), (c, 7, 8), output (a, 1), (b, 2), (b, 4), (a, 5), (c, 7), (c, 8).


The O(nlogn) Solution is pretty straight forward. The interesting part is: whether can we find O(n) solution. The answer is NO.
I can prove this by contradiction.
Assume such algorithm exists. Then for any N integers x1,x2,....xn. I construct the N three tuples (a, -infinity, x1),
(b, -infinity, x2)...... clearly -infinity < xk, so it satisfies the condition. Now, with the algorithm, we can get
(a,-infinity), (b, -infinity) .......(a, x1), (b, x3)..... This means we can sort any N integers in O(N) time, which
is impossible based on normal comparison. Of course, if you do it by using bucket sort, you can do it but it needs
more assumptions about the numbers.
*/
class TupleSort
{
public:
	static void test()
	{
		vector<tuple<char, int, int>> values = { {'a', 1, 5}, {'b', 2, 4}, {'c', 7, 8} };

		vector<pair<char, int>> sortedPair = generateSortedPair(values);
		cout << to_string(sortedPair) << endl;
	}

	static vector<pair<char, int>> generateSortedPair(vector<tuple<char, int, int>> values)
	{
		vector<pair<char, int>> result;
		vector<pair<char, int>> tmp1;
		vector<pair<char, int>> tmp2;

		for (auto e : values)
		{
			tmp1.push_back({ get<0>(e), get<1>(e) });
			tmp2.push_back({ get<0>(e), get<2>(e) });
		}

		int i = 0, j = 0;
		while (i < tmp1.size() || j < tmp2.size())
		{
			if (i == tmp1.size())
				result.push_back(tmp2[j++]);
			else if (j == tmp2.size())
				result.push_back(tmp1[i++]);
			else if (tmp1[i].second <= tmp2[j].second)
				result.push_back(tmp1[i++]);
			else
				result.push_back(tmp2[j++]);
		}

		return result;
	}
};