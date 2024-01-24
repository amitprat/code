#pragma once
#include "../Header.h"

class MaxAreaRectangle {
    static const int n = 5, m = 5;
public:
    static void test() {
        MaxAreaRectangle obj;
        int mat[][m] = {
            {0,0,0,1,0},
            {1,1,1,0,0},
            {1,1,1,1,0},
            {1,1,0,0,0},
            {1,1,0,1,0}
        };

        auto res = obj.maxArea(mat);
        cout << "Max Area = " << res << endl;
    }

    int maxArea(int mat[][m]) {
        int mxArea = 0;
        int left, right, top, bottom;
        for (int i = 0; i < n; i++) {
            if (i != 0) {
                for (int j = 0; j < m; j++) {
                    if (mat[i][j]) {
                        mat[i][j] += mat[i - 1][j];
                    }
                }
            }
            int curLeft, curRight;
            int curArea = maxAreaHist(mat[i], curLeft, curRight);
            if (curArea > mxArea) {
                left = curLeft;
                right = curRight;
                bottom = i;
                top = i - mat[i][right]+1;
                mxArea = curArea;
            }
        }

        for (int i = top; i <= bottom; i++) {
            for (int j = left; j <= right; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }

        return mxArea;
    }

    int maxAreaHist(int hist[m], int& left, int& right) {
        int mxArea = 0;
        stack<int> st;
        int i = 0;
        while (i < m) {
            if (st.empty() || hist[st.top()] <= hist[i]) {
                st.push(i++);
            }
            else {
                int h = hist[st.top()]; st.pop();
                int w = st.empty() ? i : (i - st.top() - 1);
                if (h * w > mxArea) {
                    mxArea = h * w;
                    left = st.empty() ? 0 : st.top();
                    right = i - 1;
                }
            }
        }

        while (!st.empty()) {
            int h = hist[st.top()]; st.pop();
            int w = st.empty() ? i : (i - st.top() - 1);
            if (h * w > mxArea) {
                mxArea = h * w;
                left = st.empty() ? 0 : st.top();
                right = i - 1;
            }
        }
        return mxArea;
    }
};