#pragma once
#include "../Header.h"

class CountPaths {
public:
    static void test() {
        CountPaths obj;
        vector<vector<int>> graph = { { 0, 1, 1, 1 },
                    { 0, 0, 0, 1 },
                    { 0, 0, 0, 1 },
                    { 0, 0, 0, 0 } };
        int u = 0, v = 3, k = 2;
        cout << obj.countwalks(graph, u, v, k);
    }

    int countwalks(vector<vector<int>> graph, int src, int dst, int k) {
        if (k == 0 && src == dst) return 1;
        if (k <= 0) return 0;

        int count = 0;
        for (int v = 0; v < graph.size(); v++) {
            if (graph[src][v]) count += countwalks(graph, v, dst, k - 1);
        }
        return count;
    }
};