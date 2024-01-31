#pragma once
#include "../header.h"

class AllSort
{
public:
    static void test()
    {
        AllSort obj;

        vector<vector<int>> inputs = {
            {1, 3, 2, 5, 23, 62, 42, 3},
            {3, 6, 23, 6, 34, 24, 6, 6, 23},
            {3, 42, 5, 2, 42, 3, 2, 52, 5, 23},
            {3, 4, 5, 1, 3, 6, 2, 3, 6, 2, 7, 2, 8, 2, 3, 0, 7}};

        for (const auto &input : inputs)
        {
            cout << "Input array: " << input << endl;

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.bubbleSort(input_copy);
                cout << "Sorted array using bubble sort: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.selectionSort(input_copy);
                cout << "Sorted array using selection sort: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.insertionSort(input_copy);
                cout << "Sorted array using insertion sort: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.mergeSort(input_copy);
                cout << "Sorted array using merge sort: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.quickSort(input_copy);
                cout << "Sorted array using quick sort: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.heapSort(input_copy);
                cout << "Sorted array using heap sort: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.countSort1(input_copy);
                cout << "Sorted array using count sort1: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.countSort2(input_copy);
                cout << "Sorted array using count sort2: " << input_copy << endl;
            }

            {
                vector<int> input_copy(input.begin(), input.end());
                obj.radixSort(input_copy);
                cout << "Sorted array using radix sort: " << input_copy << endl;
            }

            cout << endl;
        }

        {
            vector<vector<string>> strs = {
                {"amit", "pratap", "singh"},
                {"hello", "world", "cpp"},
                {"my", "name", "is", "amit", "pratap", "singh"}};

            for (auto &str : strs)
            {
                obj.radixSort(str);
                cout << "Sorted strings using radix sort: " << str << endl;
            }

            cout << endl;
        }

        {
            vector<int> arr = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
            auto res = obj.minLenghtUnsortedArr(arr);
            cout << "Min Length = " << to_string(res) << endl;
        }

        {
            ListNode *first = new ListNode(1);
            first->next = new ListNode(5);
            first->next->next = new ListNode(10);
            cout << "First Linked List: " << first->to_string() << endl;

            ListNode *second = new ListNode(0);
            second->next = new ListNode(2);
            second->next->next = new ListNode(4);
            second->next->next->next = new ListNode(9);
            second->next->next->next->next = new ListNode(10);
            second->next->next->next->next->next = new ListNode(20);
            cout << "Second Linked List: " << second->to_string() << endl;

            cout << "Merged Linked List: ";
            auto result = obj.mergeSortedLinkedList(first, second);
            cout << result->to_string() << endl;
        }
    }

public:
    void bubbleSort(vector<int> &arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            bool swapped = false;
            for (int j = 0; j < arr.size() - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }

public:
    void selectionSort(vector<int> &arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            int mn = i;
            for (int j = i + 1; j < arr.size(); j++)
            {
                if (arr[j] < arr[mn])
                    mn = j;
            }

            if (mn != i)
            {
                swap(arr[mn], arr[i]);
            }
        }
    }

