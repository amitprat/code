#pragma once
#include "../header.h"

class ValidTree {
   public:
    static void test() {
        ValidTree obj;

        vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};

        auto res = obj.validTree(5, edges);

        println("Is valid tree? {}", res);
    }

   public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;

        unordered_map<int, vector<int>> adjList;
        for (auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        unordered_set<int> visited;
        if (hasCycle(0, -1, adjList, visited)) return false;

        return visited.size() == n;
    }

   public:
    bool hasCycle(int u, int p, unordered_map<int, vector<int>>& adjList, unordered_set<int>& visited) {
        visited.insert(u);

        for (int v : adjList[u]) {
            if (!visited.contains(v)) {
                if (hasCycle(v, u, adjList, visited)) return true;
            } else if (v != p) return true;
        }

        return false;
    }
};