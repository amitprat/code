#include "../header.h"

class MinDiceThrowsInSnakeLadderGame {
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

        cout << "Min Dice throws required is " << minDiceThrows(snakeLadders, N) << endl;
    }

   public:
    static int minDiceThrows(unordered_map<int, int>& snakeLadders, int N) {
        auto res1 = getMinDiceThrowsUsingBFS(snakeLadders, N);
        auto res2 = getMinDiceThrowsUsingBFSWithPath(snakeLadders, N);
        auto res3 = getMinDiceThrowsUsingDFS(snakeLadders, N);

        assert(res1 == res2);
        assert(res1 == res3);

        return res1;
    }

   private:
    static int getMinDiceThrowsUsingBFS(unordered_map<int, int>& snakeLadders, int N) {
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
                if (snakeLadders.find(v) != snakeLadders.end()) {
                    v = snakeLadders[v];
                }
                if (v <= N && visited.count(v) == 0) {
                    visited.insert(v);
                    q.push({v, f.second + 1});
                }
            }
        }

        return INT_MAX;
    }

   private:
    static int getMinDiceThrowsUsingBFSWithPath(unordered_map<int, int>& snakeLadders, int N) {
        unordered_set<int> visited;
        using P = pair<int, vector<int>>;
        queue<P> q;
        q.push({1, {1}});
        visited.insert(1);

        while (!q.empty()) {
            auto front = q.front();
            q.pop();

            auto u = front.first;
            auto path = front.second;

            if (u == N) {
                cout << path << endl;
                return path.size();
            }

            for (auto dice = 1; u + dice <= N && dice <= 6; dice++) {
                auto v = u + dice;
                if (visited.find(v) == visited.end()) {
                    v = snakeLadders[v] != -1 ? snakeLadders[v] : v;
                    visited.insert(v);

                    auto newPath = path;
                    newPath.push_back(v);
                    q.push({v, newPath});
                }
            }
        }

        return -1;
    }

   private:
    static int getMinDiceThrowsUsingDFS(unordered_map<int, int>& snakeLadders, int N) {
        int minJumps = INT_MAX;
        unordered_set<int> visited;

        getMinDiceThrowsUsingDFS(1, snakeLadders, N, minJumps, visited, 0);

        return minJumps;
    }

    static void getMinDiceThrowsUsingDFS(int u, unordered_map<int, int>& snakeLadders, int N, int& minJumps, unordered_set<int> visited, int jumps) {
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
