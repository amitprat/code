#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=14099679
* Design an algorithm that, given a list of n elements in an array, finds all the elements that appear more than n/3 times in the list. The algorithm should run in linear time ( n >=0 )
* You are expected to use comparisons and achieve linear time. No hashing/excessive space/ and don't use standard linear time deterministic selection algo
*/

class FindNumberOccurringMoreThanKTimes
{
public:
	static void test() {
		int arr[] = { 4,4,4,1,2,3,5,5,5,5,1,2,3,6,4,5,4 };
		int n = sizeof(arr) / sizeof(int);
		int k = 3;
		auto a_map = findOverNth(arr, n, k);

		cout << "Numbers appearing more than (n/k) times, where n=" << n << ", k=" << k << endl;
		for (auto elem : a_map)
		{
			cout << elem.first << " occurred " << elem.second << " times in array" << endl;
		}
	}

	static unordered_map<int, int> findOverNth(int arr[], int n, int k)
	{
		unordered_map<int, int> map;
		for (int i = 0; i < n; i++)
		{
			map[arr[i]]++;
			if (map.size() == k)
			{
				for (auto it = map.begin(); it != map.end();)
				{
					it->second--;
					if (it->second == 0) map.erase(it++);
					else  it++;
				}
			}
		}

		for (auto it = map.begin(); it != map.end(); it++)
		{
			it->second = 0;
		}

		for (int i = 0; i < n; i++)
		{
			if (map.find(arr[i]) != map.end())
			{
				map[arr[i]]++;
			}
		}

		for (auto it = map.begin(); it != map.end();)
		{
			if (it->second < n / k) map.erase(it++);
			else it++;
		}

		return map;
	}
};