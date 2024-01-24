#include "../header.h"

class MinimumSpanningTree
{
public:
    static void test()
    {
        MinimumSpanningTree obj;
        obj.primsTest();
    }

private:
    struct Edge
    {
        int src, dst, wt;
        Edge(int src, int dst, int wt) : src(src), dst(dst), wt(wt) {}
        string to_string()
        {
            stringstream ss;
            ss << "{" << src << "->" << dst << ":" << wt << "}";

            return ss.str();
        }
    };
    struct Graph
    {
        Graph(int V) : V(V) {}

        int V;
        vector<Edge> edges;
        unordered_map<int, vector<Edge>> adjMap;

        void addEdge(int src, int dst, int wt)
        {
            edges.push_back(Edge(src, dst, wt));
            adjMap[src].push_back(Edge(src, dst, wt));
        }
    };

    class UnionFind
    {
        int V;
        vector<int> parent;
        vector<int> rank;

    public:
        UnionFind(int V) : V(V)
        {
            parent.resize(V);
            rank.resize(V);

            for (int i = 0; i < V; i++)
            {
                parent[i] = -1;
                rank[i] = 1;
            }
        }
        void connect(int src, int dst)
        {
            auto u_parent = find(src);
            auto v_parent = find(dst);

            if (connected(u_parent, v_parent))
                return;

            if (rank[u_parent] < rank[v_parent])
            {
                parent[u_parent] = v_parent;
            }
            else if (rank[u_parent] > rank[v_parent])
            {
                parent[v_parent] = u_parent;
            }
            else
            {
                rank[u_parent]++;
                parent[v_parent] = u_parent;
            }
        }

        int find(int src)
        {
            while (parent[src] != -1)
            {
                src = parent[src];
            }
            return src;
        }

        bool connected(int src, int dst)
        {
            auto u_parent = find(src);
            auto v_parent = find(dst);

            return u_parent == v_parent;
        }
    };

    void krushkalsTest()
    {
        Graph g(4);
        g.addEdge(0, 1, 10);
        g.addEdge(1, 3, 15);
        g.addEdge(2, 3, 4);
        g.addEdge(2, 0, 6);
        g.addEdge(0, 3, 5);

        auto result = krushkals(g);
        cout << "Krushkals: " << to_string(result) << endl;
    }

    vector<Edge> krushkals(Graph g)
    {
        sort(g.edges.begin(), g.edges.end(), [](auto &f, auto &s)
             { return f.wt < s.wt; });

        vector<Edge> result;
        UnionFind uf(g.V);
        int i = 0;
        for (auto e = 0; e < g.V; e++)
        {
            auto edge = g.edges[e];
            if (!uf.connected(edge.src, edge.dst))
            {
                uf.connect(edge.src, edge.dst);
                result.push_back(edge);
                i++;
            }
            if (i == g.V - 1)
                break;
        }

        return result;
    }

    string to_string(vector<Edge> edges)
    {
        stringstream ss;
        for (Edge edge : edges)
        {
            ss << edge.to_string() << ", ";
        }

        return ss.str();
    }

private:
    void primsTest()
    {
        Graph g(4);
        g.addEdge(0, 1, 10);
        g.addEdge(1, 3, 15);
        g.addEdge(2, 3, 4);
        g.addEdge(2, 0, 6);
        g.addEdge(0, 3, 5);

        prims(g);
    }

    void prims(Graph g)
    {
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> pq;

        int src = 0;
        vector<bool> visited(g.V, false);
        vector<int> parent(g.V, -1);
        vector<int> dist(g.V, INT_MAX);
        parent[src] = -1;
        dist[src] = 0;
        pq.push({dist[src], src});

        while (!pq.empty())
        {
            auto cur = pq.top();
            pq.pop();

            auto u = cur.second;
            if (visited[u])
                continue;
            visited[u] = true;

            for (auto next : g.adjMap[u])
            {
                auto v = next.dst;
                auto wt = next.wt;
                if (!visited[v] && dist[v] > wt)
                {
                    dist[v] = wt;
                    pq.push({dist[v], v});
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < g.V; i++)
        {
            if (visited[i])
            {
                cout << parent[i] << "->" << i << ":" << dist[parent[i]] << endl;
            }
        }
    }
};