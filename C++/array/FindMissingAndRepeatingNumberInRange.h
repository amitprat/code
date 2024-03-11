#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=21263687

You are given an array of n integers which can contain integers from 1 to n only. Some elements can be repeated multiple times
and some other elements can be absent from the array. Write a running code on paper which takes O(1) space apart from the input
array and O(n) time to print which elements are not present in the array and the count of every element which is there in the array
along with the element number .
NOTE: The array isn't necessarily sorted.

First Let's see what all approaches we can take and then we check if it fits our requirement.
1. Brute Force: Select an element from 1 to N and check it frequency of occurrence. But this will be O(n2) and not O(n) .
2. XOR : but this technique won't work as question mentions an element can be repeated multiple times.
so if element repeats 2 times or 4 times each time result of xor will be 0 so we cannot get the frequency of occurrences.
3. HashMap : We can create a HashMap in O(n) key will be elements and value will be their frequency of occurrence.
But since we have to do it in O(1) space we cannot take this approach.

So we cannot opt for any of the above 3 approach. We have to check for some 4th approach.

Since we have range of numbers given to us we have to think in those lines.
Array Index is from 0 to N-1 and range is from 1 to N.
Can't we use the array as hash itself?
where array "Index-1" represents the key (element) and value stored at index will represent the "frequency of occurrence".

But how will we take care that an element present at any index is not overwritten as this can cause problem?
We can sort the array in that case value present at index i is I+1 itself.

What is the complexity of sorting the array?
O(nlogn) if we opt for heap/merge/quick sort.

But since the range of element is given to us we can sort it in O(n).
*/

class FindMissingAndRepeatingNumberInRange {
   public:
    static void test() {
        FindMissingAndRepeatingNumberInRange obj;
        vector<vector<int>> input = {
            {1, 1, 2},
            {1, 2, 3, 4, 5, 6, 7, 8},
            {1, 1, 1, 4, 5, 6, 7, 8},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {9, 9, 9, 9, 9, 9, 9, 9},
            {1},
            {9, 9, 9, 9, 9, 9, 9, 8, 7, 9, 9},
        };

        for (auto& arr : input) {
            cout << "Processing array: " << arr << endl;
            obj.solve(arr);
            cout << endl;
        }
    }

   public:
    void solve(vector<int>& arr) {
        int size = arr.size();
        for (auto& num : arr) {
            int orginalNumber = num % (size + 1);
            arr[orginalNumber - 1] += (size + 1);
        }

        for (int num = 1; num <= size; num++) {
            int count = arr[num - 1] / (size + 1);

            if (count == 0)
                cout << format("Element={0} is missing.", num) << endl;
            else
                cout << format("Count of element={0} is {1}", num, count) << endl;
        }
    }
};
