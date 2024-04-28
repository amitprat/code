#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/leaders-in-an-array/

Write a program to print all the LEADERS in the array. An element is a leader if it is greater than all the elements to its right side. And the rightmost element is always a leader.

For example:

Input: arr[] = {16, 17, 4, 3, 5, 2},
Output: 17, 5, 2

Input: arr[] = {1, 2, 3, 4, 5, 2},
Output: 5, 2
*/

class LeadersInArray {
   public:
    static void test() {
        LeadersInArray obj;
        vector<int> arr = {16, 17, 4, 3, 5, 2};

        cout << "Print leaders using stack: ";
        obj.printLeaders(arr);

        cout << "Print leaders by iterating from back: ";
        obj.printLeaders2(arr);
    }

   public:
    void printLeaders(vector<int>& arr) {
        if (arr.empty()) return;
        stack<int> st;
        st.push(arr.back());

        for (int i = arr.size() - 2; i >= 0; i--) {
            if (arr[i] >= st.top()) {
                st.push(arr[i]);
            }
        }

        cout << "Leaders in array: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }

   public:
    void printLeaders2(vector<int>& arr) {
        if (!arr.empty()) return;

        int n = arr.size();
        int maxFromRight = arr[n - 1];

        cout << maxFromRight << " ";

        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] >= maxFromRight) {
                maxFromRight = arr[i];
                cout << maxFromRight << " ";
            }
        }
    }
};