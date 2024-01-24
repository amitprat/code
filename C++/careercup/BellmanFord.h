#pragma once
#include "../Header.h"

class BellmanFord {
    class Graph {
    public:
        struct Edge {
            int u, v, w;
        };
        int V;
        vector<Edge> edges;
        Graph(int v) :V(v) {}
        void add(Edge edge) { edges.push_back(edge); }
    };
public:
    static void test() {
        BellmanFord obj;
        Graph g(5);
        g.add({ 0, 1, -1 });
        g.add({ 0, 2, 4 });
        g.add({ 1, 2, 3 });
        g.add({ 1, 3, 2 });
        g.add({ 1, 4, 2 });
        g.add({ 3, 2, 5 });
        g.add({ 3, 1, 1 });
        g.add({ 4, 3, -3 });

        int s = 0;
        vector<int> dist = obj.bellman(g, s);
        for (auto i = 0; i < dist.size(); i++) {
            cout << "Min distance from " << s << " to " << i << " = " << dist[i] << endl;
        }
    }

    vector<int> bellman(Graph g, int s) {
        vector<int> dist(g.V, INT_MAX);
        dist[s] = 0;

        // relax all edges for V-1 times
        for (int cnt = 0; cnt < g.V - 1; cnt++) {
            for (auto e : g.edges) {
                relax(e, dist);
            }
        }

        // try relaxing edges again and if we can still relax edge then its negative weight cycle
        for (auto e : g.edges) {
            if (canRelax(e, dist)) {
                cout << "Contains negative weight cycle!!";
                return {};
            }
        }

        return dist;
    }

    void relax(Graph::Edge e, vector<int>& dst) {
        // relax is just a way to find if we can reach other end of edge using this edge which has lesser total weight
        if (dst[e.v] > dst[e.u] + e.w) dst[e.v] = dst[e.u] + e.w;
    }

    bool canRelax(Graph::Edge e, vector<int> dst) {
        return dst[e.v] > dst[e.u] + e.w;
    }
};