#pragma once
#include "../header.h"

class CountWalksFromSourceToDestWithKEdges {
    using Matrix = vector<vector<int>>;

   public:
    int countWalks(Matrix g, int src, int dst, int k, unordered_set<int>& visited) {
        if (k == 0 && src == dst) return 1;
        if (k < 0 || src == dst) return 0;

        visited.insert(src);

        int walks = 0;
        for (int v = 0; v < g[src].size(); v++) {
            if (g[src][v] && visited.find(v) == visited.end()) {
                walks += countWalks(g, v, dst, k - 1, visited);
            }
        }

        visited.erase(visited.end());

        return walks;
    }
};