#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template <class T>
class Graph
{
public:
    int V;
    unordered_set<T> vertices;
    unordered_map<T, vector<T>> edges;

    Graph() {}
    Graph(int V) : V(V) {}
    Graph(vector<T> v) {
        V = v.size();
        for (auto u : v) vertices.insert(u);
    }

    void addEdge(T a, T b)
    {
        vertices.insert(a);
        vertices.insert(b);
        edges[a].push_back(b);
    }
};

class BuildOrder
{
public:
    static void test()
    {
        Graph<char> g({ 'a','b','c','d','e','f' });
        g.addEdge('a', 'd');
        g.addEdge('f', 'b');
        g.addEdge('b', 'd');
        g.addEdge('f', 'a');
        g.addEdge('d', 'c');

        BuildOrder obj;
        stack<char> order = obj.getBuildOrder(g);
        while (!order.empty()) {
            cout << order.top() << " ";
            order.pop();
        }
        cout << endl;
    }

    stack<char> getBuildOrder(Graph<char> g)
    {
        unordered_set<char> visited;
        stack<char> st;

        for (auto u : g.vertices) {
            if (visited.find(u) == visited.end())
                dfs(g, visited, u, st);
        }

        return st;
    }

    void dfs(Graph<char> g, unordered_set<char>& visited, char u, stack<char>& st)
    {
        visited.insert(u);
        for (auto v : g.edges[u]) {
            if (visited.find(v) == visited.end()) {
                dfs(g, visited, v, st);
            }
        }
        st.push(u);
    }
};