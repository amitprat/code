#pragma once
#include "../Header.h"

class ConnectedComponentsInUndirectedGraph {
    struct Graph {
        unordered_map<int, unordered_set<int>> edges;
        unordered_set<int> vertices;

        void addEdge(int u, int v) {
            edges[u].insert(v);
            edges[v].insert(u);

            vertices.insert(u);
            vertices.insert(v);
        }
    };

public:
    static void test() {
        ConnectedComponentsInUndirectedGraph obj;

        Graph graph;
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(3, 4);

        obj.printConnectedComponents(graph);

        auto cnt = obj.getConnectedComponents(graph);

        cout << format("Connected components in graph {}", cnt) << endl;
    }

    int getConnectedComponents(Graph& g) {
        int V = g.vertices.size();
        unordered_set<int> visited;
        int components = 0;

        for (auto u : g.vertices) {
            if (visited.count(u) == 0) {
                vector<int> connectedComponenets;
                dfs(g, u, visited, connectedComponenets);
                components++;
            }
        }

        return components;
    }

    void printConnectedComponents(Graph& g) {
        int V = g.vertices.size();
        unordered_set<int> visited;

        for (auto u : g.vertices) {
            if (visited.count(u) == 0) {
                vector<int> connectedComponenets;
                dfs(g, u, visited, connectedComponenets);
                cout << to_string(connectedComponenets) << endl;
            }
        }
    }

    void dfs(Graph& g, int u, unordered_set<int>& visited, vector<int>& connectedComponenets) {
        connectedComponenets.push_back(u);
        visited.insert(u);

        for (auto v : g.edges[u]) {
            if (visited.count(v) == 0) {
                dfs(g, v, visited, connectedComponenets);
            }
        }
    }
};
