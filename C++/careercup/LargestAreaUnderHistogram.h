#include "../header.h"

class LargestAreaUnderHistogram {
   public:
    static void test() {
        LargestAreaUnderHistogram obj;
        vector<int> hist = {6, 2, 5, 4, 5, 1, 6};
        auto res = obj.largestArea(hist);
        cout << "Largest " << res << endl;
    }

   public:
    int largestArea(vector<int>& arr) {
        stack<int> st;
        int maxArea = 0;
        int i = 0;
        for (; i < arr.size();) {
            // if this bar is higher then we can keep pushing it to stack
            // as we can always consider previous bar * distance as maximum area
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