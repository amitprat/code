#include "../header.h"

/*
https://careercup.com/question?id=4798365246160896


Question was on Arithmetic progression

Example :
Given the AP :- 1 3 7 9 11 13 find the missing value "which would be 5 here".

Conditions :
Get an user for the length of AP sequence and make sure user provides length is above 3.
Get the input in a single line ex:- "1 3 5 7 9 11"

public static int findMissing_binary(int[] array) {
    assert array != null && array.length > 2;

    int diff = Math.min(array[2]-array[1], array[1]-array[0]);

    int low = 0, high = array.length-1;
    while(low < high) {
        int mid = (low+high) >>> 1;

        int leftDiff = array[mid]-array[low];
        if(leftDiff > diff * (mid-low)) {
            if(mid-low == 1)
                return (array[mid]+array[low]) / 2;

            high = mid;
            continue;
        }

        int rightDiff = array[high]-array[mid];
        if(rightDiff > diff * (high-mid)) {
            if(high-mid == 1)
                return (array[high]+array[mid]) / 2;

            low = mid;
            continue;
        }
    }

    return -1;
}
*/
class FindMissingElementInAP {
   public:
    static void test() {
        FindMissingElementInAP obj;
        vector<int> arr = {1, 3, 7, 9, 11, 13};
        auto res = obj.findMissing(arr);
        cout << "Missing element is " << res << endl;
    }

    int findMissing(vector<int> arr) {
        int d = min(arr[2] - arr[1], arr[1] - arr[0]);
        return findMissing(arr, 0, arr.size() - 1, d);
    }
    int findMissing(vector<int> arr, int l, int r, int d) {
        if (l == r) return INT_MIN;
        if (r - l == 1) return arr[l] + d;
        int m = (l + r) / 2;
        if (arr[m] - arr[l] > (m - l) * d) {
            return findMissing(arr, l, m, d);
        } else {
            return findMissing(arr, m, r, d);
        }

        return INT_MIN;
    }
};
