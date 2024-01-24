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
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <algorithm>
#include <functional>
#include "PriorityQueue.h"
using namespace std;

class KthSmallestElementInSortedMatrix
{
private:
    class Node {
    public:
        int val;
        pair<int, int> pos;
        Node() {}
        Node(int val, pair<int, int> pos) :val(val), pos(pos) {}
    };

public:
    static void test() {
        KthSmallestElementInSortedMatrix obj;
        vector<vector<int>> matrix = {
            { 1, 5, 9},
            {10, 11, 13},
            {12, 13, 15}
        };
        int k = 8;
        auto res = obj.findkthsmallest(matrix, k);
        cout << "Kth smallest element: " << res << endl;
        assert(res == 13);
    }

    int findkthsmallest(vector<vector<int>>& matrix, int k) {
        auto comparator = [](const Node& a, const Node& b) {return a.val < b.val; };
        PriorityQueue<Node> pq(comparator);
        pq.add(Node(matrix[0][0], { 0,0 }));
        auto res = INT_MIN;
        while (!pq.empty() && k--) {
            auto cur = pq.pop();
            res = cur.val;
            if (cur.pos.first + 1 < matrix.size()) pq.add(Node(matrix[cur.pos.first + 1][cur.pos.second], { cur.pos.first + 1 , cur.pos.second }));
            if (cur.pos.second + 1 < matrix[0].size()) pq.add(Node(matrix[cur.pos.first][cur.pos.second + 1], { cur.pos.first, cur.pos.second + 1 }));
        }

        return res;
    }
};