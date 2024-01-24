#pragma once
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <cassert>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;
using Point = pair<int, int>;

class MincostPathDijkstra
{
public:
    static void test()
    {
        MincostPathDijkstra obj;
        vector <Graph> contexts =
        {
            {
                {31, 100, 65, 12, 18},
                {10, 13, 47, 157, 6},
                {100, 113, 174, 11, 33},
                {88, 124, 41, 20, 140},
                {99, 32, 111, 41, 20}
            }
        };
        for (auto context : contexts)
        {
            auto res = obj.minCostPath(context, { 0,0 }, { 4,4 });
            cout << "Result:" << res << endl;
        }
    }

    int minCostPath(Graph g, Point s, Point d)
    {
        int n = g.size();
        int m = g[0].size();
        bool** visited = new bool* [n];
        int** cost = new int* [n];
        for (int i = 0; i < n; i++) {
            visited[i] = new bool[m];
            cost[i] = new int[m];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
                cost[i][j] = INT_MAX;
            }
        }

        cost[s.first][s.second] = g[s.first][s.second];
        vector<Point> neighbours = { {-1,0},{0,-1},{1,0},{0,1} };
        vector<Point> q;
        q.push_back(s);
        while (!q.empty())
        {
            Point p = minCost(q, cost, visited, n, m);
            visited[p.first][p.second] = true;
            if (equal(p, d)) break;
            for (auto n : getNeighbours(p, visited, neighbours, n, m)) {
                cost[n.first][n.second] = min(cost[n.first][n.second],
                    cost[p.first][p.second] + g[n.first][n.second]);
                q.push_back(n);
            }
        }

        return cost[d.first][d.second];
    }

private:
    Point minCost(vector<Point> q, int** cost, bool** visited, int n, int m)
    {
        Point res = { INT_MAX, INT_MAX };
        int mnDis = INT_MAX;
        for (auto i : q) {
            if (!visited[i.first][i.second]) {
                if (less(i, mnDis, cost)) {
                    res = i; mnDis = cost[i.first][i.second];
                }
            }
        }
        return res;
    }

    bool equal(Point f, Point s) {
        return f.first == s.first && f.second == s.second;
    }
    bool less(Point f, int dist, int** cost) {
        return cost[f.first][f.second] < dist;
    }

    vector<Point> getNeighbours(Point p, bool** visited, vector<Point> neighbours, int n, int m)
    {
        vector<Point> res;
        for (auto delta : neighbours) {
            Point d = { p.first + delta.first, p.second + delta.second };
            if (d.first < 0 || d.second < 0 || d.first >= n || d.second >= m) continue;
            if (!visited[d.first][d.second]) res.push_back(d);
        }

        return res;
    }
};