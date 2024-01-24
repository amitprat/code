#include "../header.h"

/*
https://careercup.com/question?id=5726537143812096

Write a program to replace each element of an array with a number present on the right side of the element such that the number is least greater than the element. If there is no greater number replace it with -1

e.g : 8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28
ans : 18, 63, 80, 25, 32, 43, 80, 93, 80, 25, 93, -1, 28, -1, -1

I gave the obvious o(n^2) solution. He asked to optimize it.

Here is an O(nlogn) [amortized] approach using a threaded BST where each node points to the next in order successor.
1) read the array from right to left
2) Insert each element into a threaded BST.
3) Output the inorder successor after each insertion.

Perhaps we could reshape the threaded tree in between to make it balanced and increase performance but am not sure if we can modify a threaded tree.
*/
class FindNextGreaterElementOnRight {
   private:
    void printNextGreaterElement(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " --> ";
            for (int j = i + 1; j < arr.size(); j++) {
                if (arr[j] > arr[i]) {
                    cout << arr[j] << endl;
                    break;
                }
            }
        }
    }

   private:
    void printNextGreaterUsingStack(vector<int>& arr) {
        stack<int> st;
        for (auto& e : arr) {
            while (!st.empty() && st.top() < e) {
                cout << st.top() << " --> " << e << endl;
                st.pop();
            }

            st.push(e);
        }

        while (!st.empty()) {
            cout << st.top() << " --> "
                 << "-1" << endl;
            st.pop();
        }
    }

   private:
    void printNextGreaterElementOptimized(vector<int>& arr) {
        int n = arr.size();
        vector<int> greater(n, -1);
        int mx = arr[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            if (arr[i + 1] > arr[i])
                greater[i] = arr[i + 1];
            else {
                if (greater[i + 1] > greater[i])
                    greater[i] = greater[i + 1];
                else if (mx > arr[i]) {
                    int k = i + 1;
                    while (arr[k] <= arr[i]) k++;
                    greater[i] = arr[k];
                } else {
                    greater[i] = -1;
                }
            }
            mx = max(mx, arr[i]);
        }

        cout << greater << endl;
    }
};