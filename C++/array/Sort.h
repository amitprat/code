#pragma once
#include "../header.h"
using namespace std;

class Sort
{
public:
    void test()
    {
        vector<vector<int>> v = {
            {1,3,2,5,23,62,42,3},
            {3,6,23,6,34,24,6,6,23},
            {3,42,5,2,42,3,2,52,5,23}
        };

        for (auto arr : v) {
            cout << "Processing: {{";
            for (auto j : arr) cout << j << " ";
            cout << "} : ";

            countSort(arr, 10000);
            cout << "Sorted = {";
            for (auto j : arr) cout << j << " ";
            cout << "}" << endl;
        }
    }

    void countSort(vector<int>& v, int range)
    {
        vector<int> output;
        output.resize(v.size());
        int* count = new int[range];
        memset(count, 0, sizeof(int) * range); // init count of each element in this range
        for (int i = 0; i < v.size(); i++) count[v[i]]++; // increment count of each element

        for (int i = 1; i < range; i++) count[i] += count[i - 1]; // get additive count i.e. its position in range

        // place element at corect position
        for (int i = v.size() - 1; i >= 0; i--) {
            int elementCount = count[v[i]];
            int elementLastIndx = elementCount - 1;
            output[elementCount] = v[i];
            count[elementCount]--;
        }

        // fill the old array back
        for (int i = 0; i < v.size(); i++) v[i] = output[i];
    }
};