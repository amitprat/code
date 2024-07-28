#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5637944224251904

Given a number M (N-digit integer) and K-swap operations(a swap
operation can swap 2 digits), devise an algorithm to get the maximum possible integer?
Examples:
M = 132 K = 1 output = 312
M = 132 K = 2 output = 321
M = 7899 k = 2 output = 9987
M = 8799 and K = 2 output = 9987
*/

class MaximumPossibleNumber {
   public:
    static void test() {
        MaximumPossibleNumber obj;

        vector<int> input1 = {1, 3, 2};
        obj.swap2max(input1, 1);
        cout << "Result : " << obj.makeMax(input1, 1) << endl;

        vector<int> input2 = {1, 3, 2};
        obj.swap2max(input2, 2);
        cout << "Result : " << obj.makeMax(input2, 2) << endl;

        vector<int> input3 = {7, 8, 9, 9};
        obj.swap2max(input3, 2);
        cout << "Result : " << obj.makeMax(input3, 2) << endl;

        vector<int> input4 = {8, 7, 9, 9};
        obj.swap2max(input4, 2);
        cout << "Result : " << obj.makeMax(input4, 2) << endl;
    }

   public:
    void swap2max(vector<int> input, int k) {
        if (input.size() < 2) {
            cout << "invalid input" << endl;
        }
        int maxNum = INT_MIN;
        vector<int> maxVec;
        getMax(input, k, maxNum, maxVec);  // DFS function to call

        // print out the results here
        cout << "{ ";
        for (int i = 0; i < maxVec.size(); i++) {
            cout << maxVec[i] << " ";
        }
        cout << " }" << endl;
        return;
    }

    void getMax(vector<int>& input, int k, int& maxNum, vector<int>& output) {
        if (k == 0) {
            if (max(input) > max(output)) {
                output = input;
            }
            return;
        }

        for (int i = 0; i < input.size() - 1; i++) {
            for (int j = i + 1; j < input.size(); j++) {
                swap(input[i], input[j]);              // try to swap input[i] with input[j]
                getMax(input, k - 1, maxNum, output);  // takecare of the other k - 1 swaps
                swap(input[i], input[j]);              // swap back
            }
        }
    }

   public:
    vector<int> makeMax(vector<int>& arr, int k) {
        vector<int> res;
        makeMax(arr, k, 0, res);

        return res;
    }

    void makeMax(vector<int>& arr, int k, int index, vector<int>& res) {
        if (k == 0 || index == arr.size()) {
            if (max(arr) > max(res)) {
                res = arr;
            }
            return;
        }

        for (int i = index; i < arr.size(); i++) {
            swap(arr[index], arr[i]);
            makeMax(arr, k - 1, index + 1, res);
            swap(arr[index], arr[i]);
        }
    }

    int max(vector<int>& arr) {
        int val = 0;
        for (auto& e : arr) {
            val = val * 10 + e;
        }

        return val;
    }
};