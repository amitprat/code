#include "../header.h"

/*
https://careercup.com/question?id=5129701993480192

Given an array of ages (integers) sorted lowest to highest, output the number of occurrences for each age.
For instance:
[8,8,8,9,9,11,15,16,16,16]
should output something like:
8: 3
9: 2
11: 1
15: 1
16: 3

This should be done in less than O(n).
*/
class CountOccurancesOfNumberInSortedArr {
   public:
    static void test() {
        CountOccurancesOfNumberInSortedArr obj;
        vector<int> arr = {8, 8, 8, 9, 9, 11, 15, 16, 16, 16};

        unordered_map<int, int> result = obj.count1(arr);
        cout << result << endl;

        result = obj.count2(arr);
        cout << result << endl;
    }

    unordered_map<int, int> count1(vector<int>& arr) {
        unordered_map<int, int> result;
        if (arr.size() == 0) return result;

        int prev = arr[0];
        int cnt = 1;

        for (int i = 1; i < arr.size(); i++) {
            if (prev == arr[i])
                cnt++;
            else {
                result[prev] = cnt;
                prev = arr[i];
                cnt = 1;
            }
        }
        result[prev] = cnt;

        return result;
    }

    unordered_map<int, int> count2(vector<int>& arr) {
        unordered_map<int, int> result;
        if (arr.size() == 0) return result;

        for (auto& e : arr) {
            if (result.find(e) == result.end()) {
                int cnt = getCount(arr, e);
                result[e] = cnt;
            }
        }

        return result;
    }

    int getCount(vector<int>& arr, int e) {
        int l = 0, r = arr.size() - 1;

        // get lower point
        while (l < r) {
            int m = (l + r) / 2;
            if (e <= arr[m])
                r = m;
            else
                l = m + 1;
        }
        if (arr[l] != e) return -1;
        int p1 = l;

        l = 0, r = arr.size() - 1;
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (e >= arr[m])
                l = m;
            else
                r = m - 1;
        }

        int p2 = l;

        return p2 - p1 + 1;
    }
};