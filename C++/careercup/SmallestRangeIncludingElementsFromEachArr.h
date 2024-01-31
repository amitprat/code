#pragma once
#include "../Header.h"
/*
You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists.
For example,
List 1: [4, 10, 15, 24, 26]
List 2: [0, 9, 12, 20]
List 3: [5, 18, 22, 30]
The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.

Solution:
Min heap of size 3. containing 1 element of each list
Heap [0, 4, 5]
Range - 6

Remove 0 and add 9
Heap [4, 9, 5]
Range - 6

Remove 4 and add 10
Heap [5, 9, 10]
Range - 6
*/
template <class K, class V>
class Minheap {
    struct Node {
        K key;
        V val;
        Node(K key, V val) : key(key), val(val) {}
    };

   private:
    vector<Node> arr;
    int sz = 0;

    void heapify(int index) {
        int smallestIndex = index;
        int l = left(index);
        int r = right(index);

        auto curNode = arr[index];
        if (l < sz && arr[l].key < curNode.key) smallestIndex = l;
        if (r < sz && arr[r].key < curNode.key) smallestIndex = r;

        if (smallestIndex != index) {
            swap(arr[smallestIndex], arr[index]);
            heapify(smallestIndex);
        }
    }

   public:
    void insert(K key, V val) {
        arr.push_back({key, val});
        sz++;
        heapify(0);
    }

    Node pop() {
        auto node = arr[0];
        arr[0] = arr[sz - 1];
        sz--;
        arr.pop_back();

        heapify(0);

        return node;
    }

   private:
    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
    int parent(int index) { return (index - 1) / 2; }
};

class SmallestRangeIncludingElementsFromEachArr {
   public:
    static void test() {
        SmallestRangeIncludingElementsFromEachArr obj;
        vector<vector<vector<int>>> inputs = {
            // first input
            {{4, 10, 15, 24, 26},
             {0, 9, 12, 20},
             {5, 18, 22, 30}},
            // second input
            {{4, 7, 9, 12, 15},
             {0, 8, 10, 14, 20},
             {6, 12, 16, 30, 50}},
            // third input
            {{4, 7},
             {1, 2},
             {20, 40}}};
        for (const auto& input : inputs) {
            pair<int, int> res1 = obj.findRange(input);
            pair<int, int> res2 = obj.findRangeUsingSTL(input);
            pair<int, int> res3 = obj.findRangeUsingSTLOptimized(input);
            assert(res1 == res2);
            assert(res1 == res3);

            cout << format("Smallest range convering atleast one element from each list: {}", to_string(res1)) << endl;
        }
    }

   private:
    // Using own implement minheap
    pair<int, int> findRange(const vector<vector<int>>& input) {
        Minheap<int, pair<int, int>> heap;
        pair<int, int> range = {INT_MAX, INT_MIN};

        pair<int, int> newRange = {INT_MAX, INT_MIN};
        int maxSoFar = INT_MIN;
        for (int index = 0; index < input.size(); index++) {
            if (input[index].empty()) return range;  // if any of array is empty, no point of moving forward

            heap.insert(input[index][0], {index, 0});
            maxSoFar = max(newRange.second, input[index][0]);
        }

        while (true) {
            auto node = heap.pop();
            auto elem = node.key;
            auto arrIdx = node.val.first;
            auto arrPos = node.val.second;

            newRange = {elem, maxSoFar};  // {min, max}
            if (range.first == INT_MAX || newRange.second - newRange.first < range.second - range.first) {
                range = newRange;
            }

            arrPos++;
            if (arrPos >= input[arrIdx].size()) break;

            auto newval = input[arrIdx][arrPos];
            heap.insert(newval, {arrIdx, arrPos});
            maxSoFar = max(maxSoFar, newval);  // update new max
        }

        return range;
    }

   private:
    pair<int, int> findRangeUsingSTL(const vector<vector<int>>& input) {
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> minHeap;
        pair<int, int> range = {INT_MAX, INT_MIN};
        vector<int> indices;

        // insert first element of each array
        for (int index = 0; index < input.size(); index++) {
            if (input[index].empty()) return range;  // if any of array is empty, no point of moving forward

            minHeap.push({input[index][0], index});
            indices.push_back(0);
        }

        while (true) {
            auto elem = minHeap.top();
            minHeap.pop();
            int arrIdx = elem.second;

            auto newRange = getRange(input, indices);
            if (range.first == INT_MAX || newRange.second - newRange.first < range.second - range.first) {
                range = newRange;
            }

            indices[arrIdx]++;  // consider next element

            if (indices[arrIdx] >= input[arrIdx].size()) {
                break;  // if any of array gets empty, no point of moving forward
            } else {
                int nextElem = input[arrIdx][indices[arrIdx]];
                minHeap.push({nextElem, arrIdx});
            }
        }

        return range;
    }

    pair<int, int> getRange(const vector<vector<int>>& input, const vector<int>& indices) {
        int mn = INT_MAX, mx = INT_MIN;
        for (int arrIdx = 0; arrIdx < input.size(); arrIdx++) {
            int pos = indices[arrIdx];

            if (input[arrIdx][pos] < mn) mn = input[arrIdx][pos];
            if (input[arrIdx][pos] > mx) mx = input[arrIdx][pos];
        }

        return {mn, mx};
    }

   private:
    pair<int, int> findRangeUsingSTLOptimized(const vector<vector<int>>& arrs) {
        using p = pair<int, pair<int, int>>;
        using v = vector<pair<int, pair<int, int>>>;
        priority_queue<p, v, std::greater<p>> pq;  // minheap

        int mn = INT_MAX, mx = INT_MIN;
        pair<int, int> result = {mn, mx};
        for (int i = 0; i < arrs.size(); i++) {
            pq.push({arrs[i][0], {i, 0}});  // insert first element of each array
            mn = min(mn, arrs[i][0]);
            mx = max(mx, arrs[i][0]);
        }

        while (true) {
            auto f = pq.top();
            pq.pop();

            auto elem = f.first;

            mn = elem;  // this is smallest element of range
            if (result.first == INT_MAX || mx - mn < result.second - result.first) {
                result = {mn, mx};
            }

            int arrIdx = f.second.first;
            int arrPos = f.second.second;
            if (arrPos + 1 < arrs[arrIdx].size()) {
                arrPos++;
                pq.push({arrs[arrIdx][arrPos], {arrIdx, arrPos}});
                mx = max(mx, arrs[arrIdx][arrPos]);
            } else {
                // if any of the arrays end, exist it.
                break;
            }
        }

        return result;
    }
};