#pragma once
#include "../header.h"
#include "PriorityQueue.h"

class KthSmallestElementInSortedMatrix {
   private:
    class Node {
       public:
        int val;
        pair<int, int> pos;

        Node() {}
        Node(int val, pair<int, int> pos) : val(val), pos(pos) {}
    };

   public:
    static void test() {
        KthSmallestElementInSortedMatrix obj;
        vector<vector<int>> matrix = {
            {1, 5, 9},
            {10, 11, 13},
            {12, 13, 15}};
        int k = 8;
        auto res = obj.findkthsmallest(matrix, k);
        cout << "Kth smallest element: " << res << endl;
        assert(res == 13);
    }

    int findkthsmallest(vector<vector<int>>& matrix, int k) {
        auto comparator = [](const Node& a, const Node& b) { return a.val < b.val; };
        PriorityQueue<Node> pq(comparator);
        pq.insert(Node(matrix[0][0], {0, 0}));
        auto res = INT_MIN;
        while (!pq.empty() && k--) {
            auto cur = pq.pop();
            res = cur.val;
            if (cur.pos.first + 1 < matrix.size()) pq.insert(Node(matrix[cur.pos.first + 1][cur.pos.second], {cur.pos.first + 1, cur.pos.second}));
            if (cur.pos.second + 1 < matrix[0].size()) pq.insert(Node(matrix[cur.pos.first][cur.pos.second + 1], {cur.pos.first, cur.pos.second + 1}));
        }

        return res;
    }
};