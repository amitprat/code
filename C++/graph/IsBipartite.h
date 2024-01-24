#pragma once
#include "../header.h"

namespace Test {
    class Graph {
    private:
        unordered_map<int, vector<int>> nodes;

    public:
        void add(int vertexId) {
            nodes.insert({ vertexId, {} });
        }

        void addEdge(int src, int dst) {
            nodes[src].push_back(dst);
        }

        vector<int> adjList(int u) {
            return nodes[u];
        }

        string to_string() {
            stringstream ss;
            ss << "[";
            for (auto entry : nodes) {
                ss << "{";
                ss << entry.first << ":";
                for (auto j : entry.second) {
                    ss << j << " ";
                }
                ss << "}";
            }
            ss << "]";

            return ss.str();
        }

        int size() {
            return nodes.size();
        }
    };

    class IsBipartite {
    public:
        static void test() {
            IsBipartite obj;
            Graph graph;
            graph.add(0);
            graph.add(1);
            graph.add(2);
            graph.add(3);

            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            graph.addEdge(0, 3);
            graph.addEdge(1, 0);
            graph.addEdge(1, 3);
            graph.addEdge(2, 0);
            graph.addEdge(2, 3);
            graph.addEdge(3, 1);
            graph.addEdge(3, 2);
            graph.addEdge(3, 0);

            cout << graph.to_string() << endl;

            vector<int> colorSet(graph.size(), -1);
            bool res = obj.isBipartite(graph, 0, colorSet, 0);
            cout << "Is Bipartite = " << res << endl;
        }

        bool isBipartite(Graph g, int u, vector<int>& colorSet, int color) {
            if (colorSet[u] != -1 && colorSet[u] != color) {
                return false;
            }
            colorSet[u] = color;

            bool res = true;
            for (auto v : g.adjList(u)) {
                if (colorSet[v] == -1) {
                    res &= isBipartite(g, v, colorSet, 1 - color);
                }

                if (colorSet[v] == color)  res = false;
                if (!res) return res;
            }
            return true;
        }
    };
}