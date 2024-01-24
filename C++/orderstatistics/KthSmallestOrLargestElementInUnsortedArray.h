#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

template <class T>
class Heap
{
public:
    enum class TYPE { MIN, MAX };

private:
    vector<T> v;
    TYPE type;
public:
    Heap(TYPE t, vector<T>& v) {
        type = t;
        for (auto i : v) {
            this->v.push_back(i);
        }

        for (int i = (v.size() - 1) / 2; i >= 0; i--) {
            heapify(i);
        }
    }

    T pop() {
        auto top = v[0];
        v[0] = v[v.size() - 1];
        v.pop_back();
        heapify(0);

        return top;
    }

    T top() { return v[0]; }

private:
    void heapify(int index) {
        int l = left(index);
        int r = right(index);
        int p = index;
        if (l < v.size() && compare(v, l, index)) {
            p = l;
        }
        if (r < v.size() && compare(v, r, p)) {
            p = r;
        }
        if (p != index) {
            swap(v[p], v[index]);
            heapify(p);
        }
    }

    bool compare(vector<int>& v, int x, int y) {
        if (type == TYPE::MAX) {
            return v[x] > v[y];
        }
        else {
            return v[x] < v[y];
        }
    }

    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
};
class KthSmallestOrLargestElement {
public:
    static void test() {
        KthSmallestOrLargestElement obj;
        {
            vector<int> v = { 12, 3, 5, 7, 19 };

            for (int k = 1; k <= v.size(); k++) {
                {
                    auto res_sort = obj.kthSmallestUsingSort(v, k);
                    //cout << k << "th smallest using sort = " << res << endl;
                    auto res_heap = obj.findKthSmallestMinHeap(v, k);
                    //cout << k << "th smallest element is = " << res << endl;
                    auto res_partition = obj.findKthSmallestPartitioning(v, k);
                    //cout << k << "th smallest element is = " << res << endl;
                    if (res_sort != res_heap || res_sort != res_partition) {
                        cout << "Mismatch: res_sort=" << res_sort << ", res_heap=" << res_heap << ", res_partition=" << res_partition << endl;
                    }
                    else {
                        cout << k << "th smallest element is = " << res_partition << endl;
                    }
                }

                {
                    auto res_sort = obj.kthLargestUsingSort(v, k);
                    //cout << k << "th largest using sort = " << res << endl;
                    auto res_heap = obj.findKthLargestMaxHeap(v, k);
                    //cout << k << "th largest element is = " << res << endl;
                    auto res_partition = obj.findKthLargestPartitioning(v, k);
                    //cout << k << "th largest element is = " << res << endl;
                    if (res_sort != res_heap || res_sort != res_partition) {
                        cout << "Mismatch: res_sort=" << res_sort << ", res_heap=" << res_heap << ", res_partition=" << res_partition << endl;
                    }
                    else {
                        cout << k << "th smallest element is = " << res_partition << endl;
                    }
                }
                cout << endl << endl;
            }
        }
    }

    int findKthSmallestMinHeap(vector<int>& v, int k) {
        Heap<int> heap(Heap<int>::TYPE::MIN, v);
        while (k-- > 1) {
            auto popped = heap.pop();
            //cout << "popped = " << popped << endl;
        }
        return heap.top();
    }

    int findKthLargestMaxHeap(vector<int>& v, int k) {
        Heap<int> heap(Heap<int>::TYPE::MAX, v);
        while (k-- > 1) {
            auto popped = heap.pop();
            //cout << "popped = " << popped << endl;
        }
        return heap.top();
    }

    int findKthSmallestPartitioning(vector<int>& v, int k) {
        return findKthSmallestPartitioningInterval(v, 0, v.size() - 1, k);
    }

    int findKthLargestPartitioning(vector<int>& v, int k) {
        return findKthLargestPartitioningInterval(v, 0, v.size() - 1, k);
    }

    int kthSmallestUsingSort(vector<int> v, int k) {
        sort(v.begin(), v.end(), [](const auto& i, const auto& j) {return i < j; });
        return v[k - 1];
    }

    int kthLargestUsingSort(vector<int> v, int k) {
        sort(v.begin(), v.end(), [&v](const auto& i, const auto& j) {return i > j; });
        return v[k - 1];
    }

private:
    int findKthSmallestPartitioningInterval(vector<int>& v, int l, int r, int k) {
        if (l <= r) {
            int p = partition(v, l, r);
            int q = p - l + 1;
            if (q == k) return v[p];
            else if (k < q) return findKthSmallestPartitioningInterval(v, l, p - 1, k);
            else return findKthSmallestPartitioningInterval(v, p + 1, r, k - q);
        }
    }

    int findKthLargestPartitioningInterval(vector<int>& v, int l, int r, int k) {
        if (l <= r) {
            int p = partition(v, l, r);
            int q = r - p + 1;
            if (q == k) return v[p];
            else if (k < q) return findKthLargestPartitioningInterval(v, p + 1, r, k);
            else return findKthLargestPartitioningInterval(v, l, p - 1, k - q);
        }
    }

    int partition(vector<int>& v, int l, int r) {
        int pivot = v[r];
        int i = l;
        for (int j = l; j < r; j++) {
            if (v[j] < pivot) {
                swap(v[i++], v[j]);
            }
        }
        swap(v[i], v[r]);
        return i;
    }
};