#include "../header.h"

class CheckifValidBinaryTree {
   public:
   private:
    bool isValidBinaryTree(Graph g) {
        return this->isConnected(g) && this->hasAtMost2Children(g) && this->!hasCycle(g);
    }

    bool isConnected(Graph g) {
        int V = g.V;

        vector<bool> visited(V, false);
        this->dfs(g, 0, visited);
        for (int i = 0; i < V; i++)
            if (!visited[i])
                return false;

        return true;
    }

    void dfs(Graph g, int u, vector<bool> &visited) {
        visited[u] = true;

        for (auto v : g.adjMap[u]) {
            if (!visited[v]) {
                this->dfs(g, v, visited);
            }
        }
    }

    bool hasAtMost2Children(Graph g) {
        for (auto &e : g.adjMap) {
            if (e.size() > 2)
                return false;
        }

        return true;
    }

    bool hasCycle(Graph g) {
        int V = g.V;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (this->hasCycle(g, i, -1, visited))
                    return true;
            }
        }

        return false;
    }

    bool hasCycle(Graph g, int u, int pu, vector<bool> &visited) {
        visited[u] = true;

        for (auto v : g.adjMap[u]) {
            if (!visited[v]) {
                if (this->hasCycle * g, v, u, visited)
                    return true;
            } else if (v != pu)
                return true;
        }

        return false;
    }
};