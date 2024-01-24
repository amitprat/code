#pragma once
#include "../header.h"

class HamiltonianCycle {
private:
    // Check if it is safe to consider next vertex in hamcycle
    bool isSafe(vector<vector<int>> graph, vector<int>& paths, int pos, int v) {
        auto u = paths[pos - 1];
        if (!graph[u][v]) return false; // check if there is an edge to next vertex
        for (int p = 0; p < pos; p++) { // check if this vertex already included
            if (paths[p] == v) return false;
        }
        return paths[pos] == -1;
    }
    bool hamCycle(vector<vector<int>> graph, vector<int>& paths, int pos) {
        auto u = paths[pos - 1];
        if (pos == graph.size()) { // if we have visited all the vertices
            auto v = paths[0];
            if (graph[u][v]) return true; // check if it has edge back to start vertex
            return false;
        }
        for (int v = 1; v < graph.size(); v++) {
            if (isSafe(graph, paths, pos, v)) { // include the next vertex
                paths[pos] = v;
                if (hamCycle(graph, paths, pos + 1)) return true; // if this finds one solution, the return true
                paths[pos] = -1; // else freeup this vertex
            }
        }
        return false;
    }

    void printSol(vector<int> paths) {
        cout << "Hamiltonian Cycle: ";
        for (auto i : paths) {
            cout << i << " ";
        }
        cout << paths[0];
        cout << endl;
    }
public:
    void hamCycle(vector<vector<int>> graph) {
        int V = graph.size();
        vector<int> paths(V, -1);
        paths[0] = 0;
        if (!hamCycle(graph, paths, 1)) {
            cout << "Solution doesn't exist" << endl;
            return;
        }
        printSol(paths);
    }

    static void test() {
        HamiltonianCycle obj;
        vector<vector<int>> graph1 = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1},
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0},
        };
        obj.hamCycle(graph1);

        vector<vector<int>> graph2 = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1},
            {1, 1, 0, 0, 0},
            {0, 1, 1, 0, 0},
        };
        obj.hamCycle(graph2);
    }
};