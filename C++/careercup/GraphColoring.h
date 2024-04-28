#pragma once
#include "../header.h"

class GraphColoring {
   public:
    static void test() {
        GraphColoring obj;

        vector<vector<int>> graph = {
            {0, 1, 1, 1},
            {1, 0, 1, 0},
            {1, 1, 0, 1},
            {1, 0, 1, 0},
        };

        int m = 3;
        auto res = obj.canColor(graph, m);
        cout << format("Can graph be colored using {} colors? {}", m, to_string(res)) << endl;
    }

   public:
    bool canColor(Graph g, int m) {
        int u = *g.getVertices().begin();
        int V = g.getVertices().size();
        unordered_map<int, int> colorMap;

        if (canColor(g, u, V, m, colorMap)) {
            cout << colorMap << endl;

            return true;
        }

        return false;
    }

   public:
    bool canColor(Graph g, int u, int V, int m, unordered_map<int, int>& colorMap) {
        if (u == V) return true;

        for (int c = 1; c <= m; c++) {
            if (isSafe(g, u, c, colorMap)) {
                colorMap[u] = c;

                if (canColor(g, u + 1, V, m, colorMap)) return true;

                colorMap[u] = -1;
            }
        }

        return false;
    }

    bool isSafe(Graph g, int u, int newColor, unordered_map<int, int>& colorMap) {
        for (auto& v : g.getAdjMap()[u]) {
            if (colorMap[v] != -1 && colorMap[v] == newColor) return false;
        }

        return true;
    }

   public:
    bool canColor(vector<vector<int>>& graph, int m) {
        vector<int> colors(graph.size(), 0);

        bool res = canColor(graph, 0, m, colors);
        if (res) cout << colors << endl;

        return res;
    }

    bool canColor(vector<vector<int>>& graph, int pos, int m, vector<int>& colors) {
        if (pos == graph.size()) return true;

        for (int c = 1; c <= m; c++) {
            if (isSafe(graph, pos, c, colors)) {
                colors[pos] = c;
                if (canColor(graph, pos + 1, m, colors)) return true;
                colors[pos] = 0;
            }
        }
        return false;
    }

   private:
    bool isSafe(vector<vector<int>>& graph, int u, int c, vector<int>& colors) {
        for (int v = 0; v < graph.size(); v++) {
            if (graph[u][v] && c == colors[v]) return false;
        }
        return true;
    }
};