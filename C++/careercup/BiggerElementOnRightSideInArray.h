#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=6497025214382080

Replace element of an Array with nearest bigger number at right side of the Array in O(n)
For example if the input Array is
7, 5, 6, 3, 4, 1, 2, 9, 11
output array should be
9, 6, 9, 4, 9, 2, 9, 11, 11


for( i = N-1; i>=0; i-- )
{
    while( !S.isEmpty && a[i] >= S.checkTop() )  //try to find > a[i] element
        S.pop();

    if( S.isEmpty )
        result[i]= INF;  //nothing > a[i] to right  (or use a[i] instead of INF)
    else
        result[i]= S.checkTop();    //this was > a[i] to right

    S.push(a[i]);
}
*/
class BiggerElementOnRightSideInArray {
   public:
    static void test() {
        vector<int> arr = {7, 5, 6, 3, 4, 1, 2, 9, 11};
        cout << "Input: " << arr << endl;

        BiggerElementOnRightSideInArray obj;

        auto result = obj.replaceWithBiggerElementsOnRight(arr);
        cout << "Output: " << result << endl;
    }

    vector<int> replaceWithBiggerElementsOnRight(const vector<int>& arr) {
        stack<int> st;
        vector<int> result(arr.size(), INT_MAX);

        for (int i = arr.size() - 1; i >= 0; i--) {
            while (!st.empty() && arr[i] > st.top()) st.pop();

            if (st.empty())
                result[i] = INT_MAX;
            else
                result[i] = st.top();

            st.push(arr[i]);
        }

        return result;
    }
};