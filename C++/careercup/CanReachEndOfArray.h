#include "../header.h"

/*
https://careercup.com/question?id=5728188153987072

You are given an array of non-negative integers (0, 1, 2 etc). The value in each element represents the number of hops you may take to the next destination. Write a function that determines when you start from the first element whether you will be able to reach the last element of the array.

if a value is 3, you can take either 0, 1, 2 or 3 hops.

For eg: for the array with elements 1, 2, 0, 1, 0, 1, any route you take from the first element, you will not be able to reach the last element.

BOOL isPathPossibleArray(int array[], int n){


    int stepsCounter = array[0];

    int index = 0;

    while (stepsCounter > 0) {
        stepsCounter --;
        index++;

        if (index == n-1) {
            return YES;
        }
        int newSteps = array[index];

        if (newSteps > stepsCounter) {
            stepsCounter = newSteps;
        }
    }


    return NO;
}
*/
class CanReachEndOfArray {
   public:
    static void test() {
    }

    bool canReachEnd(vector<int>& arr) {
        int reach = arr[0];
        int index = 0;
        while (reach) {
            index++;
            reach--;
            if (index == arr.size()) return true;

            reach = max(reach, arr[i]);
        }

        return false;
    }

    bool canReachEnd2(vector<int>& arr) {
        int curEnd = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (curEnd < i) return false;
            if (curEnd >= arr.size() - 1) return true;
            curEnd = max(curEnd, i + arr[i]);
        }

        return false;
    }
};