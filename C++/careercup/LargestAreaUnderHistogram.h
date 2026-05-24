#pragma once
#include "../header.h"

/*
Find the largest rectangular area possible in a given histogram where the largest rectangle can be made of a number of contiguous bars
whose heights are given in an array.
*/
class LargestAreaUnderHistogram {
   public:
    static void test() {
        LargestAreaUnderHistogram obj;

        vector<int> hist = {6, 2, 5, 4, 5, 1, 6};
        auto res = obj.largestArea(hist);
        assert(res == 12);
        cout << format("Largest area: {}", res) << endl;
    }

   public:
    int largestArea(vector<int>& arr) {
        stack<int> st;
        int maxArea = 0;

        int i = 0;
        for (; i < arr.size();) {
            // if new bar on right is greater or equal to current bar on top of stack (or stack is empty),
            // push bar to top of stack. This is because, while popping elements from stack, we know that
            // bars between [being popped, end or bar lesser then stack top-1] are all larger than bar [being popped].
            if (st.empty() || arr[i] >= arr[st.top()]) {
                st.push(i++);
            } else {
                // calculate the area on left without considering this bar
                auto top = st.top();
                st.pop();
                auto height = arr[top];
                auto width = st.empty() ? i : (i - 1 - st.top());
                auto curArea = height * width;
                maxArea = max(maxArea, curArea);
            }
        }

        // if elements are there in stack, they are all in increasing order
        // example: 2,3,4,5
        // if there were smaller elements on right, they were already removed above
        // ex: 1,2,3,4,5,4,3,2 (when inserting 4, 5 was removed, inserting 3, 4s were removed, inserting 2, 3s were removed)
        // so only left is 1. And all elements on right till end must be greater than that.
        while (!st.empty()) {
            auto cur = st.top();
            st.pop();
            auto height = arr[cur];
            auto width = st.empty() ? i : (i - 1 - st.top());
            auto curArea = height * width;
            maxArea = max(maxArea, curArea);
        }

        return maxArea;
    }

   private:
    int largestRectangleArea(vector<int>& heights) {
        int area = 0;

        stack<int> st;

        // we push -1 to stack to handle the case when we are popping all elements from stack and calculating area for first element in histogram.
        st.push(-1);

        for (int i = 0; i < heights.size(); i++) {
            // example case: 2,3,1
            // lets say, we are at 1 (i==2)
            // lets not consider right element at 1, right most position = 1
            // height of bar at position 1 is 3.
            // then we pop 3 as no longer considerin it for future after that, st.top becomes 0.
            // the width we need to consider starts at left position=1(value=3), right postition=1(value=3)
            // so area under this bar is 3*1=3. We update max area with that.

            // After that we consider 2 at index 0;
            // lets not consider right element at 1, right most position = 1
            // height of bar at position 1 is 2.
            // then we pop 2 as no longer considerin it for future after that, st.top becomes -1.
            // the width we need to consider starts at left position=0(value=2), right postition=1(value=3)
            // so area under this bar is 2*2=4. We update max area with that.

            // One thing to note is that all bars on right of current bar are greater than current bar,
            // otherwise they would have been popped already. So we can consider all bars on right till end.
            while (st.top() != -1 && heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();
                int w = (i - 1 - st.top());  // consider all on right except current one
                area = max(area, h * w);
            }

            // if current bar is greater than or equal to bar on top of stack, we can consider it for future as well, so push it to stack.
            st.push(i);
        }

        // if elements are there in stack, they are all in increasing order
        // example: 2,3,4,5
        // if there were smaller elements on right, they were already removed above
        // ex: 1,2,3,4,5,4,3,2 (when inserting 4, 5 was removed, inserting 3, 4s were removed, inserting 2, 3s were removed)
        // so only left is 1. And all elements on right till end must be greater than that.
        // so, here all bars on right is equal to historgram width and current bar is height, so area is height*width.
        while (st.size() > 1) {
            int h = heights[st.top()];
            st.pop();
            int w = heights.size() - 1 - st.top();  // everything on right, except left one
            area = max(area, h * w);
        }

        return area;
    }
};