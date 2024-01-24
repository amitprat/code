#include "../header.h"

/*
https://careercup.com/question?id=5201559730257920

Give you an array which has n integers,it has both positive and negative integers.Now you need sort this array in a special way.After that,the negative integers should in the front,and the positive integers should in the back.Also the relative position should not be changed.
eg. -1 1 3 -2 2 ans: -1 -2 1 3 2.
o(n)time complexity and o(1) space complexity is perfect.
*/
class RearrangePositiveNegativeNumbers
{
public:
    static void test()
    {
        RearrangePositiveNegativeNumbers obj;
        vector<vector<int>> arrs =
            {
                {5, 5, -3, 4, -8, 0, -7, 3, -9, -3, 9, -2, 1},
                {-1, 1, 3, -2, 2}};
        for (auto &arr : arrs)
        {
            cout << "Original array: " << arr << endl;
            obj.rearrageUsingMergeSort(arr);
            cout << "Output array: " << arr << endl;
        }
    }

private:
    vector<int> rearrangeUsingExtraSpace(vector<int> &arr)
    {
        int posIndex = 0;
        vector<int> output(arr.size());
        for (auto &i : arr)
        {
            if (i < 0)
                posIndex++;
        }

        int negIndex = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] < 0)
                output[negIndex++] = arr[i];
            else
                output[posIndex++] = arr[i];
        }

        return output;
    }

private:
    void rearrangeUsingInsertionSort(vector<int> &arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            // if current element is posite, then continue
            if (arr[i] >= 0)
                continue;

            // if current number is negative, then shift element to right
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] >= 0)
            {
                arr[j + 1] = arr[j];
                j--;
            }

            // place the negative value at correct place
            arr[j + 1] = key;
        }
    }

private:
    void rearrageUsingMergeSort(vector<int> &arr)
    {
        int r = arr.size() - 1;
        rearrageUsingMergeSort(arr, 0, r);
    }
    void rearrageUsingMergeSort(vector<int> &arr, int l, int r)
    {
        if (l < r)
        {
            int m = (l + r) / 2;
            rearrageUsingMergeSort(arr, l, m);
            rearrageUsingMergeSort(arr, m + 1, r);

            merge(arr, l, m, r);
        }
    }

    void merge(vector<int> &arr, int l, int m, int r)
    {
        int i = l, j = m + 1;
        while (i <= m && arr[i] < 0)
            i++;
        while (j <= r && arr[i] >= 0)
            j++;

        reverse(arr, i, m);
        reverse(arr, m + 1, j - 1);
        reverse(arr, i, j - 1);
    }

    void reverse(vector<int> &arr, int l, int r)
    {
        while (l < r)
        {
            swap(arr[l++], arr[r--]);
        }
    }
};