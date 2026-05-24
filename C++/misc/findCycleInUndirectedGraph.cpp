#pragma once
#include "../header.h"

/*
 * Given an undirected graph, determine if it contains a cycle.
 * For example, the graph represented by edges [[0, 1], [1, 2], [2, 0]] contains a cycle, while the graph represented by edges
 * [[0, 1], [1, 2]] does not contain a cycle.
 * The graph is represented as an edge list, where each edge is a pair of vertices. The vertices are labeled from 0 to n-1,
 * where n is the number of vertices in the graph.
 *
 * To solve this problem, we can use Depth-First Search (DFS) to traverse the graph and check for cycles.
 * We will maintain a visited set to keep track of the vertices we have already visited. When we visit a vertex, we will check
 * its neighbors. If we encounter a neighbor that has already been visited and is not the parent of the current vertex,
 * then we have found a cycle. Note that we need to keep track of parent vertex as we can visit parent vertex while traversing the graph,
 * and if we encounter a visited neighbor that is not the parent, it indicates a cycle.
 */

class FindCycleInUndirectedGraph {
   public:
    static void test() {
        FindCycleInUndirectedGraph obj;

        vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};

        auto res = obj.hasCycleDFS(3, edges);

        println("Has cycle? {}", res);
    }

   public:
    bool hasCycleDFS(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adjList;
        for (auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        unordered_set<int> visited;
        for (int i = 0; i < n; i++) {
            if (!visited.contains(i)) {
                if (hasCycleDFS(i, -1, adjList, visited)) return true;
            }
        }

        return false;
    }

   public:
    bool hasCycleDFS(int u, int p, unordered_map<int, vector<int>>& adjList, unordered_set<int>& visited) {
        visited.insert(u);

        for (int v : adjList[u]) {
            if (!visited.contains(v)) {
                if (hasCycleDFS(v, u, adjList, visited)) return true;
            } else if (v != p) return true;
        }

        return false;
    }

   public:
    bool hasCycleBFS(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adjList;
        for (auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        unordered_set<int> visited;
        for (int i = 0; i < n; i++) {
            if (!visited.contains(i)) {
                if (hasCycleBFS(i, adjList, visited)) return true;
            }
        }

        return false;
    }

   public:
    bool hasCycleBFS(int start, unordered_map<int, vector<int>>& adjList, unordered_set<int>& visited) {
        queue<pair<int, int>> q;  // pair of (current vertex, parent vertex)
        q.push({start, -1});
        visited.insert(start);

        while (!q.empty()) {
            auto [u, p] = q.front();
            q.pop();

            for (int v : adjList[u]) {
                if (!visited.contains(v)) {
                    visited.insert(v);
                    q.push({v, u});
                } else if (v != p) return true;  // found a visited neighbor that is not the parent
            }
        }

        return false;
    }
};
