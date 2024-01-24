#pragma once
#include "../Header.h"
#define V 8

class EdgeDisjointPaths {
public:
    static void test() {
        EdgeDisjointPaths obj;
        int graph[V][V] = { {0, 1, 1, 1, 0, 0, 0, 0},
                    {0, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 0, 1, 0, 0, 1, 0},
                    {0, 0, 0, 0, 0, 0, 1, 0},
                    {0, 0, 1, 0, 0, 0, 0, 1},
                    {0, 1, 0, 0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0, 1, 0, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0}
        };

        int s = 0;
        int t = 7;
        int maxFlow = obj.findDisjointPaths(graph, s, t);

        cout << "There can be maximum " << maxFlow
            << " edge-disjoint paths from " << s << " to " << t;
    }

    int findDisjointPaths(int graph[][V], int s, int d) {
        int rGraph[V][V];
        copy(graph, rGraph);
        int parent[V];
        int maxFlow = 0;
        while (bfs(rGraph, s, d, parent)) {
            cout << "Route found from src to dst" << endl;

            auto curFlow = getFlow(rGraph, s, d, parent);
            cout << "Current possible flow = " << curFlow << endl;

            updateCapacity(rGraph, s, d, parent, curFlow);
            maxFlow += curFlow;
        }
        cout << "Max Flow = " << maxFlow << endl;
        return maxFlow;
    }

private:
    void copy(int graph[][V], int rGraph[][V]) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                rGraph[i][j] = graph[i][j];
            }
        }
    }

    bool bfs(int graph[][V], int s, int d, int parent[]) {
        queue<int> q;
        q.push(s);
        unordered_set<int> visited;
        visited.insert(s);
        parent[s] = -1;

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u == d) return true;
            for (int v = 0; v < V; v++) {
                if (graph[u][v] && visited.find(v) == visited.end()) {
                    parent[v] = u;
                    q.push(v);
                    visited.insert(v);
                }
            }
        }

        return false;
    }

    int getFlow(int graph[][V], int s, int d, int parent[]) {
        int flow = INT_MAX;
        for (auto u = d; u != s; u = parent[u]) {
            flow = min(flow, graph[parent[u]][u]);
        }
        return flow;
    }

    void updateCapacity(int graph[][V], int s, int d, int parent[], int flow) {
        for (auto u = d; u != s; u = parent[u]) {
            graph[parent[u]][u] -= flow;
            graph[u][parent[u]] += flow;
        }
    }
};