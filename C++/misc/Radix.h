#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class RadixSort
{
public:
    void test()
    {
        vector<vector<string>> v = {
            {"amit", "pratap", "singh"},
            {"hello", "world", "cpp"}
        };

        for (auto strlist : v) {
            cout << "Sorting: ";
            for (auto str : strlist)
                cout << str << " ";
            cout << " :: ";

            radixSort(strlist);
            for (auto str : strlist)
                cout << str << " ";
            cout << endl;
        }
    }

    void radixSort(vector<string>& strlist)
    {
        int range = 256;
        int mxLength = 0;
        for (auto str : strlist) mxLength = max(mxLength, (int)str.length());

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
};