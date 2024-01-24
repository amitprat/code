#pragma once
#include "../header.h"
#include "../design/Set.h"

class TSP {
public:
    static void test() {
        vector<vector<int>> graph = {
            { 0, 10, 15, 20 },
            { 10, 0, 35, 25 },
            { 15, 35, 0, 30 },
            { 20, 25, 30, 0 }
        };

        TSP obj;
        int dist = obj.getShortestDist(graph);
        cout << "Get Shortest Distance: " << dist << endl;
    }

    int getShortestDist(vector<vector<int>> v) {
        Set<int> visited;
        int shortestDist = INT_MAX;
        visited.add(0);
        getShortestDist(v, visited, 0, 0, shortestDist, 0, 0);

        return shortestDist;
    }

private:
    void getShortestDist(vector<vector<int>> g, Set<int>& visited, int u, int v, int& shortestDist, int cur, int cnt) {
        if (cnt == g.size() - 1 && g[v][u]) {
            shortestDist = min(shortestDist, cur + g[v][u]);
            return;
        }

        for (int i = 0; i < g.size(); i++) {
            if (!visited.exists(i) && g[v][i]) {
                visited.add(i);
                getShortestDist(g, visited, u, i, shortestDist, cur + g[v][i], cnt + 1);
                visited.remove(i);
            }
        }
    }
};