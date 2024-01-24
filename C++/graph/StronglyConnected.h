#pragma once
#include "../Header.h"

class StronglyConnected {
    template <class T>
    class Graph {
    public:
        unordered_map<T, vector<T>> edges;
        unordered_set<T> vertices;
        void add(T src, T dst) {
            edges[src].push_back(dst);
            vertices.insert(src);
            vertices.insert(dst);
        }
        string to_string() {
            stringstream ss;
            for (auto e : edges) {
                ss << std::to_string(e.first) << ": ";
                for (auto ad : e.second) {
                    ss << std::to_string(ad) << " ";
                }
                ss << endl;
            }
            return ss.str();
        }
    };
public:
    static void test() {
        StronglyConnected obj;
        Graph<int> g;
        g.add(1, 0);
        g.add(0, 2);
        g.add(2, 1);
        g.add(0, 3);
        g.add(3, 4);
        cout << "Graph: " << endl;
        cout << g.to_string() << endl;

        cout << "Following are strongly connected components in the graph:" << endl;
        obj.printSCCs(g);
    }

    void printSCCs(Graph<int> g) {
        unordered_set<int> visited;
        stack<int> st;
        for (auto v : g.vertices) {
            if (visited.find(v) == visited.end()) {
                fillOrder(g, v, visited, st);
            }
        }
        auto gr = transpose(g);

        visited.clear();
        while (!st.empty()) {
            auto v = st.top(); st.pop();
            if (visited.find(v) == visited.end()) {
                vector<int> set;
                dfs(gr, v, visited, set);

                cout << "Connected Component = ";
                for (auto u : set) {
                    cout << std::to_string(u) << " ";
                }
                cout << endl;
            }
        }
    }

private:
    void fillOrder(Graph<int> g, int u, unordered_set<int>& visited, stack<int>& st) {
        visited.insert(u);
        for (auto v : g.edges[u]) {
            if (visited.find(v) == visited.end()) fillOrder(g, v, visited, st);
        }
        st.push(u);
    }
    void dfs(Graph<int> g, int u, unordered_set<int>& visited, vector<int>& set) {
        visited.insert(u);
        set.push_back(u);
        for (auto v : g.edges[u]) {
            if (visited.find(v) == visited.end()) dfs(g, v, visited, set);
        }
    }
    Graph<int> transpose(Graph<int> g) {
        Graph<int> gr;
        for (auto e : g.edges) {
            for (auto ad : e.second) gr.add(ad, e.first);
        }
        return gr;
    }
};