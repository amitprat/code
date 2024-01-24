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

and so on....

Finally you will yield the result.
*/

class Minheap {
    struct Node {
        int arrIndex;
        int arrPos;
        int elem;
        Node(int arrIndex, int arrPos, int elem) : arrIndex(arrIndex), arrPos(arrPos), elem(elem) {}
    };

   private:
    vector<Node> arr;
    int sz = 0;
    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
    int parent(int index) { return (index - 1) / 2; }

    void heapify(int index) {
        int smallestIndex = index;
        int l = left(index);
        int r = right(index);

        auto curNode = arr[index];
        if (l < sz && arr[l].elem < curNode.elem) smallestIndex = l;
        if (r < sz && arr[r].elem < curNode.elem) smallestIndex = r;

        if (smallestIndex != index) {
            swap(arr[smallestIndex], arr[index]);
            heapify(smallestIndex);
        }
    }

   public:
    void insert(int arrIndex, int arrPos, int elem) {
        arr.push_back({arrIndex, arrPos, elem});
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
};

class SmallestRange {
   public:
    static void test() {
        SmallestRange obj;

        {
            vector<vector<int>> input = {
                {4, 10, 15, 24, 26},
                {0, 9, 12, 20},
                {5, 18, 22, 30}};

            pair<int, int> res1 = obj.findRange(input);
            pair<int, int> res2 = obj.findRangeUsingSTL(input);
            pair<int, int> res3 = obj.findRangeUsingSTLOptimized(input);
            assert(res1 == res2);
            assert(res1 == res3);

            cout << format("Smallest range convering atleast one element from each list: {}", to_string(res1)) << endl;
        }

        {
            vector<vector<int>> input = {
                {4, 7, 9, 12, 15},
                {0, 8, 10, 14, 20},
                {6, 12, 16, 30, 50}};

            pair<int, int> res1 = obj.findRange(input);
            pair<int, int> res2 = obj.findRangeUsingSTL(input);
            pair<int, int> res3 = obj.findRangeUsingSTLOptimized(input);
            assert(res1 == res2);
            assert(res1 == res3);

            cout << format("Smallest range convering atleast one element from each list: {}", to_string(res1)) << endl;
        }

        {
            vector<vector<int>> input = {
                {4, 7},
                {1, 2},
                {20, 40}};

            pair<int, int> res1 = obj.findRange(input);
            pair<int, int> res2 = obj.findRangeUsingSTL(input);
            pair<int, int> res3 = obj.findRangeUsingSTLOptimized(input);
            assert(res1 == res2);
            assert(res1 == res3);

            cout << format("Smallest range convering atleast one element from each list: {}", to_string(res1)) << endl;
        }
    }

    pair<int, int> findRange(vector<vector<int>> input) {
        Minheap heap;
        pair<int, int> range = {INT_MAX, INT_MIN};

        pair<int, int> newRange = {INT_MAX, INT_MIN};
        for (int index = 0; index < input.size(); index++) {
            if (input[index].empty()) return range;  // if any of array is empty, no point of moving forward

            heap.insert(index, 0, input[index][0]);
            newRange.second = max(newRange.second, input[index][0]);
        }

        while (true) {
            auto node = heap.pop();
            newRange.first = node.elem;

            if (range.first == INT_MAX || newRange.second - newRange.first < range.second - range.first) {
                range = newRange;
            }

            node.arrPos++;
            if (node.arrPos >= input[node.arrIndex].size()) break;

            heap.insert(node.arrIndex, node.arrPos, input[node.arrIndex][node.arrPos]);
            newRange.second = max(newRange.second, input[node.arrIndex][node.arrPos]);
        }

        return range;
    }

   private:
    pair<int, int> findRangeUsingSTL(vector<vector<int>>& input) {
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

            if (indices[arrIdx] >= input[arrIdx].size())
                break;  // if any of array gets empty, no point of moving forward
            else {
                int next = input[arrIdx][indices[arrIdx]];
                minHeap.push({next, arrIdx});
            }
        }

        return range;
    }

    pair<int, int> getRange(vector<vector<int>> input, vector<int> indices) {
        int mn = INT_MAX, mx = INT_MIN;
        for (int j = 0; j < input.size(); j++) {
            if (input[j][indices[j]] < mn) mn = input[j][indices[j]];
            if (input[j][indices[j]] > mx) mx = input[j][indices[j]];
        }

        return {mn, mx};
    }

   private:
    pair<int, int> findRangeUsingSTLOptimized(vector<vector<int>>& arrs) {
        using p = pair<int, pair<int, int>>;
        using v = vector<pair<int, pair<int, int>>>;
        priority_queue<p, v, std::greater<p>> pq;

        int mn = INT_MAX, mx = INT_MIN;
        pair<int, int> result = {mn, mx};
        for (int i = 0; i < arrs.size(); i++) {
            pq.push({arrs[i][0], {i, 0}});
            mn = min(mn, arrs[i][0]);
            mx = max(mx, arrs[i][0]);
        }

        while (true) {
            auto f = pq.top();
            pq.pop();

            mn = f.first;  // this is smallest element of range
            if (mx - mn < result.second - result.first) {
                result = {mn, mx};
            }

            int arrIdx = f.second.first;
            int arrPos = f.second.second;
            if (arrPos + 1 < arrs[arrIdx].size()) {
                arrPos++;
                pq.push({arrs[arrIdx][arrPos], {arrIdx, arrPos}});

                mx = max(arrs[arrIdx][arrPos], mx);  // keep updating mx value always
            } else {
                // if any of the arrays end, exist it.
                break;
            }
        }

        return result;
    }
};