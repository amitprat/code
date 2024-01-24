#pragma once
#include "../Header.h"

class ChainStrings {
    const int CHAR_SET = 256;
    template <class T>
    class Graph {
    public:
        int v;
        unordered_map<T, int> in;
        unordered_map<T, vector<T>> edges;
        Graph(int v) : v(v) {}
        void addEdge(T src, T dst) {
            edges[src].push_back(dst);
            in[dst]++;
        }
        vector<T> adjList(T src) {
            return edges[src];
        }
        int inList(T src) {
            return in[src];
        }
        int size() {
            return v;
        }
        string to_string() {
            stringstream ss;
            ss << "{" << endl;
            for (auto u : edges) {
                ss << setw(4) << u.first << ":";
                for (auto v : u.second) {
                    ss << v << " ";
                }
                ss << endl;
            }
            ss << "}";

            return ss.str();
        }
    };
public:
    static void test() {
        ChainStrings obj;

        vector<string> arr1 = { "for", "geek", "rig", "kaf" };
        cout << "Checking if input " << to_string(arr1) << " can be chained" << endl;
        auto res = obj.canBeChained(arr1);
        if (res) cout << "Can be chained \n";
        else cout << "Can't be chained \n";
        cout << endl << endl;

        vector<string> arr2 = { "aab", "abb" };
        cout << "Checking if input " << to_string(arr2) << " can be chained" << endl;
        res = obj.canBeChained(arr2);
        if (res) cout << "Can be chained \n";
        else cout << "Can't be chained \n";
        cout << endl << endl;
    }

    bool canBeChained(vector<string> input) {
        Graph<char> g(CHAR_SET);
        for (auto s : input) {
            g.addEdge(s.front(), s.back());
        }
        cout << "Graph:" << endl;
        cout << g.to_string() << endl;

        return isEulerianCycle(g);
    }

    bool isEulerianCycle(Graph<char> g) {
        cout << "Checking if strongly connected" << endl;
        if (!stronglyConnected(g)) return false;

        cout << "Checking if we have odd degree vertex" << endl;
        for (int i = 0; i < g.size(); i++) {
            if (g.adjList(i).size() != g.inList(i)) {
                cout << "Found odd degree vertex = " << i << endl;
                return false;
            }
        }

        cout << "Graph forms eulerian circuit" << endl;
        return true;
    }
    bool stronglyConnected(Graph<char> g) {
        unordered_set<int> visited;

        // find first un-isolated vertex
        int i = 0;
        for (; i < g.size(); i++) {
            if (g.adjList(i).size() != 0) break;
        }

        // do the dfs from above found vertex which marks all reachable vertices
        cout << "Do dfs from vertex = " << i << endl;
        dfs(g, i, visited);

        // if we find any un-isolated vertex which isn't visited yet, then its not strongly connected
        for (int j = 0; j < g.size(); j++) {
            if (g.adjList(j).size() > 0 && visited.find(j) == visited.end()) {
                cout << "Found un-isolated vertex = " << j << ", which wan't visited" << endl;
                return false;
            }
        }

        // calculate transpose
        Graph<char> gr = transpose(g);
        visited.clear();

        cout << "Transpose Graph:" << endl;
        cout << gr.to_string() << endl;

        // do the dfs from above found vertex which marks all reachable vertices
        cout << "Do dfs on transponse graph from vertex = " << i << endl;
        dfs(gr, i, visited);

        // if we find any un-isolated vertex which isn't visited yet, then its not strongly connected
        for (int j = 0; j < g.size(); j++) {
            if (g.adjList(j).size() > 0 && visited.find(j) == visited.end()) {
                cout << "Found un-isolated vertex = " << j << ", which wan't visited" << endl;
                return false;
            }
        }

        cout << "Graph is strongly connected." << endl;
        return true;
    }

private:
    void dfs(Graph<char> g, int u, unordered_set<int>& visited) {
        visited.insert(u);
        for (auto v : g.adjList(u)) {
            if (visited.find(v) == visited.end()) {
                dfs(g, v, visited);
            }
        }
    }

    Graph<char> transpose(Graph<char> g) {
        Graph<char> gr(CHAR_SET);
        for (auto i : g.edges) {
            for (auto j : i.second) {
                gr.addEdge(j, i.first);
            }
        }
        return gr;
    }
};