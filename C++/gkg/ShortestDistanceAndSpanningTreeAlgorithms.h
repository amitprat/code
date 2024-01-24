#pragma once
#include "../Header.h"

class ShortestDistanceAndMinimumSpanningTree {
    static const int V = 5;
    class Edge {
    public:
        int u, v;
        int dist;
        Edge() {}
        Edge(int u, int v, int d) : u(u), v(v), dist(d) {}
        string to_string() {
            return "(" + std::to_string(u) + "-->" + std::to_string(v) + ":" + std::to_string(dist) + ")";
        }
    };

    class UnionFind {
        int V;
        int* parent;
        int* rank;
    public:
        UnionFind(int V) :V(V) {
            parent = new int[V];
            rank = new int[V];

            for (int i = 0; i < V; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }

        void Union(int x, int y) {
            int px = find(x);
            int py = find(y);

            if (px == py) return;
            if (rank[px] == rank[y]) rank[px]++;

            if (rank[px] < rank[py]) {
                parent[py] = px;
            }
            else if (rank[px] > rank[py]) {
                parent[px] = py;
            }
        }

        int find(int x) {
            int px = parent[x];

            while (px != x) {
                x = px;
                px = parent[x];
            }

            return x;
        }

        bool connected(int x, int y) {
            int px = find(x);
            int py = find(y);

            return px == py;
        }
    };
public:
    static void test() {
        ShortestDistanceAndMinimumSpanningTree obj;
        /*
        int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
        */

        /* Let us create the following graph
                     2     3
                (0)---(1)----(2)
                |     / \     |
                |    /   \    |
                6   8     5   7
                |  /       \  |
                | /         \ |
                (3)-----9----(4)
        */
        int graph[V][V] = { { 0, 2, 0, 6, 0 },
                            { 2, 0, 3, 8, 5 },
                            { 0, 3, 0, 0, 7 },
                            { 6, 8, 0, 0, 9 },
                            { 0, 5, 7, 9, 0 } };

        auto res = obj.primsForMatrix(graph);
        cout << "Mst using Prims = " << to_string(res) << endl;

        res = obj.krushkalsForMatrix(graph);
        cout << "Mst using krushkals = " << to_string(res) << endl;

        int s = 0, d = 4;
        cout << "Check if path exists between " << s << ", " << d << ": ";
        auto exists = obj.pathExists(graph, s, d);
        cout << (exists ? "True" : "False") << endl;

        cout << "Find shortest distance between " << s << " " << d << " : ";
        auto sd = obj.dijkastraForWeightedGraph(graph, s, d);
        cout << sd << endl;
    }

    // MST algos
    vector<Edge> primsForMatrix(int graph[V][V]) {
        vector<Edge> res;
        int parent[V];
        int dist[V];
        bool mstSet[V];
        for (int i = 0; i < V; i++) {
            parent[i] = -1;
            dist[i] = INT_MAX;
            mstSet[i] = false;
        }
        dist[0] = 0;

        for (int cnt = 0; cnt < V - 1; cnt++) {
            int u = minDistVertex(dist, mstSet);
            mstSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (!mstSet[v] && graph[u][v] && graph[u][v] != INT_MAX && graph[u][v] < dist[v]) {
                    parent[v] = u;
                    dist[v] = graph[u][v];
                }
            }
        }

        for (int i = 0; i < V; i++) {
            res.push_back(Edge(parent[i], i, dist[i]));
        }

        return res;
    }

    vector<Edge> krushkalsForMatrix(int graph[V][V]) {
        vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (graph[i][j]) {
                    edges.push_back(Edge(i, j, graph[i][j]));
                }
            }
        }

        sort(edges.begin(), edges.end(), [](const auto& f, const auto& s) {
            return f.dist < s.dist;
            });

        UnionFind uf(V);
        vector<Edge> result(V - 1);

        int e = 0, i = 0;
        while (e < V - 1 && i < edges.size()) {
            Edge edge = edges[i++];

            if (!uf.connected(edge.u, edge.v)) {
                uf.Union(edge.u, edge.v);
                result[e++] = edge;
            }
        }

        return result;
    }

    // check if any path exists
    bool pathExists(int graph[V][V], int s, int d) {
        unordered_set<int> visited;

        return bfs(graph, s, d, visited);
    }

    bool dfs(int graph[V][V], int s, int d, unordered_set<int>& visited) {
        visited.insert(s);
        if (s == d) return true;

        for (int v = 0; v < V; v++) {
            if (visited.find(v) == visited.end()) {
                if (dfs(graph, v, d, visited)) return true;
            }
        }

        return false;
    }

    bool bfs(int graph[V][V], int s, int d, unordered_set<int>& visited) {
        queue<int> q;
        q.push(s);
        visited.insert(s);

        while (!q.empty()) {
            auto f = q.front(); q.pop();
            if (f == d) return true;

            for (int v = 0; v < V; v++) {
                if (visited.find(v) == visited.end()) {
                    q.push(v);
                    visited.insert(v);
                }
            }
        }

        return false;
    }

    // single source/single destination path
    void bfsForUnweightedGraph() {

    }

    int dijkastraForWeightedGraph(int graph[V][V], int s, int d) {
        int dist[V];
        bool visited[V];
        int parent[V];

        for (int i = 0; i < V; i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }

        dist[0] = 0;

        for (int cnt = 0; cnt < V - 1; cnt++) {
            int u = minDistVertex(dist, visited);
            visited[u] = true;

            if (u == d) break;

            for (int v = 0; v < V; v++) {
                if (graph[u][v] && graph[u][v] != INT_MAX && !visited[v] && dist[v] > dist[u] + graph[u][v]) {
                    parent[v] = u;
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        return dist[d];
    }

    void bellmanFordForNegativeCycles() {

    }

    // single source shortest path [single source to multiple destination]
    void disjkastraForMatrix() {

    }

    void bellmanFordForMatrix() {

    }

    // Multiple source, multiple destination
    void floydWarshallForMatrix() {

    }

    int minDistVertex(int dist[V], bool mst[V]) {
        int mn = INT_MAX;
        int mnIndex = -1;
        for (int i = 0; i < V; i++) {
            if (!mst[i] && dist[i] < mn) {
                mn = dist[i];
                mnIndex = i;
            }
        }

        return mnIndex;
    }
};