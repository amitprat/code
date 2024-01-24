#include "../header.h"

class CheckBiPartitite {
    class Graph {
       public:
        int V;
        unordered_set<int> vertices;
        unordered_map<int, vector<int>> adjMap;

        Graph(int v) : V(v) {}

        void addEdge(int u, int v) {
            vertices.insert(u);
            vertices.insert(v);

            this->adjMap[u].push_back(v);
            this->adjMap[v].push_back(u);
        }
    };

   public:
    static void test() {
        Graph g(7);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge(3, 4);
        g.addEdge(4, 5);
        g.addEdge(5, 6);
        g.addEdge(6, 1);

        CheckBiPartitite obj;
        bool result = obj.isBipartite(g);

        if (result) {
            cout << "Grpah is bipartite." << endl;
        } else {
            cout << "Graph isn't bipartite." << endl;
        }
    }

   private:
    bool isBipartite(Graph g) {
        vector<int> colors(g.V, -1);
        vector<bool> visited(g.V, false);

        for (auto &u : g.vertices) {
            if (!visited[u]) {
                bool result = this->dfs(g, u, visited, colors, 0);
                if (!result)
                    return false;
            }
        }

        return true;
    }

    bool dfs(Graph g, int u, vector<bool> &visited, vector<int> &colors, int curColor) {
        visited[u] = true;
        colors[u] = curColor;

        for (auto &v : g.adjMap[u]) {
            if (!visited[v]) {
                if (!dfs(g, v, visited, colors, !curColor))
                    return false;
            } else if (colors[v] == colors[u]) {
                return false;
            }
        }

        return true;
    }
};