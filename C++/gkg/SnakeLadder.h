#pragma once
#include "../Header.h"

class SnakeLadder {
public:
    static void test() {
        int N = 30;
        unordered_map<int, int> snakeLadders;
        snakeLadders[2] = 21;
        snakeLadders[4] = 7;
        snakeLadders[10] = 25;
        snakeLadders[19] = 28;

        // Snakes
        snakeLadders[26] = 0;
        snakeLadders[20] = 8;
        snakeLadders[16] = 3;
        snakeLadders[18] = 6;

        cout << "Min Dice throws required is " << getMinDiceThrowsUsingBFS(snakeLadders, N) << endl;
        cout << "Min Dice throws required is " << getMinDiceThrowsUsingDFS(snakeLadders, N) << endl;
    }

    static int getMinDiceThrowsUsingBFS(unordered_map<int, int>& snakeLadders, int N) {
        unordered_set<int> visited;
        queue<pair<int, int>> q;
        q.push({ 1,0 });
        visited.insert(1);

        while (!q.empty()) {
            auto f = q.front(); q.pop();
            if (f.first == N) return f.second;

            for (int c = 1; c <= 6; c++) {
                int v = f.first + c;
                if (snakeLadders.find(v) != snakeLadders.end()) {
                    v = snakeLadders[v];
                }
                if (v <= N && visited.count(v) == 0) {
                    visited.insert(v);
                    q.push({ v,f.second + 1 });
                }
            }
        }

        return INT_MAX;
    }

    static int getMinDiceThrowsUsingDFS(unordered_map<int, int>& snakeLadders, int N) {
        int minJumps = INT_MAX;
        unordered_set<int> visited;

        getMinDiceThrowsUsingDFS(1, snakeLadders, N, minJumps, visited, 0);

        return minJumps;
    }

    static void getMinDiceThrowsUsingDFS(int u, unordered_map<int, int>& snakeLadders, int N, int& minJumps, unordered_set<int> visited, int jumps)
    {
        if (u == N) {
            minJumps = min(minJumps, jumps);
            return;
        }

        for (int c = 6; c >= 1; c--) {
            int v = u + c;
            if (snakeLadders.find(v) != snakeLadders.end()) {
                v = snakeLadders[v];
            }
            if (v <= N && visited.find(v) == visited.end()) {
                visited.insert(v);
                getMinDiceThrowsUsingDFS(v, snakeLadders, N, minJumps, visited, jumps + 1);
            }
        }
    }
};