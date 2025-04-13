#pragma once
#include "../header.h"

/**
 * 0-1 BFS for Shortest Path in a Graph with Edge Weights 0 or 1
 * -------------------------------------------------------------
 * Uses a deque to maintain vertices in increasing order of distance.
 * Time: O(V + E), Space: O(V)
 */

class WeightedBFSShortestPath {
    struct Edge {
        int v;  // destination vertex
        int w;  // weight (0 or 1)
    };

    class Graph {
       public:
        unordered_set<int> vertices;
        unordered_map<int, vector<Edge>> adjMap;

        void addVertex(int src) {
            vertices.insert(src);
        }

        void addEdge(int src, int dest, int weight) {
            adjMap[src].emplace_back(Edge{dest, weight});
            vertices.insert(src);
            vertices.insert(dest);
        }
    };

   public:
    void zeroOneBFS(Graph& g, int src, vector<int>& distOut) {
        int maxV = *max_element(g.vertices.begin(), g.vertices.end()) + 1;
        vector<int> dist(maxV, INT_MAX);
        dist[src] = 0;

        deque<int> dq;
        dq.push_back(src);

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();

            for (const auto& edge : g.adjMap[u]) {
                if (dist[edge.v] > dist[u] + edge.w) {
                    dist[edge.v] = dist[u] + edge.w;
                    if (edge.w == 0) {
                        dq.push_front(edge.v);
                    } else {
                        dq.push_back(edge.v);
                    }
                }
            }
        }

        distOut = dist;
        cout << "Distances from source " << src << ": ";
        for (int i = 0; i < maxV; ++i) {
            if (g.vertices.count(i)) cout << "[" << i << ": " << dist[i] << "] ";
        }
        cout << endl;
    }

    static void test() {
        WeightedBFSShortestPath algo;
        Graph g;

        // Test graph: directed edges with weights 0 or 1
        g.addEdge(0, 1, 0);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 0);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 4, 0);

        vector<int> dist;
        algo.zeroOneBFS(g, 0, dist);

        // Expected distances: 0->0, 1->0, 2->1, 3->0, 4->0
        assert(dist[0] == 0);
        assert(dist[1] == 0);
        assert(dist[2] == 1);
        assert(dist[3] == 0);
        assert(dist[4] == 0);

        // Edge case: Disconnected node
        g.addVertex(5);
        algo.zeroOneBFS(g, 0, dist);
        assert(dist[5] == INT_MAX);

        cout << "All test cases passed.\n";
    }
};
