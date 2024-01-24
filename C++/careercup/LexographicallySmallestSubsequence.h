/*
Given an array of n integers, find the lexicographically smallest subsequence of length k.
*/

/*
I feel this question can be solved by stack. once we found previous
element in the stack is larger than current element, than pop out
*/
#include "../Header.h"

void subseq(vector<int> v, int k)
{
    stack<int> st;
    for (auto i : v)
    {
        if (!st.empty() && st.top() > i)
            st.pop();
        if (st.size() < k)
            st.push(i);
    }
    while (!st.empty())
    {
        cout << st.top();
        st.pop();
    }
}