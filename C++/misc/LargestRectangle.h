#pragma once
#include "../header.h"

class LargestRectangle {
public:
    static void test() {
        LargestRectangle obj;
        vector<int> v = { 6, 2, 5, 4, 5, 1, 6 };
        cout << "Area of largest rectangle: " << obj.getArea(v) << endl;
    }

    int getArea(vector<int> hist) {
        stack<int> indices;
        int mxArea = 0;
        int i = 0;
        for (; i < hist.size();) {
            if (indices.empty() || hist[i] >= hist[indices.top()]) {
                indices.push(i++);
            }
            else {
                int cur = indices.top(); indices.pop();
                int height = hist[cur];
                int width = indices.empty() ? i : i - indices.top() - 1;
                mxArea = max(mxArea, height * width);
            }
        }
        while (!indices.empty()) {
            int cur = indices.top(); indices.pop();
            int height = hist[cur];
            int width = indices.empty() ? i : i - indices.top() - 1;
            mxArea = max(mxArea, height * width);
        }
        return mxArea;
    }
};