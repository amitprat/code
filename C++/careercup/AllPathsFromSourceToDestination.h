#include "../header.h"

class AllPathsFromSourceToDestination {
    class Graph {
       public:
        int V;
        Graph(int v) : V(v) {}

        unordered_set<int> vertices;
        unordered_map<int, vector<int>> adjMap;

        void addEdge(int u, int v) {
            vertices.insert(u);
            vertices.insert(v);

            adjMap[u].push_back(v);
        }
    };

   public:
    static void test() {
        Graph g(4);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 3);
        g.addEdge(2, 0);
        g.addEdge(2, 1);
        g.addEdge(1, 3);

        AllPathsFromSourceToDestination obj;
        int s = 2, d = 3;
        cout << "Following are all different paths from " << s
             << " to " << d << endl;
        obj.printAllPaths(g, s, d);
    }

   private:
    void printAllPaths(Graph g, int s, int d) {
        vector<vector<int>> paths;
        vector<bool> visited(g.V, false);

        this->printAllPaths(g, s, d, visited, {}, paths);

        cout << "All paths: " << endl;
        for (auto &path : paths) {
            cout << "Path: " << path << endl;
        }
        cout << endl;
    }

    void printAllPaths(Graph g, int s, int d, vector<bool> &visited, vector<int> path, vector<vector<int>> &paths) {
        path.push_back(s);
        visited[s] = true;

        if (s == d) {
            paths.push_back(path);
        } else {
            for (auto &v : g.adjMap[s]) {
                if (!visited[v]) {
                    this->printAllPaths(g, v, d, visited, path, paths);
                }
            }
        }

        path.pop_back();
        visited[s] = false;
    }
};