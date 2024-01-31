#pragma once
#include "../header.h"
#include "ds/Graph.h"

class CheckifValidBinaryTree {
   public:
    bool isValidBinaryTree(Graph g) {
        return this->isConnected(g) && this->hasAtMost2Children(g) && !this->hasCycle(g);
    }

   private:
    bool isConnected(Graph g) {
        int V = g.size();

        vector<bool> visited(V, false);
        this->dfs(g, 0, visited);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                return false;

        return true;
    }

    void dfs(Graph g, int u, vector<bool> &visited) {
        visited[u] = true;

        for (auto v : g.adjVertices(u)) {
            if (!visited[v]) {
                this->dfs(g, v, visited);
            }
        }
    }

   private:
    bool hasAtMost2Children(Graph g) {
        unordered_set<int> visited;
        return hasAtMost2Children(g, 0, -1, visited);
    }
    bool hasAtMost2Children(Graph g, int src, int parent, unordered_set<int> &visited) {
        if (visited.find(src) != visited.end()) return true;

        visited.insert(src);

        auto children = g.adjVertices(src);
        if (children.size() > 3)
            return false;

        if (children.size() > 2 && (children.find(parent) == children.end()))
            return false;

        for (auto &e : children) {
            if (!hasAtMost2Children(g, e, src, visited)) return false;
        }

        return true;
    }

   private:
    bool hasCycle(Graph g) {
        int V = g.size();
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (this->hasCycle(g, i, -1, visited))
                    return true;
            }
        }

        return false;
    }

    bool hasCycle(Graph g, int u, int p, vector<bool> &visited) {
        visited[u] = true;

        for (auto v : g.adjVertices(u)) {
            if (!visited[v]) {
                if (hasCycle(g, v, u, visited))
                    return true;

                return false;
            } else if (v != p)
                return true;
        }

        return false;
    }
};