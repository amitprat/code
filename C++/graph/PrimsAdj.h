#pragma once
#include "../header.h"
using namespace std;

class Node
{
public:
    int d, w;
    Node() {}
    Node(int d, int w) :d(d), w(w) {}
    string to_string() {
        return "(" + std::to_string(d) + ", " + std::to_string(w) + ")";
    }
};
class Graph
{
public:
    int V;
    unordered_map<int, vector<Node>> adjList;

public:
    Graph(int v) : V(v) {}
    void addEdge(int s, int d, int w) {
        adjList[s].push_back(Node(d, w));
        adjList[d].push_back(Node(s, w));
    }
    Graph(vector<tuple<int, int, int>> v)
    {
        for (auto i : v) {
            adjList[get<0>(i)].push_back(Node(get<1>(i), get<2>(i)));
            adjList[get<1>(i)].push_back(Node(get<0>(i), get<2>(i)));
        }
        this->V = adjList.size();
    }

    string to_string() {
        stringstream ss;
        ss << "[" << endl;
        for (auto entry : adjList) {
            ss << setw(4) << "{" << entry.first;
            ss << ":";
            for (auto v : entry.second) ss << v.to_string() << " ";
            ss << "}";
            ss << endl;
        }
        ss << "]";

        return ss.str();
    }
};

template <class T>
class Minheap
{
private:
    vector<T> nodes;
    int sz = 0;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void upHeapify(int c)
    {
        int p = parent(c);
        while (c != 0 && nodes[p].w > nodes[c].w)
        {
            swap(nodes[p], nodes[c]);
            c = p;
            p = parent(c);
        }
    }

    void downHeapify(int i)
    {
        int smallest = i;
        int l = left(i);
        if (l < sz && nodes[l].w < nodes[smallest].w) smallest = l;

        int r = right(i);
        if (r < sz && nodes[r].w < nodes[smallest].w) smallest = r;

        if (smallest != i)
        {
            swap(nodes[i], nodes[smallest]);
            downHeapify(smallest);
        }
    }

public:
    Minheap(int v)
    {
        sz = v;
        nodes.resize(sz);
    }

    void add(int key, T val)
    {
        nodes[key] = val;
    }

    void build()
    {
        for (int i = sz / 2 - 1; i >= 0; i--) {
            downHeapify(i);
        }
    }

    T pop()
    {
        T top = nodes.front();
        nodes[0] = nodes[sz - 1];
        sz--;
        nodes.pop_back();
        downHeapify(0);

        return top;
    }
    bool empty() { return sz == 0; }
    int size() { return sz; }
    int weight(int k) {
        for (int i = 0; i < sz; i++) {
            if (nodes[i].d == k) {
                return nodes[i].w;
            }
        }
    }
    void decreaseKey(int k, int w)
    {
        for (int i = 0; i < sz; i++) {
            if (nodes[i].d == k) {
                nodes[i].w = w;
                upHeapify(i);
                break;
            }
        }
    }
};

class PrimsAdj
{
public:
    static void test()
    {
        PrimsAdj obj;
        vector<Graph> graphs = {
            Graph({{0,1,2},{1,2,4},{2,0,1}}),
            Graph({{0,1,4}, {0,7,8},{1,2,8},{1,7,11},{2,3,7},{2,8,2},{2,5,4},{3,4,9},{3,5,14},{4,5,10},{5,6,2},{6,7,1},{6,8,6},{7,8,7}})
        };

        for (auto graph : graphs) {
            cout << "Current Grpah: " << endl;
            cout << graph.to_string() << endl;

            cout << "Finding MST: " << endl;
            obj.findMst(graph);
        }
    }

    void findMst(Graph g)
    {
        Minheap<Node> heap(g.V);
        int src = 0;
        bool* visited = new bool[g.V];
        int* parent = new int[g.V];
        parent[src] = -1;
        heap.add(src, Node(src, 0));

        for (int i = 1; i < g.V; i++) {
            visited[i] = false;
            heap.add(i, Node(i, INT_MAX));
        }
        heap.build();

        while (!heap.empty())
        {
            auto minWtVertex = heap.pop();
            visited[minWtVertex.d] = true;
            cout << parent[minWtVertex.d] << "->" << minWtVertex.d << endl;

            for (auto child : g.adjList[minWtVertex.d]) {
                if (!visited[child.d]) {
                    if (child.w < heap.weight(child.d)) {
                        heap.decreaseKey(child.d, child.w);
                        parent[child.d] = minWtVertex.d;
                    }
                }
            }
        }

        printMst(parent, g);
    }

    void printMst(int parent[], Graph g)
    {
        cout << "MST = ";
        cout << "{";
        for (int i = 1; i < g.V; i++) {
            cout << "(" << parent[i] << "->" << i << ")";
            cout << " ";
        }
        cout << "}";
        cout << endl;
    }
};