public:
    void insertionSort(vector<int> &arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

public:
    void mergeSort(vector<int> &arr)
    {
        int l = 0, r = arr.size() - 1;
        vector<int> tmp(arr.size());

        mergeSort(arr, l, r, tmp);
    }

    void mergeSort(vector<int> &arr, int l, int r, vector<int> &tmp)
    {
        if (l < r)
        {
            int m = (l + r) / 2;
            mergeSort(arr, l, m, tmp);
            mergeSort(arr, m + 1, r, tmp);

            merge(arr, l, m, r, tmp);
        }
    }

    void merge(vector<int> &arr, int l, int m, int r, vector<int> &tmp)
    {
        int i = l, j = m + 1;
        int k = l;
        while (i <= m && j <= r)
        {
            if (arr[i] <= arr[j])
                tmp[k++] = arr[i++];
            else
                tmp[k++] = arr[j++];
        }

        while (i <= m)
            tmp[k++] = arr[i++];
        while (j <= r)
            tmp[k++] = arr[j++];

        k = l;
        while (k <= r)
        {
            arr[k] = tmp[k];
            k++;
        }
    }

public:
    void quickSort(vector<int> &arr)
    {
        int l = 0, r = arr.size() - 1;
        quickSort(arr, l, r);
    }

    void quickSort(vector<int> &arr, int l, int r)
    {
        if (l < r)
        {
            int p = partition(arr, l, r);
            quickSort(arr, l, p - 1);
            quickSort(arr, p + 1, r);
        }
    }

    int partition(vector<int> &arr, int l, int r)
    {
        int pivot = arr[r];
        int j = l;
        for (int i = l; i < r; i++)
        {
            if (arr[i] < pivot)
            {
                swap(arr[i], arr[j++]);
            }
        }
        swap(arr[j], arr[r]);

        return j;
    }

public:
    void heapSort(vector<int> &arr)
    {
        this->buildHeap(arr);

        for (int i = arr.size(); i > 0; i--)
        {
            swap(arr[0], arr[i - 1]);

            this->heapify(arr, i - 1, 0);
        }
    }

    void buildHeap(vector<int> &arr)
    {
        for (int i = (arr.size() - 1) / 2; i >= 0; i--)
        {
            this->heapify(arr, arr.size(), i);
        }
    }

    void heapify(vector<int> &arr, int n, int i)
    {
        int l = left(i);
        int r = right(i);

        int mx = i;
        if (l < n && arr[l] > arr[mx])
            mx = l;
        if (r < n && arr[r] > arr[mx])
            mx = r;

        if (mx != i)
        {
            swap(arr[i], arr[mx]);
            heapify(arr, n, mx);
        }
    }

    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
    int parent(int index) { return (index - 1) / 2; }

public:
    void countSort1(vector<int> &arr)
    {
        int mx = *std::max_element(arr.begin(), arr.end());

        int *count = new int[mx + 1];
        memset(count, 0, sizeof(int) * (mx + 1));
        for (int i = 0; i < arr.size(); i++)
        {
            count[arr[i]]++;
        }

        for (int i = 1; i <= mx; i++)
        {
            count[i] += count[i - 1];
        }

        int *out = new int[arr.size()];
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            out[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < arr.size(); i++)
        {
            arr[i] = out[i];
        }
    }

    void countSort2(vector<int> &arr)
    {
        int mx = *max_element(arr.begin(), arr.end());
        int mn = *min_element(arr.begin(), arr.end());

        int range = mx - mn + 1;

        vector<int> count(range, 0);
        for (int i = 0; i < arr.size(); i++)
        {
            count[arr[i] - mn]++;
        }

        for (int i = 1; i < range; i++)
        {
            count[i] += count[i - 1];
        }

        vector<int> out(arr.size());
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            out[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < arr.size(); i++)
        {
            arr[i] = out[i];
        }
    }

    void countSort3(vector<int> &v, int range)
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

private:
    void radixSort(vector<int> &arr)
    {
        int n = arr.size();
        for (int exp = 1;; exp *= 10)
        {
            bool res = countSort(arr, n, 10, exp);
            if (!res)
                break;
        }
    }

    bool countSort(vector<int> &arr, int n, int r, int exp)
    {
        int *output = new int[n];
        int *count = new int[r];
        memset(count, 0, sizeof(int) * r);

        bool res = false;
        for (int i = 0; i < n; i++)
        {
            int v = arr[i] / exp;
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
            int idx = (arr[i] / exp) % 10;
            output[count[idx] - 1] = arr[i];
            count[idx]--;
        }

        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }

        return true;
    }

private:
    void radixSort(vector<string> &strlist)
    {
        int range = 256;

        int mxLength = 0;
        for (const auto &str : strlist)
            mxLength = max(mxLength, (int)str.length());

        while (mxLength >= 1)
        {
            countSort(strlist, mxLength - 1, range);
            mxLength--;
        }
    }

    void countSort(vector<string> &v, int pos, int range)
    {
        vector<string> output;
        output.resize(v.size());

        int *count = new int[range];
        memset(count, 0, sizeof(int) * range); // init count of each element in this range

        for (int i = 0; i < v.size(); i++)
        {
            int index = 0;
            if (v[i].length() > pos)
            {
                index = v[i][pos];
            }
            count[index]++; // increment count of each element
        }

        for (int i = 1; i < range; i++)
            count[i] += count[i - 1]; // get additive count i.e. its position in range

        // place element at corect position
        for (int i = v.size() - 1; i >= 0; i--)
        {
            int index = 0;
            if (v[i].length() > pos)
            {
                index = v[i][pos];
            }
            int elementCount = count[index];
            int elementLastIndx = elementCount - 1;
            output[elementLastIndx] = v[i];
            count[index]--;
        }

        // fill the old array back
        for (int i = 0; i < v.size(); i++)
            v[i] = output[i];
    }

private:
    pair<int, int> minLenghtUnsortedArr(vector<int> &arr)
    {
        int n = arr.size();
        int i = 0, j = n - 1;

        while (i < n - 1 && arr[i] <= arr[i + 1])
            i++;
        if (i == n - 1)
            return {0, 0};

        while (j > 0 && arr[j] >= arr[j - 1])
            j--;

        int mn = arr[i], mx = arr[j];
        for (int k = i + 1; k < j; k++)
        {
            mn = min(mn, arr[k]);
            mx = max(mx, arr[k]);
        }

        for (int k = 0; k < i; k++)
        {
            if (arr[k] > mn)
            {
                i = k;
                break;
            }
        }

        for (int k = n - 1; k >= 0; k--)
        {
            if (arr[k] < mx)
            {
                j = k;
                break;
            }
        }

        return {i, j};
    }

private:
    ListNode *mergeSortedLinkedList(ListNode *first, ListNode *second)
    {
        if (!first)
            return second;
        if (!second)
            return first;

        if (first->val <= second->val)
        {
            first->next = mergeSortedLinkedList(first->next, second);
            return first;
        }
        else
        {
            second->next = mergeSortedLinkedList(first, second->next);
            return second;
        }
    }
};