#include "../header.h"

class RouteBetweenNodes
{
    class Graph
    {
    public:
        int V;
        unordered_map<int, vector<int>> adjMap;
        unordered_set<int> vertices;

        Graph(int v) : V(v) {}
        void addVertex(int src)
        {
            vertices.insert(src);
        }

        void addEdge(int src, int dst)
        {
            vertices.insert(src);
            vertices.insert(dst);

            adjMap[src].push_back(dst);
        }
    };

public:
    static void test()
    {
        Graph g(6);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(3, 4);
        g.addEdge(4, 5);
        g.addVertex(6);

        RouteBetweenNodes obj;

        int src = 1, dst = 6;

        {
            vector<int> path;
            vector<bool> visited(g.V, false);
            bool res = obj.isConnectedUsingDFS(g, src, dst, visited, path);
            if (res)
            {
                cout << "Is connected: " << path << endl;
            }
        }

        {
            bool res = obj.isConnectedUsingBFS(g, src, dst);
            if (res)
                cout << "Connected" << endl;
            else
                cout << "Not connected" << endl;
        }
    }

    bool isConnectedUsingDFS(Graph g, int src, int dst, vector<bool> visited, vector<int> &path)
    {
        if (src == dst)
        {
            path.push_back(src);
            return true;
        }

        path.push_back(src);
        visited[src] = true;

        for (auto v : g.adjMap[src])
        {
            if (!visited[v])
            {
                if (isConnectedUsingDFS(g, v, dst, visited, path))
                    return true;
            }
        }

        visited[src] = false;
        path.pop_back();

        return false;
    }

    friend std::ostream &operator<<(std::ostream &out, vector<int> &path)
    {
        for (auto u : path)
        {
            out << u << " ";
        }

        return out;
    }

    bool isConnectedUsingBFS(Graph g, int src, int dst)
    {
        vector<bool> visited(g.V, false);
        queue<int> q;
        q.push(src);
        visited[src] = true;

        while (!q.empty())
        {
            auto u = q.front();
            q.pop();
            if (u == dst)
                return true;

            for (auto v : g.adjMap[u])
            {
                if (!visited[v])
                {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }

        return false;
    }
};