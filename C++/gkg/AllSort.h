#pragma once
#include "../header.h"

class AllSort {
   public:
    static void test() {
        AllSort obj;

        auto testCase = [](const vector<int> &input) {
            vector<int> ref = input;
            sort(ref.begin(), ref.end());

            auto runSortTest = [&](const function<void(vector<int> &)> &sortFunc, string name) {
                vector<int> arr = input;
                sortFunc(arr);
                assert(arr == ref && (cout << name << " passed\n"));
            };

            runSortTest(AllSort::bubbleSort, "BubbleSort");
            runSortTest(AllSort::selectionSort, "SelectionSort");
            runSortTest(AllSort::insertionSort, "InsertionSort");
            runSortTest(AllSort::mergeSort, "MergeSort");
            runSortTest(AllSort::quickSort, "QuickSort");
            runSortTest(AllSort::heapSort, "HeapSort");
            runSortTest(AllSort::countSort1, "CountSort");
        };

        testCase({5, 2, 9, 1, 5, 6});
        testCase({3, 0, -2, 1, 3, 3});
        testCase({1});
        testCase({});
        testCase({10, 10, 10});

        vector<vector<int>> inputs = {
            {1, 3, 2, 5, 23, 62, 42, 3},
            {3, 6, 23, 6, 34, 24, 6, 6, 23},
            {3, 42, 5, 2, 42, 3, 2, 52, 5, 23},
            {3, 4, 5, 1, 3, 6, 2, 3, 6, 2, 7, 2, 8, 2, 3, 0, 7}};

        for (const auto &input : inputs) {
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

            for (auto &str : strs) {
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
            using ListNode = LinkedList<int>::Node;
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
    static void bubbleSort(vector<int> &arr) {
        for (size_t i = 0; i < arr.size(); ++i) {
            bool swapped = false;
            for (size_t j = 0; j < arr.size() - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

   public:
    static void selectionSort(vector<int> &arr) {
        for (size_t i = 0; i < arr.size(); ++i) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < arr.size(); ++j) {
                if (arr[j] < arr[minIdx]) minIdx = j;
            }
            if (minIdx != i) swap(arr[minIdx], arr[i]);
        }
    }

   public:
    static void insertionSort(vector<int> &arr) {
        for (size_t i = 1; i < arr.size(); ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

   public:
    static void mergeSort(vector<int> &arr) {
        vector<int> tmp(arr.size());
        mergeSortHelper(arr, 0, arr.size() - 1, tmp);
    }

   private:
    static void mergeSortHelper(vector<int> &arr, int left, int right, vector<int> &tmp) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, tmp);
        mergeSortHelper(arr, mid + 1, right, tmp);
        merge(arr, left, mid, right, tmp);
    }

    static void merge(vector<int> &arr, int l, int m, int r, vector<int> &tmp) {
        int i = l, j = m + 1, k = l;
        while (i <= m && j <= r) {
            if (arr[i] <= arr[j])
                tmp[k++] = arr[i++];
            else
                tmp[k++] = arr[j++];
        }
        while (i <= m) tmp[k++] = arr[i++];
        while (j <= r) tmp[k++] = arr[j++];
        for (int p = l; p <= r; ++p) arr[p] = tmp[p];
    }

   public:
    static void quickSort(vector<int> &arr) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }

   private:
    static void quickSortHelper(vector<int> &arr, int l, int r) {
        if (l >= r) return;

        int p = partition(arr, l, r);
        quickSortHelper(arr, l, p - 1);
        quickSortHelper(arr, p + 1, r);
    }

    static int partition(vector<int> &arr, int l, int r) {
        int pivot = arr[r];
        int p = l;
        for (int j = l; j < r; ++j) {
            if (arr[j] < pivot) swap(arr[p++], arr[j]);
        }
        swap(arr[p], arr[r]);

        return p;
    }

   public:
    static void heapSort(vector<int> &arr) {
        buildHeap(arr);
        for (int i = arr.size() - 1; i > 0; --i) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    static void buildHeap(vector<int> &arr) {
        for (int i = arr.size() / 2 - 1; i >= 0; --i) heapify(arr, arr.size(), i);
    }

    static void heapify(vector<int> &arr, int n, int i) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest]) largest = l;
        if (r < n && arr[r] > arr[largest]) largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

   public:
    static void countSort1(vector<int> &arr) {
        int mx = *std::max_element(arr.begin(), arr.end());

        int *count = new int[mx + 1];
        memset(count, 0, sizeof(int) * (mx + 1));
        for (const auto &e : arr) count[e]++;

        for (int i = 1; i <= mx; i++) count[i] += count[i - 1];

        int *out = new int[arr.size()];
        for (int i = arr.size() - 1; i >= 0; i--) {
            out[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = out[i];
        }
    }

    static void countSort2(vector<int> &arr) {
        int mx = *max_element(arr.begin(), arr.end());
        int mn = *min_element(arr.begin(), arr.end());

        int range = mx - mn + 1;

        vector<int> count(range, 0);
        for (const auto &e : arr) {
            count[e - mn]++;
        }

        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        vector<int> out(arr.size());
        for (int i = arr.size() - 1; i >= 0; i--) {
            out[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = out[i];
        }
    }

    static void countSort3(vector<int> &v, int range) {
        vector<int> output;
        output.resize(v.size());

        int *count = new int[range];
        memset(count, 0, sizeof(int) * range);  // init count of each element in this range
        for (int i = 0; i < v.size(); i++)
            count[v[i]]++;  // increment count of each element

        for (int i = 1; i < range; i++)
            count[i] += count[i - 1];  // get additive count i.e. its position in range

        // place element at corect position
        for (int i = v.size() - 1; i >= 0; i--) {
            int elementLastIndx = count[v[i]] - 1;
            output[elementLastIndx] = v[i];
            count[v[i]]--;
        }

        // fill the old array back
        for (int i = 0; i < v.size(); i++)
            v[i] = output[i];
    }

   private:
    void radixSort(vector<int> &arr) {
        int n = arr.size();
        for (int exp = 1;; exp *= 10) {
            bool res = countSort(arr, n, 10, exp);
            if (!res) break;
        }
    }

    bool countSort(vector<int> &arr, int n, int r, int exp) {
        int *output = new int[n];
        int *count = new int[r];
        memset(count, 0, sizeof(int) * r);

        bool res = false;
        for (int i = 0; i < n; i++) {
            int v = arr[i] / exp;
            count[v % 10]++;
            if (v != 0) {
                res = true;
            }
        }
        if (!res) return res;

        for (int i = 1; i < r; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int idx = (arr[i] / exp) % 10;
            output[count[idx] - 1] = arr[i];
            count[idx]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        return true;
    }

   private:
    void radixSort(vector<string> &strlist) {
        int range = 256;

        int mxLength = 0;
        for (const auto &str : strlist)
            mxLength = max(mxLength, (int)str.length());

        while (mxLength >= 1) {
            countSort(strlist, mxLength - 1, range);
            mxLength--;
        }
    }

    void countSort(vector<string> &v, int pos, int range) {
        vector<string> output;
        output.resize(v.size());

        int *count = new int[range];
        memset(count, 0, sizeof(int) * range);  // init count of each element in this range

        for (int i = 0; i < v.size(); i++) {
            int index = 0;
            if (v[i].length() > pos) {
                index = v[i][pos];
            }
            count[index]++;  // increment count of each element
        }

        for (int i = 1; i < range; i++)
            count[i] += count[i - 1];  // get additive count i.e. its position in range

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
        for (int i = 0; i < v.size(); i++)
            v[i] = output[i];
    }

   private:
    pair<int, int> minLenghtUnsortedArr(vector<int> &arr) {
        int n = arr.size();
        int i = 0, j = n - 1;

        while (i < n - 1 && arr[i] <= arr[i + 1]) i++;
        if (i == n - 1) return {0, 0};

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

        return {i, j};
    }

   private:
    LinkedList<int>::Node *mergeSortedLinkedList(LinkedList<int>::Node *first, LinkedList<int>::Node *second) {
        if (!first) return second;
        if (!second) return first;

        if (first->val <= second->val) {
            first->next = mergeSortedLinkedList(first->next, second);
            return first;
        } else {
            second->next = mergeSortedLinkedList(first, second->next);
            return second;
        }
    }
};