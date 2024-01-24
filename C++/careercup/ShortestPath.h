#include "../header.h"

class Dijkastra
{
    struct Edge
    {
        int dst, wt;
        Edge(int dst, int wt) : dst(dst), wt(wt) {}
    };

    struct Graph
    {
        unordered_set<int> vertices;
        unordered_map<int, vector<Edge>> adjMap;

        // directed graph
        void addEdge(int src, int dst, int wt)
        {
            vertices.insert(src);
            vertices.insert(dst);

            adjMap[src].push_back(Edge(dst, wt));
            adjMap[dst].push_back(Edge(src, wt));
        }
    };

public:
    static void test()
    {
        Graph g;
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

        Dijkastra obj;
        int src = 0, dst = 3;
        int distance = obj.dijkastraUsingPQ(g, src, dst);
        cout << "Shortest distance from " << src << " to " << dst << " is " << distance << endl;

        map<int, int> distances1 = obj.dijkastraUsingPQ(g, src);
        cout << "Shorted distances from " << src << " are : " << distances1 << endl;

        map<int, int> distances2 = obj.dijkastraUsingSet(g, src);
        cout << "Shorted distances (using set) from " << src << " are : " << distances2 << endl;
    }

    map<int, int> dijkastraUsingPQ(Graph g, int src)
    {
        map<int, int> distMap;

        using p = pair<int, int>;
        priority_queue<p, vector<p>, greater<p>> pq;
        pq.push({0, src});

        vector<int> dist(g.vertices.size(), INT_MAX);
        dist[src] = 0;

        while (!pq.empty())
        {
            auto cur = pq.top();
            pq.pop();

            int u = cur.second;
            distMap[u] = dist[u];

            for (auto next : g.adjMap[u])
            {
                int v = next.dst;
                int wt = next.wt;

                if (dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;

                    pq.push({dist[v], v});
                }
            }
        }

        return distMap;
    }

    int dijkastraUsingPQ(Graph g, int src, int dst)
    {
        using p = pair<int, int>;
        priority_queue<p, vector<p>, greater<p>> pq;
        pq.push({0, src});

        vector<int> dist(g.vertices.size(), INT_MAX);
        dist[src] = 0;

        while (!pq.empty())
        {
            auto cur = pq.top();
            pq.pop();

            int u = cur.second;
            if (u == dst)
                return dist[u];

            for (auto next : g.adjMap[u])
            {
                int v = next.dst;
                int wt = next.wt;

                if (dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;

                    pq.push({dist[v], v});
                }
            }
        }

        return -1;
    }

    map<int, int> dijkastraUsingSet(Graph g, int src)
    {
        set<pair<int, int>> s;
        vector<int> dist(g.vertices.size(), INT_MAX);
        dist[src] = 0;
        s.insert({dist[src], src});
        map<int, int> result;

        while (!s.empty())
        {
            auto cur = s.begin();
            int u_wt = cur->first;
            int u = cur->second;
            s.erase(cur);
            result.insert({u, u_wt});

            for (auto next : g.adjMap[u])
            {
                auto v = next.dst;
                auto v_wt = next.wt;

                if (dist[v] > dist[u] + v_wt)
                {
                    if (dist[v] != INT_MAX)
                        s.erase(s.find({dist[v], v}));

                    dist[v] = dist[u] + v_wt;
                    s.insert({dist[v], v});
                }
            }
        }

        return result;
    }
};

class DijkastraMatrix
{
public:
    static void test()
    {
        vector<vector<int>> graph =
            {{0, 4, 0, 0, 0, 0, 0, 8, 0},
             {4, 0, 8, 0, 0, 0, 0, 11, 0},
             {0, 8, 0, 7, 0, 4, 0, 0, 2},
             {0, 0, 7, 0, 9, 14, 0, 0, 0},
             {0, 0, 0, 9, 0, 10, 0, 0, 0},
             {0, 0, 4, 14, 10, 0, 2, 0, 0},
             {0, 0, 0, 0, 0, 2, 0, 1, 6},
             {8, 11, 0, 0, 0, 0, 1, 0, 7},
             {0, 0, 2, 0, 0, 0, 6, 7, 0}};

        // Function call
        DijkastraMatrix obj;
        int src = 0;
        map<int, int> distances1 = obj.dijkstra(graph, src);
        cout << "Shorted distances from " << src << " are : " << distances1 << endl;
    }

private:
    map<int, int> dijkstra(vector<vector<int>> graph, int src)
    {
        int V = graph.size();
        vector<bool> visited(V, false);
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i = 0; i < V - 1; i++)
        {
            int u = minDistVertex(dist, visited);
            visited[u] = true;

            for (int v = 0; v < V; v++)
            {
                if (graph[u][v] && !visited[v] && dist[u] != INT_MAX && dist[v] > dist[u] + graph[u][v])
                {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        map<int, int> result;
        for (int i = 0; i < V; i++)
        {
            result[i] = dist[i];
        }

        return result;
    }

    int minDistVertex(vector<int> dist, vector<bool> visited)
    {
        int mnVertex = -1;
        for (int i = 0; i < dist.size(); i++)
        {
            if (!visited[i])
            {
                if (mnVertex == -1 || dist[i] < dist[mnVertex])
                {
                    mnVertex = i;
                }
            }
        }

        return mnVertex;
    }
};

class BellmanFord
{
    struct Edge
    {
        int src, dst, wt;
        Edge(int src, int dst, int wt) : src(src), dst(dst), wt(wt) {}
    };

    struct Graph
    {
        unordered_set<int> vertices;
        vector<Edge> edges;

        // directed graph
        void addEdge(int src, int dst, int wt)
        {
            vertices.insert(src);
            vertices.insert(dst);

            edges.push_back(Edge(src, dst, wt));
        }
    };

public:
    static void test()
    {
        {
            Graph g;
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

            BellmanFord obj;
            int src = 0;
            map<int, int> distances = obj.bellmanFord(g, src);
            cout << "Shorted distances from " << src << " are : " << distances << endl;
        }

        {
            Graph g;
            g.addEdge(0, 1, -1);
            g.addEdge(0, 2, 4);
            g.addEdge(1, 2, 3);
            g.addEdge(1, 3, 2);
            g.addEdge(1, 4, 2);
            g.addEdge(3, 2, 5);
            g.addEdge(3, 1, 1);
            g.addEdge(4, 3, -3);

            BellmanFord obj;
            int src = 0;
            map<int, int> distances = obj.bellmanFord(g, src);
            cout << "Shorted distances from " << src << " are : " << distances << endl;
        }
    }

    map<int, int> bellmanFord(Graph g, int src)
    {
        int V = g.vertices.size();
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i = 1; i <= V - 1; i++)
        {
            for (auto &edge : g.edges)
            {
                auto u = edge.src;
                auto v = edge.dst;
                auto w = edge.wt;

                if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                }
            }
        }

        for (auto &edge : g.edges)
        {
            auto u = edge.src;
            auto v = edge.dst;
            auto w = edge.wt;

            if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
            {
                cout << "Graph contains negative cycle" << endl;
            }
        }

        map<int, int> result;
        for (int i = 0; i < V; i++)
        {
            result[i] = dist[i];
        }

        return result;
    }
};

class ShortestPath
{

public:
    static void test()
    {
        DijkastraMatrix::test();

        Dijkastra::test();

        BellmanFord::test();
    }
};