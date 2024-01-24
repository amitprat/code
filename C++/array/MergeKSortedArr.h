#pragma once
#include "../header.h"

class MergeKSortedArr {
    template <class T, class C>
    class PriorityQueue {
       private:
        vector<T> container;
        C comparator;
        int capacity;

       public:
        PriorityQueue(C comparator, int capacity) : comparator(comparator), capacity(capacity) {}
        void push(T item) {
            container.push_back(item);

            upHeapify(container.size() - 1);
        }
        T top() {
            if (container.empty()) throw exception("Empty");
            return container.front();
        }
        T pop() {
            if (container.empty()) throw exception("Empty");
            auto item = container[0];
            container[0] = container[container.size() - 1];
            container.pop_back();

            downHeapify(0);

            return item;
        }
        bool isFull() {
            return container.size() == capacity;
        }
        bool empty() {
            return container.empty();
        }

       private:
        void upHeapify(int idx) {
            auto p = parent(idx);
            while (idx > 0 && container[p] > container[idx]) {
                swap(container[p], container[idx]);
                idx = p;
                p = parent(idx);
            }
        }
        void downHeapify(int idx) {
            int sm = idx;
            int l = left(idx);
            if (l < container.size() && container[l] < container[idx]) sm = l;

            int r = right(idx);
            if (r < container.size() && container[r] < container[idx]) sm = r;

            if (sm != idx) {
                swap(container[idx], container[sm]);
                downHeapify(sm);
            }
        }

        int left(int i) { return 2 * i + 1; }

        int right(int i) { return 2 * i + 2; }

        int parent(int i) { return (i - 1) / 2; }
    };

   public:
    static void test() {
        MergeKSortedArr obj;

        vector<vector<int>> arr =
            {
                {2, 6, 12, 34},
                {1, 9, 20, 1000},
                {23, 34, 90, 2000}};
        cout << "Original Arrays:" << to_string(arr) << endl;

        int k = 3;
        vector<int> output = obj.merge(arr, k);
        cout << "Merged array is " << to_string(output) << endl;

        Solution sol;
        auto res = sol.mergeKSortedArrays(arr);
        cout << to_string(res) << endl;
    }

    vector<int> merge(vector<vector<int>>& arrs, int k) {
        auto Comparator = [](auto f, auto s) { return f < s; };
        PriorityQueue<int, decltype(Comparator)> pq(Comparator, k);
        vector<int> result;

        for (int i = 0;; i++) {
            bool processed = false;
            for (auto& arr : arrs) {
                if (i < arr.size()) {
                    processed = true;
                    if (pq.isFull()) {
                        result.push_back(pq.pop());
                    }
                    pq.push(arr[i]);
                }
            }
            if (processed == false) break;
        }

        while (!pq.empty()) {
            result.push_back(pq.pop());
        }

        return result;
    }

    class Solution {
       public:
        using Node = tuple<int, int, int>;
        struct Compare {
            bool operator()(Node& f, Node& s) {
                return get<0>(f) > get<0>(s);
            }
        };

        vector<int> mergeKSortedArrays(vector<vector<int>>& arrays) {
            priority_queue<Node, vector<Node>, Compare> pq;

            int i = 0;
            for (auto& arr : arrays) {
                if (arr.size() > 0) pq.push({arr[0], i, 0});
                i++;
            }

            vector<int> result;
            while (!pq.empty()) {
                auto elem = pq.top();
                pq.pop();
                result.push_back(get<0>(elem));

                int arrIndex = get<1>(elem), pos = get<2>(elem);
                if (pos + 1 < arrays[arrIndex].size()) {
                    pq.push({arrays[arrIndex][pos + 1], arrIndex, pos + 1});
                }
            }

            return result;
        }
    };
};