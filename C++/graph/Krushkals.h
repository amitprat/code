#pragma once
#include "../header.h"
using namespace std;

class Edge
{
public:
    int source;
    int destination;
    int weight;

    Edge(int source, int destination, int weight) : source(source), destination(destination), weight(weight) {}

    string str() {
        stringstream ss;
        ss << "(";
        ss << source << ", ";
        ss << destination << ", ";
        ss << weight << ")";

        return ss.str();
    }
};

class Graph
{
public:
    unordered_set<int> vertices;
    vector<Edge> edges;

    void addEdge(int s, int d, int w)
    {
        edges.push_back(Edge(s, d, w));
        vertices.insert(s);
        vertices.insert(d);
    }

    void sortEdgesByWeight()
    {
        sort(edges.begin(), edges.end(), [](auto l, auto r) {return l.weight < r.weight; });
    }

    string str()
    {
        stringstream ss;
        ss << "{";
        for (auto e : edges) {
            ss << e.str() << ", ";
        }
        ss << "}";

        return ss.str();
    }
};

class UnionFind
{
private:
    int* parent = nullptr;
    int* rank = nullptr;
    int sz = 0;
public:
    UnionFind(int V)
    {
        sz = V;
        parent = new int[sz];
        rank = new int[sz];

        for (int i = 0; i < sz; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    void Union(int s, int e)
    {
        int proot = Find(s);
        int eroot = Find(e);
        if (proot != eroot) {
            if (rank[proot] < rank[eroot]) {
                parent[eroot] = proot;
                rank[eroot]++;
            }
            else {
                parent[proot] = eroot;
                rank[proot]++;
            }
        }
    }

    int Find(int e)
    {
        int eroot = parent[e];
        while (eroot != e) {
            e = eroot;
            eroot = parent[e];
        }

        return eroot;
    }

    bool Connected(int s, int d)
    {
        return Find(s) == Find(d);
    }
};

class Krushkals
{
public:
    void test()
    {
        Graph g;
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 6);
        g.addEdge(0, 3, 5);
        g.addEdge(1, 3, 15);
        g.addEdge(2, 3, 4);
        cout << "Graph :" << g.str() << endl;

        auto res = findMst(g);
        cout << "Result = " << to_string(res) << endl;
    }

    vector<Edge> findMst(Graph g)
    {
        vector<Edge> result;
        g.sortEdgesByWeight();
        int E = g.edges.size();
        int V = g.vertices.size();
        int i = 0;
        UnionFind uf(V);
        int e = 0;
        while (i < E && e < V - 1)
        {
            auto newEdge = g.edges[i];
            if (!uf.Connected(newEdge.source, newEdge.destination))
            {
                result.push_back(newEdge);
                e++;
                uf.Union(newEdge.source, newEdge.destination);
            }
            i++;
        }

        return result;
    }

    string to_string(vector<Edge> res)
    {
        stringstream ss;
        ss << "{";
        for (auto s : res) {
            ss << s.str() << ", ";
        }
        ss << "}";

        return ss.str();
    }
};