#include "../header.h"

class FindBuildOrderUsingGivenDependency {
    class Graph {
       public:
        int V;
        unordered_set<char> vertices;
        unordered_map<char, vector<char>> adjMap;

        Graph(int v) : V(v) {}
        void addVertex(int v) {
            this->vertices.insert(v);
        }
        void addEdge(int u, int v) {
            this->adjMap[u].push_back(v);
        }
    };

   public:
    static void test() {
        vector<char> projects = {'a', 'b', 'c', 'd', 'e', 'f'};
        vector<pair<char, char>> dependencies = {{'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f', 'a'}, {'d', 'c'}};

        Graph g(projects.size());
        for (auto u : projects) g.addVertex(u);
        for (auto edge : dependencies) {
            g.addEdge(edge.first, edge.second);
        }

        FindBuildOrderUsingGivenDependency obj;
        vector<char> out = obj.buildOrder(g);
        cout << "Order: " << out << endl;
    }

    vector<char> buildOrder(Graph g) {
        stack<char> st;

        unordered_set<char> visited;
        for (auto u : g.vertices) {
            if (visited.find(u) == visited.end()) {
                dfs(g, u, visited, st);
            }
        }

        vector<char> out;
        while (!st.empty()) {
            out.push_back(st.top());
            st.pop();
        }

        return out;
    }

    void dfs(Graph g, char u, unordered_set<char>& visited, stack<char>& st) {
        visited.insert(u);

        for (auto v : g.adjMap[u]) {
            if (visited.find(v) == visited.end()) {
                dfs(g, v, visited, st);
            }
        }

        st.push(u);
    }
};