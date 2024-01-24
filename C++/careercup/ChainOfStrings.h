#pragma once
#include "../Header.h"

class ChainOfStrings {
    class Graph {
    public:
        unordered_map<char, vector<char>> edges;
        unordered_set<char> vertices;
        unordered_map<char, int> inDegree;

        void addEdge(char u, char v) {
            edges[u].push_back(v);
            vertices.insert(u);
            vertices.insert(v);
            inDegree[v]++;
        }
    };

public:
    static void test() {
        {
            vector<string> strs = { "for", "geek", "rig", "kaf" };

            bool res = canBeChained(strs);

            cout << "Can be chained? " << res << endl;
        }

        {
            vector<string> strs = { "abc", "bcd", "cdf" };

            bool res = canBeChained(strs);

            cout << "Can be chained? " << res << endl;
        }
    }

    static bool canBeChained(vector<string>& strs) {
        Graph g;
        for (auto& str : strs) {
            int n = str.length();
            g.addEdge(str[0], str[n - 1]);
        }

        return isEulerianCycle(g);
    }

    static bool isEulerianCycle(Graph g) {
        if (!isStronglyConnected(g)) return false;

        // if in-degree and out-degree must be same
        for (auto u : g.vertices) {
            if (g.edges[u].size() != g.inDegree[u]) return false;
        }

        return true;
    }

    static bool isStronglyConnected(Graph g) {
        unordered_set<char> visited;

        dfs(g, *g.vertices.begin(), visited);
        if (visited.size() != g.vertices.size()) return false;

        visited.clear();

        Graph gr = getTransposeGraph(g);
        dfs(g, *gr.vertices.begin(), visited);
        if (visited.size() != gr.vertices.size()) return false;

        return true;
    }

    static void dfs(Graph g, char u, unordered_set<char>& visited) {
        visited.insert(u);

        for (auto v : g.edges[u]) {
            if (visited.count(v) == 0) {
                dfs(g, v, visited);
            }
        }
    }

    static Graph getTransposeGraph(Graph g) {
        Graph gr;
        for (auto u : g.edges) {
            for (auto v : u.second) {
                gr.addEdge(v, u.first);
            }
        }

        return gr;
    }
};