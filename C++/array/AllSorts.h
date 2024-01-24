#pragma once
#include "../header.h"
using namespace std;

class AllSorts
{
public:
    static void test()
    {
        CountSortIntegerArray::test();
        RadixSortIntegerArray::test();
    }

    class CountSortIntegerArray
    {
    public:
        static void test()
        {
            vector<vector<int>> v = {
                {1, 3, 2, 5, 23, 62, 42, 3},
                {3, 6, 23, 6, 34, 24, 6, 6, 23},
                {3, 42, 5, 2, 42, 3, 2, 52, 5, 23}};

            CountSortIntegerArray obj;
            for (auto arr : v)
            {
                cout << "Processing: {{";
                for (auto j : arr)
                    cout << j << " ";
                cout << "} : ";

                obj.countSort(arr, 10000);
                cout << "Sorted = {";
                for (auto j : arr)
                    cout << j << " ";
                cout << "}" << endl;
            }
        }

        void countSort(vector<int> &v, int range)
        {
            vector<int> output;
            output.resize(v.size());
            int *count = new int[range];
            memset(count, 0, sizeof(int) * range); // init count of each element in this range
            for (int i = 0; i < v.size(); i++)
                count[v[i]]++; // increment count of each element

            for (int i = 1; i < range; i++)
                count[i] += count[i - 1]; // get additive count i.e. its position in range

            // place element at corect position
            for (int i = v.size() - 1; i >= 0; i--)
            {
                int elementLastIndx = count[v[i]] - 1;
                output[elementLastIndx] = v[i];
                count[v[i]]--;
            }

            // fill the old array back
            for (int i = 0; i < v.size(); i++)
                v[i] = output[i];
        }
    };

    class RadixSortIntegerArray
    {
    public:
        static void test()
        {
            RadixSortIntegerArray obj;
            int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
            int n = sizeof(arr) / sizeof(int);

            cout << "Unordered arr: ";
            print(arr, n);

            obj.sort(arr, n);

            cout << "Ordered arr: ";
            print(arr, n);
        }

        void sort(int a[], int n)
        {
            for (int exp = 1;; exp *= 10)
            {
                bool res = countSort(a, n, 10, exp);
                if (!res)
                    break;
            }
        }

        bool countSort(int a[], int n, int r, int exp)
        {
            int *output = new int[n];
            int *count = new int[r];
            memset(count, 0, sizeof(int) * r);

            bool res = false;
            for (int i = 0; i < n; i++)
            {
                int v = a[i] / exp;
                count[v % 10]++;
                if (v != 0)
                {
                    res = true;
                }
            }
            if (!res)
                return res;

            for (int i = 1; i < r; i++)
                count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; i--)
            {
                int idx = (a[i] / exp) % 10;
                output[count[idx] - 1] = a[i];
                count[idx]--;
            }

            for (int i = 0; i < n; i++)
            {
                a[i] = output[i];
            }
            return true;
        }
    };
};