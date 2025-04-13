#pragma once
#include "../header.h"

class SnakeLadderGame {
   public:
    static void test() {
        SnakeLadderGame obj;
        unordered_map<int, int> snakeLadders = {
            {3, 22},
            {5, 8},
            {11, 26},
            {20, 29},
            {17, 4},
            {19, 7},
            {27, 1},
            {21, 9}};

        int s = 1, d = 30;
        int jumps1 = obj.minJumpsDFS(s, d, snakeLadders);
        int jumps2 = obj.minJumpsBFS(s, d, snakeLadders);
        cout << jumps1 << ", " << jumps2 << endl;
    }

   public:
    int minJumpsBFS(int s, int d, unordered_map<int, int>& snakeLadders) {
        queue<int> q;
        q.push(s);

        unordered_set<int> visited;
        visited.insert(s);

        int jumps = 0;
        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto f = q.front();
                q.pop();
                if (f == d) return jumps;

                for (int c = 1; c <= 6 && f + c <= d; c++) {
                    int n = f + c;
                    if (snakeLadders.find(n) != snakeLadders.end()) n = snakeLadders[n];
                    if (visited.count(n) > 0) continue;

                    q.push(n);
                    visited.insert(n);
                }
            }
            jumps++;
        }

        return -1;
    }

   public:
    int minJumpsDFS(int s, int d, unordered_map<int, int>& snakeLadders) {
        unordered_set<int> visited;

        return minJumpsDFS(s, d, snakeLadders, visited);
    }

    int minJumpsDFS(int s, int d, unordered_map<int, int>& snakeLadders, unordered_set<int>& visited) {
        if (s == d) return 0;
        visited.insert(s);

        int cnt = INT_MAX;
        for (int c = 1; c <= 6 && s + c <= d; c++) {
            int n = s + c;
            if (snakeLadders.find(n) != snakeLadders.end()) n = snakeLadders[n];
            if (visited.count(n) > 0) continue;

            int curCnt = minJumpsDFS(n, d, snakeLadders, visited);
            if (curCnt != INT_MAX) {
                curCnt += 1;
            }
            cnt = min(cnt, curCnt);
        }

        return cnt;
    }

   public:
    int getMinDiceThrowsUsingBFS(unordered_map<int, int>& snakeLadders, int N) {
        unordered_set<int> visited;
        queue<pair<int, int>> q;
        q.push({1, 0});
        visited.insert(1);

        while (!q.empty()) {
            auto f = q.front();
            q.pop();

            if (f.first == N) return f.second;

            for (int c = 1; c <= 6; c++) {
                int v = f.first + c;

                // jump if there is a snake or ladder at this position.
                if (snakeLadders.find(v) != snakeLadders.end()) {
                    v = snakeLadders[v];
                }

                // avoid going out of band and in loop.
                if (v <= N && visited.count(v) == 0) {
                    visited.insert(v);
                    q.push({v, f.second + 1});
                }
            }
        }

        return INT_MAX;
    }

   public:
    int getMinDiceThrowsUsingDFS(unordered_map<int, int>& snakeLadders, int N) {
        int minJumps = INT_MAX;
        unordered_set<int> visited;

        getMinDiceThrowsUsingDFS(1, snakeLadders, N, minJumps, visited, 0);

        return minJumps;
    }

    void getMinDiceThrowsUsingDFS(int u, unordered_map<int, int>& snakeLadders, int N, int& minJumps, unordered_set<int> visited, int jumps) {
        visited.insert(u);

        if (u == N) {
            minJumps = min(minJumps, jumps);
            return;
        }

        for (int c = 6; c >= 1; c--) {
            int v = u + c;

            // jump if there is a snake or ladder at this position.
            if (snakeLadders.find(v) != snakeLadders.end()) {
                v = snakeLadders[v];
            }

            // avoid going out of band and in loop.
            if (v <= N && visited.find(v) == visited.end()) {
                getMinDiceThrowsUsingDFS(v, snakeLadders, N, minJumps, visited, jumps + 1);
            }
        }
    }
};