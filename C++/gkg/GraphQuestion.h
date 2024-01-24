#pragma once
#include "../Header.h"

class GraphQuestion {
    class Graph {
        unordered_map<string, unordered_set<string>> edges;
        unordered_set<string> vertices;
        bool isUndirectedGraph = false;
    public:
        Graph() {}
        Graph(bool isUndirectedGraph) :isUndirectedGraph(isUndirectedGraph) {}

        void add(string src, string dst) {
            vertices.insert(src);
            vertices.insert(dst);

            edges[src].insert(dst);
            if (isUndirectedGraph) {
                edges[dst].insert(src);
            }
        }

        void bfs() {
            unordered_set<string> visited;
            for (auto v : vertices) {
                if (visited.find(v) == visited.end()) {
                    bfs(v, visited);
                }
            }
            cout << endl;
        }

        void bfs(string u, unordered_set<string>& visited) {
            queue<string> q;
            q.push(u);
            visited.insert(u);

            while (!q.empty()) {
                auto f = q.front(); q.pop();
                cout << f << " ";

                for (auto v : edges[f]) {
                    if (visited.find(v) == visited.end()) {
                        q.push(v);
                        visited.insert(v);
                    }
                }
            }
        }

        void dfs() {
            unordered_set<string> visited;
            for (auto v : vertices) {
                if (visited.find(v) == visited.end()) {
                    dfs(v, visited);
                }
            }
            cout << endl;
        }

        void dfs(string u, unordered_set<string>& visited) {
            visited.insert(u);
            cout << u << " ";
            for (auto v : edges[u]) {
                if (visited.find(v) == visited.end()) {
                    dfs(v, visited);
                }
            }
        }

        bool isSC() {
            unordered_set<string> visited;
            dfs(*vertices.begin(), visited);

            for (auto v : vertices) {
                if (visited.find(v) == visited.end()) return false;
            }

            Graph gr = transpose(g);

            visited.clear();

            dfs(*vertices.begin(), visited);

            for (auto v : vertices) {
                if (visited.find(v) == visited.end()) return false;
            }

            return true;
        }

        Graph transpose(Graph g) {
            Graph gr;
            for (auto e : g.edges) {
                for (auto v : e.second) {
                    gr.add(v, e.first);
                }
            }

            return gr;
        }
    };
public:
    static void test() {
        {
            Graph g;
            g.add("0", "1");
            g.add("1", "2");
            g.add("2", "4");
            g.add("4", "2");
            g.add("3", "0");
            g.add("2", "3");
            
            cout << "BFS: ";
            g.bfs();
            cout << endl;

            cout << "DFS: ";
            g.dfs();
            cout << endl;

            cout << "Is strongly connected? " << g.isSC() << endl;

            cout << "Topology order: ";
            g.topology();
            cout << endl;
        }
        cycleInDirectedGraph();
        cycleInUndirectedGraph();
        checkIfGraphIsBipartite();
        snakeLadderGame();
        prims();
        krushkals();
        dijkastra();
        bellmanford();
        floydWarshall();
        eulerianPath();
        stronglyConnectedComponents();
        eulerianCiruit();
        biconnectedComponents();
        graphColoring();
        hamCycle();
        
        {
            vector<vector<int>> matrix = { 
                     { 1, 1, 0, 0, 0 },
                     { 0, 1, 0, 0, 1 },
                     { 1, 0, 0, 1, 1 },
                     { 0, 0, 0, 0, 0 },
                     { 1, 0, 1, 0, 1 } };

            cout << "Number of islands is: " << countIslands(matrix) <<endl;
        }
    }

    static int countIslands(vector<vector<int>>& matrix) {
        unordered_set<int> visited;
        int count = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (visited.find(i * matrix[i].size() + j) == visited.end()) {
                    count +=dfs(matrix, i, j, matrix.size(), matrix[i].size(), visited);
                }
            }
        }
        return count;
    }

    static int dfs(vector<vector<int>>& matrix, int x, int y, int n, int m, unordered_set<int>& visited) {
        visited.insert(x * m + y);

        int cnt = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int x1 = x + i;
                int y1 = y + j;
                if (x1 < 0 || y1 < 0 || x1 >= n || y1 >= m) continue;

                if (visited.find(x1 * m + y) == visited.end()) {
                    cnt += dfs(matrix, x1, y1, n, m, visited);
                }
            }
        }

        return cnt;
    }
};