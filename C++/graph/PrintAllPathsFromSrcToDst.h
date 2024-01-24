#pragma once
#include "../header.h"
#include "../design/Set.h"

class FindPaths {
private:
    template <class T>
    class Edge {
    public:
        T src, dst;
        int wt;
        Edge(T src, T dst, int wt) :src(src), dst(dst), wt(wt) {}
        string to_string() {
            stringstream ss;
            ss << "{";
            ss << setw(2) << src;
            ss << "->";
            ss << setw(2) << dst;
            ss << ":";
            ss << setw(2) << wt;
            ss << "}";
            return ss.str();
        }
    };

    template <class T>
    class Graph {
    public:
        int V;
        unordered_map<int, vector<Edge<T>*>> edges;

        Graph(int v) :V(v) {}
        void addEdge(T src, T dst, int wt) {
            edges[src].push_back(new Edge(src, dst, wt));
        }
        string to_string() {
            stringstream ss;
            ss << "{\n";
            for (auto edge : edges) ss << "  " << edge.second->to_string() << "\n";
            ss << "}\n";
            return ss.str();
        }
    };
public:
    static void test() {
        Graph<int> g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(0, 3, 1);
        g.addEdge(2, 0, 1);
        g.addEdge(2, 1, 1);
        g.addEdge(1, 3, 1);

        int s = 2, d = 3;
        FindPaths obj;
        vector<string> res = obj.getPaths(g, s, d);

        cout << "All Paths:" << endl;
        for (auto i : res) {
            cout << i << endl;
        }
    }

    vector<string> getPaths(Graph<int> g, int s, int d) {
        vector<string> path;
        Set<int> visited;

        getPaths(g, s, d, path, visited, std::to_string(s));

        return path;
    }

private:
    void getPaths(Graph<int> g, int s, int d, vector<string>& paths, Set<int>& visited, string cur = "") {
        if (s == d) {
            paths.push_back(cur);
        }
        visited.add(s);
        for (auto v : g.edges[s]) {
            if (!visited.exists(v->dst)) {
                getPaths(g, v->dst, d, paths, visited, cur + "->" + std::to_string(v->dst));
            }
        }
        visited.remove(s);
    }
};