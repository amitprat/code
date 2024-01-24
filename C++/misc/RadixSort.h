#pragma once
#include "../Header.h"
using namespace std;

class RadixSort
{
public:
    static void test()
    {
        RadixSort obj;

        {
            vector<vector<string>> inputs = {
                {"singh", "amit", "pratap"},
                {"hello", "world", "cpp"}
            };

            for (auto& input : inputs) {
                cout << "Sorting string list: " << to_string(input) << endl;

                obj.radixSort(input);
                cout << "Sorted string list: " << to_string(input) << endl;
            }
        }

        {
            vector<vector<int>> inputs = {
                {1,2,3,4,5},
                {5,4,3,2,1},
                {10,100,1000,10000},
                {1000,100,10,1},
                {},
                {1},
                {8},
                {10,8},
                {100,50,1},
                {1000,1}
            };

            for (auto& input : inputs) {
                cout << "Sorting string list: " << to_string(input) << endl;

                obj.radixSort(input);
                cout << "Sorted string list: " << to_string(input) << endl;
            }
        }
    }

    void radixSort(vector<string>& strlist)
    {
        int range = 256;
        int mxLength = 0;
        for (auto& str : strlist) mxLength = max(mxLength, (int)str.length());

        while (mxLength >= 1) {
            countSort(strlist, mxLength - 1, range);
            mxLength--;
        }
    }

    void countSort(vector<string>& v, int pos, int range)
    {
        vector<string> output;
        output.resize(v.size());

        int* count = new int[range];
        memset(count, 0, sizeof(int) * range); // init count of each element in this range

        for (int i = 0; i < v.size(); i++) {
            int index = 0;
            if (v[i].length() > pos) {
                index = v[i][pos];
            }
            count[index]++; // increment count of each element
        }

        for (int i = 1; i < range; i++) count[i] += count[i - 1]; // get additive count i.e. its position in range

        // place element at corect position
        for (int i = v.size() - 1; i >= 0; i--) {
            int index = 0;
            if (v[i].length() > pos) {
                index = v[i][pos];
            }

            int elementCount = count[index];
            int elementLastIndx = elementCount - 1;
            output[elementLastIndx] = v[i];
            count[index]--;
        }

        // fill the old array back
        for (int i = 0; i < v.size(); i++) v[i] = output[i];
    }

    void radixSort(vector<int>& arr) {
        for (int exp = 1;; exp *= 10) {
            if (!countSort(arr, 10, exp)) break;
        }
    }

    bool countSort(vector<int>& arr, int range, int exp) {
        vector<int> count(range, 0);
        vector<int> output(arr.size());

        bool processed = false;
        for (auto e : arr) {
            count[(e / exp) % 10]++;
            if ((e / exp) != 0) processed = true;
        }

        if (!processed) return processed;

        for (int i = 1; i < range; i++) count[i] += count[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--) {
            int e = arr[i];
            int idx = count[(e / exp) % 10];
            output[idx - 1] = arr[i];
            count[(e / exp) % 10]--;
        }

        arr = output;

        return processed;
    }
};