#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/maximum-sum-rectangle-in-a-2d-matrix-dp-27/
*/
class MaximumSumRectangleInMatrix {
   public:
    int findMaxSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;

        int m = matrix[0].size();

        int maxSum = INT_MIN, left, right, top, bottom;

        vector<int> tmp(m, 0);
        for (int curTop = 0; curTop < n; curTop++) {
            for (int curBottom = curTop; curBottom < n; curBottom++) {
                for (int j = 0; j < m; j++) {
                    tmp[j] += matrix[curBottom][j];
                }

                int curLeft = -1, curRight = -1;
                auto curSum = kadane(tmp, curLeft, curRight);

                if (curSum > maxSum) {
                    maxSum = curSum;
                    left = curLeft;
                    right = curRight;
                    top = curTop;
                    bottom = curBottom;
                }
            }
        }

        cout << "Max Sum Matrix:" << endl;
        for (int i = top; i <= bottom; i++) {
            for (int j = left; j <= right; j++) {
                cout << setw(4) << matrix[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Max sum is: " << maxSum << endl;

        return maxSum;
    }

   private:
    int kadane(vector<int>& arr, int& start, int& finish) {
        int maxOfAll = INT_MIN;
        int maxSoFar = 0;

        int s = 0;
        for (int i = 0; i < arr.size(); i++) {
            maxSoFar += arr[i];
            if (maxSoFar > maxOfAll) {
                start = s;
                finish = i;
                maxOfAll = maxSoFar;
            }
            if (maxSoFar < 0) {
                s = i + 1;
                maxSoFar = 0;
            }
        }

        return maxOfAll;
    }

   public:
    static void test() {
        MaximumSumRectangleInMatrix obj;
        vector<vector<int>> matrix = {
            {1, 2, -1, -4, -20},
            {-8, -3, 4, 2, 1},
            {3, 8, 10, 1, 3},
            {-4, -1, 1, 7, -6}};

        obj.findMaxSum(matrix);
    }
};
