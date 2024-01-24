#include "../header.h"
/*
* Sort an array according to the order defined by another array
* Given two arrays A1[] and A2[], sort A1 in such a way that the relative order among the elements will be same as those are in A2.
For the elements not present in A2, append them at last in sorted order.

Input: A1[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8}
       A2[] = {2, 1, 8, 3}
Output: A1[] = {2, 2, 1, 1, 8, 8, 3, 5, 6, 7, 9}
*/

class SortArrByGivenOrderOfElements {
   public:
    static void test() {
        SortArrByGivenOrderOfElements obj;
        vector<int> input = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
        vector<int> order = {2, 1, 8, 3};
        vector<int> output = input;
        obj.sortArray(output, order);

        cout << format("input={}, order={}, output={}", to_string(input), to_string(order), to_string(output)) << endl;
    }

    void sortArray(vector<int>& arr, vector<int> order) {
        unordered_map<int, int> posMap;
        for (int i = 0; i < order.size(); i++) posMap[order[i]] = i;

        sort(arr.begin(), arr.end(), [&posMap](const auto& f, const auto& s) {
            bool found1 = posMap.find(f) != posMap.end();
            bool found2 = posMap.find(s) != posMap.end();
            if (!found1 && !found2) {
                return f < s;
            } else if (found1 && found2) {
                return posMap[f] < posMap[s];
            } else if (!found2) {
                return true;
            } else {
                return false;
            }
        });
    }
};