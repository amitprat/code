#pragma once
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
using namespace std;
using VertexId = uint64_t;
using Weight = uint64_t;

struct Node
{
    VertexId id;
    Weight w;
    Node(VertexId id, Weight w) :id(id), w(w) {}
};
class Graph
{
public:
    unordered_map<VertexId, vector<Node>> vertices;
    Graph(vector<pair<VertexId, vector<Node>>> nodes)
    {
        for (auto node : nodes) vertices.insert(node);
    }

    int size() { return vertices.size(); }
};

class Minheap
{
public:
    struct Node {
        int id;
        int distance;
    };
private:
    vector<Node> nodes;
    unordered_map<int, int> indices;
    int sz = 0;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int index(int id) { return indices[id]; }
    void swapPos(int i, int j) {
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    void upHeapify(int c)
    {
        int p = parent(c);
        while (c != 0 && nodes[p].distance > nodes[c].distance)
        {
            swap(nodes[p], nodes[c]);
            swapPos(p, c);
            c = p;
            p = parent(c);
        }
    }

    void downHeapify(int i)
    {
        int smallest = i;
        int l = left(i);
        if (l < sz && nodes[l].distance < nodes[smallest].distance) smallest = l;

        int r = right(i);
        if (r < sz && nodes[r].distance < nodes[smallest].distance) smallest = r;

        if (smallest != i)
        {
            swap(nodes[i], nodes[smallest]);
            swapPos(i, smallest);
            downHeapify(smallest);
        }
    }

public:
    Minheap(int v)
    {
        sz = v;
    }

    void add(int key, int val)
    {
        nodes.push_back({ key, val });
        indices.insert({ key, nodes.size() - 1 });
    }

    void build()
    {
        int end = sz / 2 - 1;
        for (int i = end; i >= 0; i--)
        {
            downHeapify(i);
        }
    }

    Node pop()
    {
        auto top = nodes.front();
        nodes[0] = nodes[sz - 1];
        indices[nodes[0].id] = 0;

        sz--;
        nodes.pop_back();
        indices.erase(top.id);

        downHeapify(0);

        return top;
    }
    bool empty() { return sz == 0; }
    int size() { return sz; }
    int weight(int i) {
        int idx = index(i);
        cout << "idx:" << idx << endl;
        return nodes[idx].distance;
    }
    void decreaseKey(int k, int w)
    {
        int idx = index(k);
        nodes[idx].distance = w;
        upHeapify(idx);
    }
    bool isInMinheap(int v)
    {
        return indices.size() > v && indices[v] < sz;
    }

    static void test()
    {
        Minheap heap(3);
        heap.add(0, 5);
        heap.add(1, 2);
        heap.add(2, 3);
        heap.build();
        heap.decreaseKey(0, 1);

        while (!heap.empty()) {
            auto res = heap.pop();
            cout << res.id << " " << res.distance << endl;
        }
    }
};

class Dijkstra
{
public:
    static void test()
    {
        Dijkstra obj;
        vector<Graph> graphs = {
            Graph({{0, {{1,10},{2,5}}}, {1, {{2,30},{3,9}}}, {2, {{3,7}}}, {3, {}} })
        };
        for (auto g : graphs)
        {
            int src = 0;
            obj.dijkstra(src, g);
        }
    }

    void dijkstra(int src, Graph g)
    {
        Minheap heap(g.size());
        vector<VertexId> parents;
        vector<VertexId> distances;
        parents.resize(g.size());
        distances.resize(g.size());
        for (int i = 0; i < g.size(); i++) {
            heap.add(i, INT_MAX);
            parents[i] = INT_MAX;
            distances[i] = INT_MAX;
        }
        heap.build();
        heap.decreaseKey(src, 0);
        distances[0] = 0;

        while (!heap.empty())
        {
            auto current = heap.pop(); // pop min distance node
            distances[current.id] = current.distance;
            for (auto child : g.vertices[current.id])
            {
                if (current.distance != INT_MAX)
                {
                    parents[child.id] = current.id;
                    heap.decreaseKey(child.id, current.distance + child.w);
                }
            }
        }

        printArr(src, distances, parents);
    }

    void printArr(VertexId src, vector<VertexId> distances, vector<VertexId> parents)
    {
        cout << "Vertex Distance from Source:" << endl;
        for (VertexId i = 0; i < distances.size(); i++) {
            cout << src << "->" << i << "=" << distances[i] << endl;
        }
    }
};