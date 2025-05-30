#pragma once
#include "../header.h"

class MinimumSpanningTreeInAdjMatrixGraph {
   public:
    static void test() {
        MinimumSpanningTreeInAdjMatrixGraph obj;
        vector<vector<int>> g = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0}};

        auto [dist, parent] = obj.minimumSpanningTreeUsingPrims(g);
        int minSpanningDist = 0;
        for (int v = 1; v < g.size(); v++) {
            minSpanningDist += dist[v];
            auto u = parent[v];

            cout << format("{} -> {} : {}", u, v, dist[v]) << endl;
        }
        cout << "Minimum spanning distance: " << minSpanningDist << endl;
    }

   private:
    pair<vector<int>, vector<int>> minimumSpanningTreeUsingPrims(const vector<vector<int>>& g) {
        vector<int> dst(g.size(), INT_MAX);
        vector<int> parent(g.size(), -1);
        vector<bool> visited(g.size(), false);

        dst[0] = 0;  // start position

        for (int cnt = 0; cnt < g.size() - 1; cnt++) {
            int u = minVertex(dst, visited);
            visited[u] = true;

            for (int v = 0; v < g.size(); v++) {
                if (g[u][v] && !visited[v]) {
                    if (g[u][v] < dst[v]) {
                        dst[v] = g[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        return {dst, parent};
    }

   private:
    int minVertex(const vector<int>& dst, const vector<bool>& visited) {
        int mn = INT_MAX;
        int mnIndex = -1;

        for (auto i = 0; i < dst.size(); i++) {
            if (!visited[i] && dst[i] < mn) {
                mn = dst[i];
                mnIndex = i;
            }
        }

        return mnIndex;
    }
};

class MinimumSpanningTreeInAdjListGraph {
    struct Graph {
       private:
        struct Edge {
            int v, w;
        };

       public:
        int V;
        unordered_map<int, vector<Edge>> edges;

       public:
        Graph(int v) : V(v) {}

        void addEdge(int u, int v, int w) {
            edges[u].push_back({v, w});
            edges[v].push_back({u, w});
        }
    };

    class Minheap {
       public:
        struct KeyValuePair {
            int weight;
            int vertex;
        };
        vector<KeyValuePair> arr;  // {w, u}

       public:
        void insert(KeyValuePair kvp) {
            arr.push_back(kvp);

            upHeapify(arr.size() - 1);
        }

        KeyValuePair pop() {
            auto res = arr[0];
            arr[0] = arr[arr.size() - 1];
            arr.pop_back();

            downHeapify(0);

            return res;
        }

        int size() { return arr.size(); }

       private:
        void downHeapify(int index) {
            int mn = index;
            int lp = left(index);
            int rp = right(index);

            if (lp < arr.size() && arr[lp].weight < arr[mn].weight) {
                mn = lp;
            }
            if (rp < arr.size() && arr[rp].weight < arr[mn].weight) {
                mn = rp;
            }

            if (mn != index) {
                swap(arr[mn], arr[index]);
                downHeapify(mn);
            }
        }

        void upHeapify(int index) {
            int p = parent(index);
            while (index != 0 && arr[p].weight > arr[index].weight) {
                swap(arr[p], arr[index]);
                index = p;
                p = parent(index);
            }
        }

       private:
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
        MinimumSpanningTreeInAdjListGraph obj;

        Graph g(9);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 7, 8);
        g.addEdge(1, 2, 8);
        g.addEdge(1, 7, 11);
        g.addEdge(2, 3, 7);
        g.addEdge(2, 8, 2);
        g.addEdge(2, 5, 4);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 14);
        g.addEdge(4, 5, 10);
        g.addEdge(5, 6, 2);
        g.addEdge(6, 7, 1);
        g.addEdge(6, 8, 6);
        g.addEdge(7, 8, 7);

        auto res = obj.minimumSpanningTreePrimsUsingSTL(g);
        auto dist = res.first;
        auto parent = res.second;
        int minSpanningDist = 0;

        for (int v = 1; v < g.V; v++) {
            minSpanningDist += dist[v];

            auto u = parent[v];
            cout << format("{} -> {} : {}", u, v, dist[v]);
        }
        cout << "Minimum spanning distance: " << minSpanningDist << endl;
    }

    pair<vector<int>, vector<int>> minimumSpanningTreePrimsUsingHeap(Graph g) {
        unordered_set<int> visited;
        vector<int> dist(g.V, INT_MAX);
        vector<int> parent(g.V, -1);
        int src = 0;

        Minheap heap;
        dist[src] = 0;
        heap.insert({dist[src], src});  // {w,v}

        while (heap.size() != 0) {
            auto u = heap.pop();
            if (visited.count(u.vertex) != 0) continue;

            visited.insert(u.vertex);

            for (auto e : g.edges[u.vertex]) {
                if (visited.count(e.v) == 0 && e.w < dist[e.v]) {
                    dist[e.v] = e.w;
                    parent[e.v] = u.vertex;

                    heap.insert({dist[e.v], e.v});
                }
            }
        }

        return {dist, parent};
    }

   private:
    pair<vector<int>, vector<int>> minimumSpanningTreePrimsUsingSTL(Graph g) {
        unordered_set<int> visited;
        vector<int> dist(g.V, INT_MAX);
        vector<int> parent(g.V, -1);
        int src = 0;

        using p = pair<int, int>;                     // {w,v}
        priority_queue<p, vector<p>, greater<p>> pq;  // minheap
        dist[src] = 0;
        pq.push({dist[src], src});  // {w,v}

        while (!pq.empty()) {
            auto [w, u] = pq.top();
            pq.pop();

            if (visited.count(u) != 0) continue;
            visited.insert(u);

            for (auto e : g.edges[u]) {
                if (visited.count(e.v) == 0 && e.w < dist[e.v]) {
                    dist[e.v] = e.w;
                    parent[e.v] = u;

                    pq.push({dist[e.v], e.v});
                }
            }
        }

        return {dist, parent};
    }
};

class MinimumSpanningTreeKrushkalsInEdgeGraph {
    struct Edge {
        int u, v, w;
    };

    struct Graph {
        int V;
        vector<Edge> edges;

        Graph(int v) : V(v) {}
        void addEdge(int u, int v, int w) {
            edges.push_back({u, v, w});
            edges.push_back({v, u, w});
        }
    };

    struct UnionFind {
        vector<int> parent;
        vector<int> rank;

        UnionFind(int sz) {
            parent.resize(sz);
            rank.resize(sz);

            for (int i = 0; i < sz; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }

        int find(int p) {
            while (parent[p] != p) {
                p = parent[p];
            }

            return p;
        }

        void join(int p, int q) {
            auto pRoot = find(p);
            auto qRoot = find(q);

            if (rank[pRoot] == rank[qRoot]) rank[pRoot]++;

            if (rank[pRoot] < rank[qRoot]) {
                parent[pRoot] = qRoot;
            } else if (rank[qRoot] < rank[pRoot]) {
                parent[qRoot] = pRoot;
            }
        }

        bool connected(int p, int q) {
            return find(p) == find(q);
        }
    };

   public:
    static void test() {
        MinimumSpanningTreeKrushkalsInEdgeGraph obj;

        Graph g(4);
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 6);
        g.addEdge(0, 3, 5);
        g.addEdge(1, 3, 15);
        g.addEdge(2, 3, 4);

        vector<Edge> edges = obj.minimumSpanningTreeKrushkalsUsingUnionFind(g);
        int minSpanningDist = 0;
        int cnt = 0;

        for (auto e : edges) {
            minSpanningDist += e.w;
            cout << format("{} -> {} : {}", e.u, e.v, e.w);
        }
        cout << "Minimum spanning distance: " << minSpanningDist << endl;
    }

   private:
    vector<Edge> minimumSpanningTreeKrushkalsUsingUnionFind(Graph g) {
        sort(g.edges.begin(), g.edges.end(), [](auto f, auto s) { return f.w < s.w; });

        vector<Edge> edges;

        UnionFind uf(g.V);

        int e = 0;
        while (edges.size() < g.V - 1 && e < g.edges.size()) {
            auto edge = g.edges[e++];  // pick first edge
            if (!uf.connected(edge.u, edge.v)) {
                edges.push_back(edge);
                uf.join(edge.u, edge.v);
            }
        }

        return edges;
    }
};

class MinimumSpanningTree {
   public:
    static void test() {
        cout << "Minimum spanning tree using prims for adjacency matrix: " << endl;
        MinimumSpanningTreeInAdjMatrixGraph obj;
        obj.test();

        cout << "Minimum spanning tree using prims for adjacency list: " << endl;
        MinimumSpanningTreeInAdjListGraph obj1;
        obj1.test();

        cout << "Minimum spanning tree using krushkals for edge list: " << endl;
        MinimumSpanningTreeKrushkalsInEdgeGraph obj2;
        obj2.test();
    }
};