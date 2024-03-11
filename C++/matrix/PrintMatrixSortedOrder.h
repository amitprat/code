#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=6335704

Given a N*N Matrix.
All rows are sorted, and all columns are sorted.
Find the Kth Largest element of the matrix.
*/
class PrintMatrixSortedOrder {
   private:
    static const int N = 4;
    static const int M = 4;

   public:
    using Point = pair<int, int>;
    static void test() {
        PrintMatrixSortedOrder obj;
        int mat[N][N] = {
            {10, 20, 30, 40},
            {15, 25, 35, 45},
            {27, 29, 37, 48},
            {32, 33, 39, 50},
        };

        obj.printSorted(mat);
        cout << endl;

        auto res = obj.printSortedUsingMinheap2(mat);
        cout << "Matrix in sorted order : " << res << endl;
    }

   private:
    void printSorted(int mat[][M]) {
        int indices[N] = {0};
        int cnt = 0;
        while (cnt < N * M) {
            Point p = getMinIndex(indices, mat);
            cout << mat[p.first][p.second] << " ";
            cnt++;
        }
    }

    Point getMinIndex(int indices[], int mat[][M]) {
        Point k = {0, indices[0]};
        for (int i = 1; i < N; i++) {
            if (get(i, indices, mat) < get(k.first, indices, mat)) {
                k = {i, indices[i]};
            }
        }
        indices[k.first]++;

        return k;
    }

    int get(int i, int indices[], int mat[][M]) {
        if (indices[i] >= M) return INT_MAX;
        return mat[i][indices[i]];
    }

   private:
    // print matrix sorted using minheap
    vector<int> printSortedUsingMinheap(int mat[][M]) {
        using P = pair<int, Point>;
        auto comparator = [](const auto& f, const auto& s) { return f.first > s.first; };
        priority_queue<P, vector<P>, decltype(comparator)> pq;

        pq.push({mat[0][0], {0, 0}});

        vector<int> result;

        unordered_set<int> visited;
        visited.insert(0);

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            result.push_back(cur.first);

            auto p = cur.second;
            if (p.first < N - 1 && p.second < M - 1) {
                if (visited.find((p.first + 1) * N + p.second) == visited.end()) {
                    pq.push({mat[p.first + 1][p.second], {p.first + 1, p.second}});
                    visited.insert((p.first + 1) * N + p.second);
                }

                if (visited.find(p.first * N + p.second + 1) == visited.end()) {
                    pq.push({mat[p.first][p.second + 1], {p.first, p.second + 1}});
                    visited.insert((p.first) * N + p.second + 1);
                }
            } else if (p.first < N - 1) {
                if (visited.find((p.first + 1) * N + p.second) == visited.end()) {
                    pq.push({mat[p.first + 1][p.second], {p.first + 1, p.second}});
                    visited.insert((p.first + 1) * N + p.second);
                }
            } else if (p.second < M - 1) {
                if (visited.find(p.first * N + p.second + 1) == visited.end()) {
                    pq.push({mat[p.first][p.second + 1], {p.first, p.second + 1}});
                    visited.insert((p.first) * N + p.second + 1);
                }
            }
        }

        return result;
    }

   private:
    // print matrix sorted using minheap.
    // space optimized: as only keeping one row worth of records in minheap. Also, don't need set to keep track of visited.
    /*
    Complexity: k*log(k).
    First of all, you only need to consider the left-top k*k matrix to find the k-th largest element.
    It's guaranteed to be in that smaller matrix. This helps especially when k << n.
    Then extract the first element of each row and put it in the max-heap with size K. Building the heap takes time k*log(k).
    Then remove the max element from the heap and put the next element in the same row into the heap. This step takes k*log(k) time.
    So in total, 2k*log(k) = k*log(k) time.
    It only requires O(k) space.
    There may be better selection algorithm with better best-case performance. If you know of a better algorithm than mine, let me know!
    */
    vector<int> printSortedUsingMinheap2(int mat[][M]) {
        using P = pair<int, Point>;
        auto comparator = [](const auto& f, const auto& s) { return f.first > s.first; };
        priority_queue<P, vector<P>, decltype(comparator)> pq;
        vector<int> result;

        for (int j = 0; j < M; j++) {
            pq.push({mat[0][j], {0, j}});
        }

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            result.push_back(cur.first);

            auto p = cur.second;

            if (p.first < N - 1) {
                pq.push({mat[p.first + 1][p.second], {p.first + 1, p.second}});
            }
        }

        return result;
    }
};