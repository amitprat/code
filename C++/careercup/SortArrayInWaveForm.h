#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=5145759489982464

Given an array of integers, sort the array into a wave like array, namely
a1 >= a2 <= a3 >= a4 <= a5.....

There are two O(n) solutions for this problem that does not require ordering.
1. You can find the median in O(n) and then rearrange the elements around the median
2. (Better Solution) If you notice the desired ordering, the even numbered elements are bigger (or equal) than the
next element, and the odd numbered elements are less than (or equal) than the next element, of course I am assuming the
array is 0 offset.

So, you can iterate the array and swap the elements that doesn't match this arrangements,e.g., swap A[i] and A[i+1],
when i is even and A[i] < A[i + 1].

Reference : http://www.geeksforgeeks.org/sort-array-wave-form-2/
Sort array in wave format - like
ip : 2 4 6 8 10 20
op : 4 2 8 6 20 10

1) T = O(nlgn)
  Sort the array and swap adjacent elements
  for(int i=0;i<n-1;i+=2)
  {
    swap(a[i],a[i+1]);
  }

2) T = O(n)
Trick : Just consider EVEN position elements, make sure it is on crest (i.e. bigger than previous and next element)

for(int i=0;i<n;i+=2) {
  if(i > 0 && a[i] < a[i-1])  //if this even position element is less than previous element, then swap it
    swap(a[i],a[i-1]);
  if(i<n-1 && a[i] < a[i+1])  //if this element is smaller than next element, then also swap it
    swap(a[i],a[i+]);
}
*/
class SortArrayInWaveForm {
   public:
    static void test() {
        SortArrayInWaveForm obj;
        vector<vector<int>> arrs = {
            {10, 90, 49, 2, 1, 5, 23}};

        for (const auto& arr : arrs) {
            auto copy1 = arr;
            auto copy2 = arr;
            auto copy3 = arr;
            obj.sortInWave1(copy1);
            obj.sortInWave2(copy2);
            obj.sortInWave3(copy3);
            assert(areEqual(copy1, copy2));
            // assert(areEqual(copy1, copy3));

            cout << "Sorted: " << copy1 << endl;
        }
    }

   private:
    void sortInWave1(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n; i += 2) {
            if (i > 0 && arr[i] < arr[i - 1])
                swap(arr[i], arr[i - 1]);
            if (i < n - 1 && arr[i] < arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
    }

   private:
    void sortInWave2(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            if (!(i & 1) && arr[i] < arr[i + 1]) swap(arr[i], arr[i + 1]);
            if ((i & 1) && (arr[i] > arr[i + 1])) swap(arr[i], arr[i + 1]);
        }
    }

   private:
    void sortInWave3(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        for (int i = 0; i < n - 1; i += 2) swap(arr[i], arr[i + 1]);
    }
};
