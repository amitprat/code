#pragma once
#include "../header.h"

/*
-----------------------------------------------------------
🧩 PROBLEM: Print All Paths from Source to Destination in a Directed Graph
-----------------------------------------------------------

Given a directed graph and two vertices `src` and `dst`,
print all possible paths from `src` to `dst`.

Example:
Graph:
    0 → 1 → 3
    ↘︎ 2 → 0
      ↘︎ 1

Paths from 2 → 3:
    2 → 0 → 1 → 3
    2 → 1 → 3

-----------------------------------------------------------
🚀 APPROACHES:
-----------------------------------------------------------

1️⃣ **DFS Backtracking**
   - Explore all possible paths recursively.
   - Mark vertices as visited during current recursion.
   - Backtrack to explore alternative routes.
   - Time Complexity: O(V!); exponential in worst case.

2️⃣ **BFS (Level-wise path expansion)**
   - Store paths as queues and expand step by step.
   - Avoid revisiting nodes already in current path.
   - Less space-efficient, but easy to implement iteratively.

-----------------------------------------------------------
*/

class AllPathsFromSourceToDestination {
    class Graph {
       public:
        int V;
        unordered_set<int> vertices;
        unordered_map<int, vector<int>> adjMap;

        explicit Graph(int v) : V(v) {}

        void addEdge(int u, int v) {
            vertices.insert(u);
            vertices.insert(v);
            adjMap[u].push_back(v);
        }
    };

   public:
    static void test() {
        Graph g(4);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 3);
        g.addEdge(2, 0);
        g.addEdge(2, 1);
        g.addEdge(1, 3);

        AllPathsFromSourceToDestination obj;
        int s = 2, d = 3;

        cout << "DFS-based paths from " << s << " to " << d << ":\n";
        obj.printAllPathsDFS(g, s, d);

        cout << "BFS-based paths from " << s << " to " << d << ":\n";
        obj.printAllPathsBFS(g, s, d);
    }

   private:
    //-------------------------------------------------------
    // Depth-First Search (Recursive Backtracking)
    //-------------------------------------------------------
    void printAllPathsDFS(const Graph& g, int s, int d) {
        vector<vector<int>> paths;
        vector<bool> visited(g.V, false);

        vector<int> path;
        dfs(g, s, d, visited, path, paths);

                if (paths.empty()) {
            cout << "No paths found.\n";
            return;
        }

        for (const auto& p : paths) {
            cout << "[ ";
            for (int node : p) cout << node << " ";
            cout << "]\n";
        }
    }

   public:
    void dfs(const Graph& g, int s, int d, vector<bool>& visited,
             vector<int>& path, vector<vector<int>>& paths) {
        visited[s] = true;
        path.push_back(s);

        if (s == d) {
            paths.push_back(path);
        } else {
            for (int neighbor : g.adjMap.at(s)) {
                if (!visited[neighbor]) {
                    dfs(g, neighbor, d, visited, path, paths);
                }
            }
        }

        path.pop_back();
        visited[s] = false;
    }

   public:
    //-------------------------------------------------------
    // Breadth-First Search (Iterative using path queue)
    //-------------------------------------------------------
    void printAllPathsBFS(const Graph& g, int s, int d) {
        vector<vector<int>> result;

        queue<vector<int>> q;
        vector<bool> visisted(g.V, false);

        q.push({s});
        visisted[s] = true;

        while (!q.empty()) {
            auto path = q.front();
            q.pop();
            int u = path.back();

            if (u == d) {
                result.push_back(path);
                continue;
            }

            for (const auto& v : g.adjMap.at(u)) {
                if (find(path.begin(), path.end(), v) == path.end()) {
                    vector<int> new_path = path;
                    new_path.push_back(v);
                    q.push(move(new_path));
                }
            }
        }

        if (result.empty()) {
            cout << "No paths found.\n";
            return;
        }

        for (const auto& p : result) {
            cout << "[ ";
            for (int node : p) cout << node << " ";
            cout << "]\n";
        }
    }
};
