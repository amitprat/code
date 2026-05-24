#pragma once
#include "../header.h"

class MedianOfTwoSortedArraysOfSameSize {
   public:
    static void test() {
        // pair - first vector is arr1 and second vector is arr2
        using TestCase = std::pair<std::vector<int>, std::vector<int>>;

        constexpr std::array<TestCase, 6> test_cases{
            {{1, 12, 15, 26, 38}, {2, 13, 17, 30, 45}},
            {{1, 2, 3, 6}, {4, 6, 8, 10}},
            {{1}, {4}},
            {{1, 2}, {4, 8}},
            {{1, 2, 3}, {4, 7, 8}},
            {{1, 4, 6}, {2, 3, 5}},
        };

        MedianOfTwoSortedArraysOfSameSize obj;
        for (const auto& [lhs, rhs] : test_cases) {
            const auto result = obj.median(lhs, rhs);

            println("arr1 = {}, arr2 = {}, median = {}", lhs, rhs, result);
        }
    }

   public:
    double median(const vector<int>& arr1, const vector<int>& arr2) {
        auto res1 = median1(arr1, arr2);
        auto res2 = median2(arr1, arr2);
        auto res3 = medianBruteForce(arr1, arr2);

        assert(res1 == res2);
        assert(res1 == res3);

        return res1;
    }

   public:
    double median1(span<const int> arr1, span<const int> arr2) {
        int n = arr1.size();

        int p1 = 0, p2 = 0;
        int i = 0, j = 0;
        for (int cnt = 0; cnt <= n; cnt++) {
            p1 = p2;
            if (i == n) {
                p2 = arr2[0];
            } else if (j == n) {
                p2 = arr1[0];
            } else if (arr1[i] <= arr2[j]) {
                p2 = arr1[i++];
            } else {
                p2 = arr2[j++];
            }
        }

        return (double)(p1 + p2) / 2.0;
    }

   public:
    double median2(span<const int> arr1, span<const int> arr2) {
        int n = arr1.size();
        if (n == 1) return (double)(arr1[0] + arr2[0]) / 2.0;

        double m1 = median(arr1, n);
        double m2 = median(arr2, n);

        if (m1 == m2)
            return m1;
        else if (m1 <= m2)
            return median2(arr1.subspan, arr2, n - n / 2);
        else
            return median2(arr1, arr2 + n / 2, n - n / 2);
    }

    double median(span<const int> arr, int n) {
        if (n & 1) return arr[n / 2];
        return (double)(arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

   public:
    // combine both arrays, sort them and find median
    // because both arrays are of same size, so combined size must be even
    double medianBruteForce(vector<int>& arr1, vector<int>& arr2, int n) {
        int* arr3 = new int[2 * n];
        for (int i = 0, k = 0; i < n; i++) {
            arr3[k++] = arr1[i];
            arr3[k++] = arr2[i];
        }
        sort(arr3, arr3 + 2 * n);

        return (double)(arr3[n - 1] + arr3[n]) / 2.0;
    }
};