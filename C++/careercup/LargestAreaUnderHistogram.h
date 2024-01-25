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
};