#pragma once
#include "../Header.h"

class Dijkastra {
public:
    static void test() {
        Dijkastra obj;
        vector<vector<int>> graph = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                    { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                    { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                    { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                    { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                    { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                    { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                    { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                    { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

        int s = 0;
        vector<int> dist = obj.dijkstra(graph, s);
        for (auto i = 0; i < dist.size(); i++) {
            cout << "Min distance from " << s << " to " << i << " = " << dist[i] << endl;
        }
    }

    vector<int> dijkstra(vector<vector<int>> graph, int s) {
        vector<int> dist(graph.size(), INT_MAX);
        dist[s] = 0;
        vector<bool> visited(graph.size(), false);

        for (int cnt = 0; cnt < graph.size() - 1; cnt++) {
            int u = minWeightVertex(dist, visited);
            visited[u] = true;
            if (dist[u] != INT_MAX) {
                for (int v = 0; v < graph.size(); v++) {
                    if (graph[u][v] && !visited[v] &&
                        dist[u] + graph[u][v] < dist[v]) {
                        dist[v] = dist[u] + graph[u][v];
                    }
                }
            }
        }

        return dist;
    }

private:
    int minWeightVertex(vector<int> dist, vector<bool> visited) {
        int r = -1;
        int mnW = INT_MAX;
        for (int i = 0; i < dist.size(); i++) {
            if (!visited[i] && dist[i] < mnW) {
                r = i;
                mnW = dist[i];
            }
        }
        return r;
    }
};

class DijkastraAdjGraph {
    class Graph {
    public:
        class Edge {
        public:
            int v, w;
            Edge(int v, int w) :v(v), w(w) {}
        };
        unordered_map<int, vector<Edge>> vertices;
        void add(int u) {
            vertices.insert({ u, {} });
        }

        void add(int u, int v, int w) {
            vertices[u].push_back(Edge(v, w));
            vertices[v].push_back(Edge(u, w));
        }

        vector<Edge> edges(int s) {
            return vertices[s];
        }
    };

    class Minheap {
        vector<pair<int, int>> arr;
        unordered_map<int, int> positions;
    public:
        void put(pair<int, int> u) {
            if (exits(u))  update(u);
            else insert(u);
        }
        int size() { return arr.size(); }
        pair<int, int> pop() {
            auto res = arr[0];
            arr[0] = arr[arr.size() - 1];
            positions[arr[0].first] = 0;
            positions.erase(res.first);
            arr.pop_back();
            downHeapify(0);

            return res;
        }

        int get(int u) {
            return arr[positions[u]].second;
        }
        bool contains(int u) {
            return positions.find(u) != positions.end();
        }
    private:
        bool exits(pair<int, int> u) { return positions.find(u.first) != positions.end(); }
        void update(pair<int, int> u) {
            int p = positions[u.first];
            arr[p] = u;
            positions[u.first] = p;
            if (u.second > arr[p].second) downHeapify(p);
            else upHeapify(p);
        }
        void insert(pair<int, int> u) {
            arr.push_back(u);
            positions[u.first] = arr.size() - 1;
            upHeapify(arr.size() - 1);
        }
        void downHeapify(int p) {
            int mn = p;
            int lp = left(p);
            if (lp < arr.size() && arr[lp].second < arr[mn].second) { mn = lp; }
            int rp = right(p);
            if (rp < arr.size() && arr[rp].second < arr[mn].second) { mn = rp; }

            if (mn != p) {
                swap(arr[mn], arr[p]);
                swap(positions[arr[mn].first], positions[arr[p].first]);
                downHeapify(mn);
            }
        }
        void upHeapify(int u) {
            int p = parent(u);
            while (u != 0 && arr[p].second > arr[u].second) {
                swap(arr[p], arr[u]);
                swap(positions[arr[p].first], positions[arr[u].first]);
                u = p;
                p = parent(u);
            }
        }
        int parent(int u) {
            return (u - 1) / 2;
        }
        int left(int u) {
            return 2 * u + 1;
        }
        int right(int u) {
            return 2 * u + 2;
        }
    };
public:
    static void test() {
        DijkastraAdjGraph obj;
        Graph g;
        g.add(0, 1, 4);
        g.add(0, 7, 8);
        g.add(1, 2, 8);
        g.add(1, 7, 11);
        g.add(2, 3, 7);
        g.add(2, 8, 2);
        g.add(2, 5, 4);
        g.add(3, 4, 9);
        g.add(3, 5, 14);
        g.add(4, 5, 10);
        g.add(5, 6, 2);
        g.add(6, 7, 1);
        g.add(6, 8, 6);
        g.add(7, 8, 7);

        int s = 0;
        auto dist = obj.dijkstra(g, s);
        for (auto i = 0; i < dist.size(); i++) {
            cout << "Min distance from " << s << " to " << i << " = " << dist[i] << endl;
        }
    }

    vector<int> dijkstra(Graph g, int s) {
        Minheap mh;
        for (auto v : g.vertices) {
            mh.put({ v.first, INT_MAX });
        }
        mh.put({ s, 0 });
        vector<int> dist(g.vertices.size(), INT_MAX);

        while (mh.size() != 0) {
            auto u = mh.pop();
            dist[u.first] = u.second;

            for (auto v : g.edges(u.first)) {
                if (mh.contains(v.v)) {
                    int wt = mh.get(v.v);
                    if (u.second + v.w < wt) {
                        mh.put({ v.v, u.second + v.w });
                    }
                }
            }
        }

        return dist;
    }
};