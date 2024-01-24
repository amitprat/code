#pragma once
#include "../Header.h"

class HamCycle {
    static const int V = 5;
public:
    static void test() {
        HamCycle obj;
        bool graph1[V][V] = { {0, 1, 0, 1, 0},
                        {1, 0, 1, 1, 1},
                        {0, 1, 0, 0, 1},
                        {1, 1, 0, 0, 1},
                        {0, 1, 1, 1, 0} };

        // Print the solution  
        obj.hamCycle(graph1);
    }

    bool hamCycle(bool graph[V][V]) {
        int* path = new int[V];
        memset(path, -1, sizeof(int) * V);
        int pos = 0;
        path[pos] = 0; // assign vertex 0 at pos 0 in paths

        // assign the next safe vertex at pos+1
        bool res = hasHamCycle(graph, pos + 1, path);
        if (res) print(path);

        return res;
    }

    void print(int path[]) {
        for (int i = 0; i < V; i++) cout << path[i] << " ";
        cout << endl;
    }

    bool hasHamCycle(bool graph[V][V], int pos, int path[]) {
        // if we visited all vertex, then we have ham cycle
        if (pos == V) {
            int u = path[pos - 1];
            int v = path[0];
            return graph[u][v];
        }

        // try all the vertices
        for (int v = 1; v < V; v++) {
            if (isSafe(graph, v, path, pos)) {
                path[pos] = v;
                // fill the next position
                if (hasHamCycle(graph, pos + 1, path)) return true;
                path[pos] = -1;
            }
        }
    }

    bool isSafe(bool graph[V][V], int v, int path[], int pos) {
        int u = path[pos - 1];
        if (!graph[u][v]) return false; // if this vertex isn't adjacent vertex to vertex at previos pos
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) return false; // if we have included this vertex before
        }
        return true;
    }
};