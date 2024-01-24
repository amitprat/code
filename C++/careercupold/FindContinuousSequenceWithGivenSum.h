#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=6305076727513088
*
Question: Given a sequence of positive integers A and an integer T, return whether there is a continuous sequence of A that sums up to exactly T
Example
[23, 5, 4, 7, 2, 11], 20. Return True because 7 + 2 + 11 = 20
[1, 3, 5, 23, 2], 8. Return True because 3 + 5 = 8
[1, 3, 5, 23, 2], 7 Return False because no sequence in this array adds up to 7


public boolean findSum (int [] A ,int T){
		int sum = 0 ;
		int j = 0;
		for (int i = 0 ; i < A.length ; ++i) {
			while (j < A.length &&  sum < T) {
				sum += A[j] ;
				j++;
			}
			if (sum == T) {
				return true ;
			}
			sum -= A[i] ;
		}

		return false ;
}
*/
class FindContinuousSequenceWithGivenSum
{
public:
	static void test() {
		{
			vector<int> arr = { 23, 5, 4, 7, 2, 11 };
			int s = 20; // Return True because 7 + 2 + 11 = 20
			bool res = findSum(arr, s);
			cout << "Is Possible? " << res << endl;
		}
		{
			vector<int> arr = { 1, 3, 5, 23, 2 };
			int s = 8;// Return True because 3 + 5 = 8
			bool res = findSum(arr, s);
			cout << "Is Possible? " << res << endl;
		}
		{
			vector<int> arr = { 1, 3, 5, 23, 2 };
			int s = 7; // Return False because no sequence in this array adds up to 7
			bool res = findSum(arr, s);
			cout << "Is Possible? " << res << endl;
		}
	}

	static bool isPossible(vector<int>& arr, int sum) {
		for (int s = 0, e = 0, curSum = 0; s < arr.size();) {
			if (curSum == sum) return true;
			if (e == arr.size() && curSum < sum) return false;

			if (e < arr.size()) curSum += arr[e++];
			if (curSum >= sum) curSum -= arr[s++];
		}

		return false;
	}

	static bool findSum(vector<int>& arr, int sum) {
		int curSum = 0;
		for (int s = 0, e = 0; e <= arr.size();) {
			if (e < arr.size() && curSum < sum) curSum += arr[e++];
			if (curSum == sum) return true;
			if (e == arr.size() && curSum < sum) return false;

			if (curSum > sum) curSum -= arr[s++];
		}
		return false;
	}
};