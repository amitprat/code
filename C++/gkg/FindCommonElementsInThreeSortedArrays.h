#pragma once
#include "../header.h"

class FindCommonElementsInThreeSortedArrays {
   public:
    static void test() {
        FindCommonElementsInThreeSortedArrays obj;

        vector<int> arr1 = {1, 5, 10, 20, 40, 80};
        vector<int> arr2 = {6, 7, 20, 80, 100};
        vector<int> arr3 = {3, 4, 15, 20, 30, 70, 80, 120};

        vector<int> res = obj.findCommonElements(arr1, arr2, arr3);
        cout << "Common elements = " << to_string(res) << endl;
    }

   private:
    vector<int> findCommonElements(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        int i = 0, j = 0, k = 0;
        int l = arr1.size(), m = arr2.size(), n = arr3.size();

        vector<int> res;
        while (i < l && j < m && k < n) {
            int mn = min(arr1[i], min(arr2[j], arr3[k]));
            if (mn == arr1[i] && mn == arr2[j] && mn == arr3[k]) {
                res.push_back(arr1[i]);
            }
            if (mn == arr1[i]) i++;
            if (mn == arr2[j]) j++;
            if (mn == arr3[k]) k++;
        }

        return res;
    }
};