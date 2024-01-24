#include "../header.h"

/*
https://careercup.com/question?id=5692698000359424

Array of size (n-m) with numbers from 1..n with m of them missing. Find one all of the missing numbers in O(log). Array is sorted.

Example:
n = 8
arr = [1,2,4,5,6,8]
m=2
Result has to be a set {3, 7}.

We divide the array into 2 equals parts and foreach subarray - we check if the number of elements that are actually in there (meaning the highest value minus the lowest value) matches the number of element of that sub array. If so (meaning the difference is zero) the function weill return from this subarray and do nothing. otherwise, we check if we got array that is actually a pair arr[i],arr[i+1] that has a difference bigger than 1. if so we add all the numbers from arr[i] to arr[i+1].
the complexity is m*log(n). I'm assuming that m is a constant value because if he isn't (say m==n/2) that it will take n/2 times to insert m elements into the set (and O(n/2)>O(log(n))) - so I don't see how to implement it without the assumption m is not a const.


public static Set<Integer> findMissingNumbers(int arr[], int m) {
    Set<Integer> set = new HashSet<Integer>();
    findMissingNumbersBetweenToIndexes(arr, set, 0, arr.length - 1, m);
    return set;
}

public static void findMissingNumbersBetweenToIndexes(int[] arr, Set<Integer> set, int start, int finish, int m) {
    if (m == 0) {
        return;
    }
    if (start + 1 == finish) {
        for (int i = arr[start] + 1; i < arr[finish]; i++) {
            set.add(i);
            m--;
        }
        return;
    }
    int middle = (start + finish) / 2;
    // right
    findMissingNumbersBetweenToIndexes(arr, set, start, middle,
        (arr[middle] - arr[start] + 1) - (middle - start));

    // left
    findMissingNumbersBetweenToIndexes(arr, set, middle, finish,
        (arr[finish] - arr[middle] + 1) - (finish - middle));
}
*/
class FindAllMissingNumbersInArray {
   private:
    void findAllMissingNumbers(vector<int>& arr, int l, int r, int m, vector<int>& result) {
        if (l >= r) return;
        if (m == 0) return;
        if (l + 1 == r) {
            for (int i = arr[l] + 1; i < arr[r]; i++) result.push_back(i);
            return;
        }

        int mid = (l + r) / 2;
        findAllMissingNumbers(arr, l, m, (arr[m] - arr[l]) - (m - l));  // on left
        findAllMissingNumbers(arr, m, r, (arr[r] - arr[m]) - (r - m));  // on left
    }
};