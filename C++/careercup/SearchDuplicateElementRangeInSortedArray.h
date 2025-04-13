#include "../header.h"

/*
https://www.careercup.com/question?id=4785565681582080

Given a sorted array with duplicates and a number, find the range in the
form of (startIndex, endIndex) of that number. For example,

find_range({0 2 3 3 3 10 10}, 3) should return (2,4).
find_range({0 2 3 3 3 10 10}, 6) should return (-1,-1).
The array and the number of duplicates can be large.

stackoverflow: https://stackoverflow.com/questions/39712883/finding-range-index-of-a-sorted-array-on-a-specific-element
*/
class SearchDuplicateElementRangeInSortedArray {
   public:
    static void test() {
        SearchDuplicateElementRangeInSortedArray obj;

        vector<pair<vector<int>, int>> inputs = {
            {{0, 2, 3, 3, 3, 10, 10}, -5},
            {{0, 2, 3, 3, 3, 10, 10}, 0},
            {{0, 2, 3, 3, 3, 10, 10}, 3},
            {{0, 2, 3, 3, 3, 10, 10}, 6},
            {{0, 2, 3, 3, 3, 10, 10}, 10},
            {{0, 2, 3, 3, 3, 10, 10}, 12}};

        for (const auto& input : inputs) {
            auto range = obj.search_range_single_loop(input.first, input.second);

            cout << "Range for element: " << input.second << " in array " << input.first << " is " << range << endl;
        }
    }

   public:
    pair<int, int> search_range(const vector<int>& arr, int elem) {
        pair<int, int> result;
        int l = 0, r = arr.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (elem <= arr[m])
                r = m - 1;
            else
                l = m + 1;
        }
        result.first = (l < arr.size() && arr[l] == elem) ? l : -1;

        while (l <= r) {
            int m = (l + r) / 2;
            if (elem < arr[m])
                r = m - 1;
            else
                l = m + 1;
        }
        result.second = (r >= 0 && arr[r] == elem) ? r : -1;

        return result;
    }

   public:
    pair<int, int> search_range2(const vector<int>& arr, int elem) {
        int left = search_left(arr, 0, arr.size() - 1, elem);
        if (left == -1) return {-1, -1};

        int right = search_right(arr, 0, arr.size() - 1, elem);
        if (right == -1) return {-1, -1};

        return {left, right};
    }

   private:
    int search_left(const vector<int>& arr, int l, int r, int elem) {
        if (l > r) return -1;
        if (l == r) return arr[l] == elem ? l : -1;

        int m = (l + r) / 2;
        if (elem <= arr[m])
            return search_left(arr, l, m, elem);
        else
            return search_left(arr, m + 1, r, elem);
    }

    int search_right(const vector<int>& arr, int l, int r, int elem) {
        if (l > r) return -1;
        if (l == r) return arr[l] == elem ? l : -1;

        int m = (l + r + 1) / 2;
        if (elem >= arr[m])
            return search_right(arr, m, r, elem);
        else
            return search_right(arr, l, m - 1, elem);
    }

   public:
    // We only search for both half for specific case where mid element matches the search elem.
    // For rest of the cases, we ignore the other half and only search in one half and hence giving
    // overall complexity of T=O(lgn).
    pair<int, int> search_range_single_loop(const vector<int>& arr, int elem) {
        return search_range_single_loop(arr, 0, arr.size() - 1, elem);
    }

    pair<int, int> search_range_single_loop(const vector<int>& arr, int l, int r, int elem) {
        if (l > r) return {-1, -1};

        int m = (l + r) / 2;
        if (arr[m] == elem) {
            auto left = search_range_single_loop(arr, l, m - 1, elem);
            auto right = search_range_single_loop(arr, m + 1, r, elem);

            pair<int, int> result = {m, m};
            if (left.first != -1) result.first = left.first;
            if (right.second != -1) result.second = right.second;

            return result;
        } else if (elem < arr[m])
            return search_range_single_loop(arr, l, m - 1, elem);
        else
            return search_range_single_loop(arr, m + 1, r, elem);
    }
};