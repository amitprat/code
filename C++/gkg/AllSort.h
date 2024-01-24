#pragma once
#include "../Header.h"

class AllSort {
public:
    static void test() {
        AllSort obj;
        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.bubbleSort(arr);
            cout << "Bubble Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.selectionSort(arr);
            cout << "Selection Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.insertionSort(arr);
            cout << "Insertion Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.mergeSort(arr);
            cout << "Merge Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.quickSort(arr);
            cout << "Quick Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.countSort(arr);
            cout << "Count Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 3,4,5,1,3,6,2,3,6,2,7,2,8,2,3,0,7 };
            obj.heapSort(arr);
            cout << "Heap Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<string> arr = { "my","name","is","amit","pratap","singh" };
            obj.radixSort(arr);
            cout << "Radix Sort: ";
            cout << to_string(arr) << endl;
        }

        {
            vector<int> arr = { 10, 12, 20, 30, 25,40, 32, 31, 35, 50, 60 };
            auto res = obj.minLenghtUnsortedArr(arr);
            cout << "Min Length = " << to_string(res) << endl;
        }

        {
            LinkedListNode<int>* first = new LinkedListNode<int>(1);
            first->next = new LinkedListNode<int>(5);
            first->next->next = new LinkedListNode<int>(10);
            cout << "First Linked List: " << to_string(first) << endl;

            LinkedListNode<int>* second = new LinkedListNode<int>(0);
            second->next = new LinkedListNode<int>(2);
            second->next->next = new LinkedListNode<int>(4);
            second->next->next->next = new LinkedListNode<int>(9);
            second->next->next->next->next = new LinkedListNode<int>(10);
            second->next->next->next->next->next = new LinkedListNode<int>(20);
            cout << "Second Linked List: " << to_string(second) << endl;

            cout << "Merged Linked List: ";
            auto res = obj.merge(first, second);
            cout << to_string(res) << endl;
        }
    }

    void bubbleSort(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            bool swapped = false;
            for (int j = 0; j < arr.size() - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    void selectionSort(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            int mn = i;
            for (int j = i + 1; j < arr.size(); j++) {
                if (arr[j] < arr[mn]) mn = j;
            }

            if (mn != i) {
                swap(arr[mn], arr[i]);
            }
        }
    }

    void insertionSort(vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void mergeSort(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        vector<int> tmp(arr.size());

        mergeSort(arr, l, r, tmp);
    }

    void mergeSort(vector<int>& arr, int l, int r, vector<int>& tmp) {
        if (l < r) {
            int m = (l + r) / 2;
            mergeSort(arr, l, m, tmp);
            mergeSort(arr, m + 1, r, tmp);

            merge(arr, l, m, r, tmp);
        }
    }

    void merge(vector<int>& arr, int l, int m, int r, vector<int>& tmp) {
        int i = l, j = m + 1;
        int k = l;
        while (i <= m && j <= r) {
            if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
            else tmp[k++] = arr[j++];
        }

        while (i <= m) tmp[k++] = arr[i++];
        while (j <= r) tmp[k++] = arr[j++];

        k = l;
        while (k <= r) {
            arr[k] = tmp[k];
            k++;
        }
    }

    void quickSort(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        quickSort(arr, l, r);
    }

    int partition(vector<int>& arr, int l, int r) {
        int pivot = arr[r];
        int j = l;
        for (int i = l; i < r; i++) {
            if (arr[i] < pivot) {
                swap(arr[i], arr[j++]);
            }
        }
        swap(arr[j], arr[r]);

        return j;
    }

    void quickSort(vector<int>& arr, int l, int r) {
        if (l < r) {
            int p = partition(arr, l, r);
            quickSort(arr, l, p - 1);
            quickSort(arr, p + 1, r);
        }
    }

    void heapSort(vector<int>& arr) {

    }

    void countSort(vector<int>& arr) {
        int mx = max(arr);

        int* count = new int[mx + 1];
        memset(count, 0, sizeof(int) * (mx + 1));
        for (int i = 0; i < arr.size(); i++) {
            count[arr[i]]++;
        }

        for (int i = 1; i <= mx; i++) {
            count[i] += count[i - 1];
        }

        int* out = new int[arr.size()];
        for (int i = arr.size() - 1; i >= 0; i--) {
            out[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = out[i];
        }
    }

    void countSort(vector<int>& arr) {
        int mx = *max_element(arr.begin(), arr.end());
        int mn = *min_element(arr.begin(), arr.end());
        int range = mx - mn + 1;

        int* count = new int[range];
        memset(count, 0, sizeof(int) * range);
        for (int i = 0; i < arr.size(); i++) {
            count[arr[i]-mn]++;
        }

        for (int i = 1; i <= mx; i++) {
            count[i] += count[i - 1];
        }

        int* out = new int[arr.size()];
        for (int i = arr.size() - 1; i >= 0; i--) {
            out[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = out[i];
        }
    }

    void radixSort(vector<string>& arr) {

    }

    pair<int, int> minLenghtUnsortedArr(vector<int>& arr) {
        int n = arr.size();
        int i = 0, j = n - 1;

        while (i < n - 1 && arr[i] <= arr[i + 1]) i++;
        if (i == n - 1) return { 0,0 };

        while (j > 0 && arr[j] >= arr[j - 1]) j--;

        int mn = arr[i], mx = arr[j];
        for (int k = i + 1; k < j; k++) {
            mn = min(mn, arr[k]);
            mx = max(mx, arr[k]);
        }

        for (int k = 0; k < i; k++) {
            if (arr[k] > mn) {
                i = k;
                break;
            }
        }

        for (int k = n - 1; k >= 0; k--) {
            if (arr[k] < mx) {
                j = k;
                break;
            }
        }

        return { i,j };
    }

    LinkedListNode<int>* merge(LinkedListNode<int>* first, LinkedListNode<int>* second) {
        if (!first) return second;
        if (!second) return first;


        if (first->val <= second->val) {
            first->next = merge(first->next, second);
            return first;
        }
        else {
            second->next = merge(first, second->next);
            return second;
        }
    }
};