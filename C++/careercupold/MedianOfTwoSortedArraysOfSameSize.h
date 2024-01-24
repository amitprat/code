#pragma once
#include "../Header.h"

class MedianOfTwoSortedArraysOfSameSize {
public:
	static void test() {
		MedianOfTwoSortedArraysOfSameSize obj;

		{
			int ar1[] = { 1, 12, 15, 26, 38 };
			int ar2[] = { 2, 13, 17, 30, 45 };

			int n1 = sizeof(ar1) / sizeof(ar1[0]);
			int n2 = sizeof(ar2) / sizeof(ar2[0]);

			auto res = obj.median(ar1, ar2, n2);
			cout << "Median = " << res << endl;
		}

		{
			int ar1[] = { 1, 2, 3, 6 };
			int ar2[] = { 4, 6, 8, 10 };
			int n1 = sizeof(ar1) / sizeof(ar1[0]);
			int n2 = sizeof(ar2) / sizeof(ar2[0]);

			auto res = obj.median(ar1, ar2, n2);
			cout << "Median = " << res << endl;
		}

		{
			int ar1[] = { 1 };
			int ar2[] = { 4 };
			int n1 = sizeof(ar1) / sizeof(ar1[0]);
			int n2 = sizeof(ar2) / sizeof(ar2[0]);

			auto res = obj.median(ar1, ar2, n2);
			cout << "Median = " << res << endl;
		}

		{
			int ar1[] = { 1,2 };
			int ar2[] = { 4,8 };
			int n1 = sizeof(ar1) / sizeof(ar1[0]);
			int n2 = sizeof(ar2) / sizeof(ar2[0]);

			auto res = obj.median(ar1, ar2, n2);
			cout << "Median = " << res << endl;
		}

		{
			int ar1[] = { 1,2, 3 };
			int ar2[] = { 4,7,8 };
			int n1 = sizeof(ar1) / sizeof(ar1[0]);
			int n2 = sizeof(ar2) / sizeof(ar2[0]);

			auto res = obj.median(ar1, ar2, n2);
			cout << "Median = " << res << endl;
		}

		{
			int ar1[] = { 1,4, 6 };
			int ar2[] = { 2,3,5 };
			int n1 = sizeof(ar1) / sizeof(ar1[0]);
			int n2 = sizeof(ar2) / sizeof(ar2[0]);

			auto res = obj.median(ar1, ar2, n2);
			cout << "Median = " << res << endl;
		}
	}

	double median(int arr1[], int arr2[], int n) {
		auto res1 = median1(arr1, arr2, n);
		auto res2 = median2(arr1, arr2, n);
		auto res3 = medianBruteForce(arr1, arr2, n);

		assert(res1 == res2);
		assert(res1 == res3);

		return res1;
	}

	double median1(int arr1[], int arr2[], int n) {
		int p1 = 0, p2 = 0;
		int i = 0, j = 0;
		for (int cnt = 0; cnt <= n; cnt++) {
			p1 = p2;
			if (i == n) {
				p2 = arr2[0];
			}
			else if (j == n) {
				p2 = arr1[0];
			}
			else if (arr1[i] <= arr2[j]) {
				p2 = arr1[i++];
			}
			else {
				p2 = arr2[j++];
			}
		}

		return (double)(p1 + p2) / 2.0;
	}

	double median2(int arr1[], int arr2[], int n) {
		if (n == 1) return (double)(arr1[0] + arr2[0]) / 2.0;

		double m1 = median(arr1, n);
		double m2 = median(arr2, n);

		if (m1 == m2) return m1;
		else if (m1 <= m2) return median2(arr1 + n / 2, arr2, n - n / 2);
		else return median2(arr1, arr2 + n / 2, n - n / 2);
	}

	double median(int arr[], int n) {
		if (n & 1) return arr[n / 2];
		return (double)(arr[n / 2 - 1] + arr[n / 2]) / 2.0;
	}

	double medianBruteForce(int arr1[], int arr2[], int n) {
		int* arr3 = new int[2 * n];
		for (int i = 0, k = 0; i < n; i++) {
			arr3[k++] = arr1[i];
			arr3[k++] = arr2[i];
		}
		sort(arr3, arr3 + 2 * n);

		return (double)(arr3[n - 1] + arr3[n]) / 2.0;
	}
};