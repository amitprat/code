#pragma once
/*
Given an array of integer, find the maximum drop between two array elements, given that second element comes after the first one.
*/

/*
More generalized form of the problem where attempting to get the maximum a[m] - a[n] where m - n >= 1 instead of m - n == 1 .

O(n) runtime with O(1) memory:
*/

//returns -1 if no drop from some a[m] to a[n] where m < n could be computed
public static int maxDrop(int[] arr) {
    if (arr == null) {
        throw new NullPointerException();
    }
    if (arr.length == 0) {
        return -1;
    }

    int bestDiff = -1;
    int max = arr[0];
    int currentDiff = -1;

    for (int i = 0; i < arr.length; i++) {
        int val = arr[i];
        if (val > max) {
            max = val;
            currentDiff = -1;
        }
        else {
            int diff = max - val;
            if (diff > currentDiff) {
                currentDiff = diff;
                if (currentDiff > bestDiff) {
                    bestDiff = currentDiff;
                }
            }
        }
    }
    return bestDiff;
}