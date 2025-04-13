#include "../header.h"

class AllPathsFromSourceToDestination {
    class Graph {
       public:
        int V;
        unordered_set<int> vertices;
        unordered_map<int, vector<int>> adjMap;

        explicit Graph(int v) : V(v) {}

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

        cout << "DFS-based paths from " << s << " to " << d << ":\n";
        obj.printAllPathsDFS(g, s, d);

        cout << "BFS-based paths from " << s << " to " << d << ":\n";
        obj.printAllPathsBFS(g, s, d);
    }

   private:
    void printAllPathsDFS(const Graph& g, int s, int d) {
        vector<vector<int>> paths;
        vector<bool> visited(g.V, false);

        vector<int> path;
        dfs(g, s, d, visited, path, paths);

        for (const auto& p : paths) {
            for (int node : p) cout << node << " ";
            cout << endl;
        }
    }

   public:
    void dfs(const Graph& g, int s, int d, vector<bool>& visited,
             vector<int>& path, vector<vector<int>>& paths) {
        visited[s] = true;
        path.push_back(s);

        if (s == d) {
            paths.push_back(path);
        } else {
            for (int neighbor : g.adjMap.at(s)) {
                if (!visited[neighbor]) {
                    dfs(g, neighbor, d, visited, path, paths);
                }
            }
        }

        path.pop_back();
        visited[s] = false;
    }

   public:
    void printAllPathsBFS(const Graph& g, int s, int d) {
        vector<vector<int>> result;

        queue<vector<int>> q;
        vector<bool> visisted(g.V, false);

        q.push({s});
        visisted[s] = true;

        while (!q.empty()) {
            auto path = q.front();
            q.pop();
            int u = path.back();

            if (u == d) {
                result.push_back(path);
                continue;
            }

            for (const auto& v : g.adjMap[u]) {
                if (find(path.begin(), path.end(), v) == path.end()) {
                    vector<int> new_path = path;
                    new_path.push_back(v);
                    q.push(move(new_path));
                }
            }
        }

        for (const auto& p : result) {
            for (int node : p) cout << node << " ";
            cout << endl;
        }
    }
};
