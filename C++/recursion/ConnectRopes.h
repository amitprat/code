#pragma once
#include "../Header.h"

class ConnectRopes {
private:
    template <class T>
    class Minheap {
    private:
        vector<T> dataset;
        int parent(int idx) { return (idx - 1) / 2; }
        int left(int idx) { return 2 * idx + 1; }
        int right(int idx) { return 2 * idx + 2; }
    public:
        void insert(T data) {
            dataset.push_back(data);
            int n = dataset.size();
            upHeapify(n - 1);
        }
        T top() {
            if (empty()) throw exception("Heap is empty");
            return dataset.front();
        }
        T pop() {
            if (empty()) throw exception("Heap is empty");
            auto ret = top();
            dataset[0] = dataset[size() - 1];
            dataset.pop_back();
            downHeapify(0);

            return ret;
        }
        int size() {
            return dataset.size();
        }
        bool empty() {
            if (size() == 0) return true;
            return false;
        }
    private:
        void upHeapify(int cur) {
            auto x = dataset[cur];
            auto p = parent(cur);
            while (cur > 0 && dataset[p] > dataset[cur]) {
                dataset[cur] = dataset[p];
                cur = p;
                p = parent(cur);
            }
            dataset[cur] = x;
        }
        void downHeapify(int cur) {
            int sm = cur;
            auto l = left(cur);
            if (l < size() && dataset[l] < dataset[sm]) sm = l;
            auto r = right(cur);
            if (r < size() && dataset[r] < dataset[sm]) sm = r;

            if (sm != cur) {
                swap(dataset[sm], dataset[cur]);
                downHeapify(sm);
            }
        }
    };
public:
    static void test() {
        ConnectRopes obj;
        vector<int> len = { 4, 3, 2, 6 };
        cout << "Total cost for connecting ropes is "
            << obj.minCost(len);
    }
    //4, 3, 2, 6 - [3+2 = 5+4 = 9 +6 = 15]
    // [4+3=7+2=9+6=15]

    int minCost(vector<int> len) {
        Minheap<int> heap;
        for (auto l : len) {
            heap.insert(l);
        }

        int totalcost = 0;
        while (heap.size() != 1) {
            auto top1 = heap.pop();
            auto top2 = heap.pop();
            totalcost += top1 + top2;
            heap.insert(top1 + top2);
        }

        return totalcost;
    }
};