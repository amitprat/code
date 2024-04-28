#pragma once
#include "../header.h"

class WeightedBFSShortedPath {
    struct Edge {
        int v;
        int w;
    };
    class Graph {
       public:
        unordered_set<int> vertices;
        unordered_map<int, vector<Edge>> adjMap;

        void addVertex(int src) {
            vertices.insert(src);
        }

        void addEdge(int src, Edge edge) {
            adjMap[src].push_back(edge);
        }
    };

   public:
    void zeroOneBFS(Graph g, int src) {
        int V = g.vertices.size();
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        deque<int> dq;
        dq.push_back(src);

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();

            for (auto& edge : g.adjMap[u]) {
                if (dist[edge.v] > dist[u] + edge.w) {
                    dist[edge.v] = dist[u] + edge.w;

                    if (edge.w == 0)
                        dq.push_front(edge.v);
                    else
                        dq.push_back(edge.v);
                }
            }
        }

        cout << "Distance: " << dist << endl;
    }
};