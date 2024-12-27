/*
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

https://leetcode.com/problems/longest-valid-parentheses/description/
*/
#pragma once
#include "../header.h"

class Solution {
   public:
    int longestValidParentheses(string s) {
        int count = 0;

        stack<int> st;
        st.push(-1);

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();

                // This is to handle the case when string starts with ')' paren or invalid substr. In that case, update
                // st position to current position.
                if (st.empty()) {
                    st.push(i);
                } else {
                    // if so far we found it be valid string, then consider the maxLength.
                    count = max(count, i - st.top());
                }
            }
        }

        return count;
    }
};