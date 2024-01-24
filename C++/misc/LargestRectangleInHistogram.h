#pragma once
#include "../header.h"

class LargestRectangleHistogram
{
public:
    static void test()
    {
        LargestRectangleHistogram obj;
        vector<int> input = {2, 1, 5, 6, 2, 3};
        cout << obj.largestRectangleArea(input) << endl;
    }
    int largestRectangleArea(vector<int> &heights)
    {
        stack<int> st;
        int mxArea = 0;
        int i = 0;
        while (i < heights.size())
        {
            if (st.empty() || heights[i] >= heights[st.top()])
            {
                st.push(i++);
            }
            else
            {
                int tp = st.top();
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                int curArea = heights[tp] * width;
                // cout << "Current area for (" << (st.empty() ? 0 : st.top() + 1) << "," << i - 1 << ") = " << curArea << endl;
                if (curArea > mxArea)
                    mxArea = curArea;
            }
        }

        while (!st.empty())
        {
            int tp = st.top();
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            int curArea = heights[tp] * width;
            // cout << "Current area for (" << (st.empty() ? 0 : st.top() + 1) << "," << i - 1 << ") = " << curArea << endl;
            if (curArea > mxArea)
                mxArea = curArea;
        }

        return mxArea;
    }
};