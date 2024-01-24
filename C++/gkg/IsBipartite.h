#pragma once
#include "../Header.h"

class IsBipartite {
    struct Node {
        int vertex;
        int color;
        Node(int vertex, int color) :vertex(vertex), color(color) {}
    };
public:
    static void test() {
        vector<vector<int>> g = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {1, 0, 1, 0}
        };

        isBipartite(g) ? cout << "Yes" : cout << "No";
    }

    static bool isBipartite(vector<vector<int>>& g) {
        queue<int> q;
        vector<int> colors(g.size(), -1);
        colors[0] = 0;
        q.push(0);

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (int v = 0; v < g.size(); v++) {
                if (g[u][v]) {
                    if (colors[v] == -1) {
                        colors[v] = 1 - colors[u];
                        q.push(v);
                    }
                    else if (colors[v] == colors[u]) return false;
                }
            }
        }

        return true;
    }
};