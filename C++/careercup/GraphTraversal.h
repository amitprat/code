#include "../header.h"

class GraphTraversal {
   public:
    static void test() {
        GraphTraversal obj;

        cout << "BFS using adjacency matrix: ";
        obj.bfsMatrixTest();
        cout << endl;

        cout << "BFS using adjacency graph: ";
        obj.bfsAdjListTest();
        cout << endl;

        cout << "BFS 0-1: ";
        obj.bfsZeroOneTest();
        cout << endl;

        cout << "BFS Matrix test: ";
        obj.bfsMatrixTest2();
        cout << endl;

        cout << "DFS using adjacency graph: ";
        obj.dfsTest();
        cout << endl;

        cout << "DFS using matrix: ";
        obj.dfsMatrixTest();
        cout << endl;

        obj.dfsIsReachableTest();

        obj.testIsDirectedGraphStronglyConnected();

        obj.testConnectedComponentsInUndirectedGraph();

        obj.testDirectedGraphStronglyConnectedComponents();
    }

   private:
    void bfsMatrixTest() {
        vector<vector<int>> matrix = {
            {0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0}};

        GraphTraversal obj;
        int src = 0;
        obj.bfsMatrix(matrix, src);
    }

    void bfsMatrix(vector<vector<int>> &matrix, int src) {
        unordered_set<int> visited;
        queue<int> q;

        q.push(src);
        visited.insert(src);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            cout << u << " ";

            for (auto v = 0; v < matrix[u].size(); v++) {
                if (matrix[u][v] && (visited.find(v) == visited.end())) {
                    q.push(v);
                    visited.insert(v);
                }
            }
        }
    }

   private:
    struct Graph {
        unordered_set<int> vertices;
        unordered_map<int, unordered_set<int>> edges;

        void addEdge(int src, int dst) {
            vertices.insert(src);
            vertices.insert(dst);

            edges[src].insert(dst);
            edges[dst].insert(src);
        }
    };

    void bfsAdjListTest() {
        Graph g;
        // g.addEdge(1, 2);
        // g.addEdge(1, 3);
        // g.addEdge(1, 4);
        // g.addEdge(2, 5);
        // g.addEdge(2, 6);
        // g.addEdge(5, 9);
        // g.addEdge(5, 10);
        // g.addEdge(4, 7);
        // g.addEdge(4, 8);
        // g.addEdge(7, 11);
        // g.addEdge(7, 12);
        g.addEdge(0, 4);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 3);
        g.addEdge(3, 4);

        unordered_set<int> visited;
        for (int i = 0; i < 5; i++) {
            if (visited.find(i) == visited.end()) {
                this->bfsAdjList(g, visited, i);
            }
        }
    }

    void bfsAdjList(Graph g, unordered_set<int> &visited, int src) {
        queue<pair<int, int>> q;

        q.push({src, 0});
        visited.insert(src);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            cout << "{" << u.first << "," << u.second << "}, ";

            for (auto v : g.edges[u.first]) {
                if (visited.find(v) == visited.end()) {
                    q.push({v, u.second + 1});
                    visited.insert(v);
                }
            }
        }

        cout << endl;
    }

   private:
    /*
    We can't use BFS for weighted graph but here we can use it for 0-1 graph where the vertices are either 0 weight or 1 weight.
    The way to acheive it is to use deque and insert vertices in queue as per following logic:
        If weight == 0 : insert in beginning of queue
        else           : insert to end

    This way, the deque always maintains weighted order of vertices on each level so the vertex with 0 weights are explored first.
    It is not exactly doing bfs as vertices with 0 weights will be inserted in beginning so kind of depth order for 0 weighted vertices.

    we don't need to use visited set to keep track of visited vertices as we only explore vertices if there is a way to relax the weight of next
    vertices using current edge. It has same limitation as Dijkastra (negative cycle), then it can go in infite loop.

    Algorithm:
        dq.push(start)

        while dq not empty:
            auto u = pop front

            for all v in adj of u:
                if dist[u] + v.dst < dist[v]://if can relax the edge
                    dist[v] = dist[u] + v.dst

                    if v.dst == 0:
                        dq.push_front(v);
                    else
                        dq.push_back(v)
    */
    struct WeightedGraph {
        unordered_set<int> vertices;
        unordered_map<int, list<pair<int, int>>> edges;

        void addEdge(int src, int dst, int wt) {
            vertices.insert(src);
            vertices.insert(dst);

            edges[src].push_back({dst, wt});
        }
    };

    void bfsZeroOneTest() {
        WeightedGraph g;
        g.addEdge(0, 1, 0);
        g.addEdge(0, 7, 1);
        g.addEdge(1, 7, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 0);
        g.addEdge(2, 5, 0);
        g.addEdge(2, 8, 1);
        g.addEdge(3, 4, 1);
        g.addEdge(3, 5, 1);
        g.addEdge(4, 5, 1);
        g.addEdge(5, 6, 1);
        g.addEdge(6, 7, 1);
        g.addEdge(7, 8, 1);

        int src = 0;
        bfsZeroOne(g, src);
    }

    void bfsZeroOne(WeightedGraph g, int src) {
        int V = g.vertices.size();
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        deque<int> dq;
        dq.push_back(src);

        while (!dq.empty()) {
            auto u = dq.front();
            dq.pop_front();

            for (auto v : g.edges[u]) {
                if (dist[u] + v.second < dist[v.first]) {
                    dist[v.first] = dist[u] + v.second;
                    if (v.second == 0)
                        dq.push_front(v.first);
                    else
                        dq.push_back(v.first);
                }
            }
        }

        cout << "dist: " << dist << endl;
    }

   private:
    /*
    For this, we start from a source vertex and do level order traversal in matrix (by visited all 4 neighbours if not visited).
    */
    void bfsMatrixTest2() {
        vector<vector<int>> matrix = {{1, 2, 3, 4},
                                      {5, 6, 7, 8},
                                      {9, 10, 11, 12},
                                      {13, 14, 15, 16}};

        bfsMatrix(matrix, {0, 0});
    }

    void bfsMatrix(vector<vector<int>> &matrix, pair<int, int> start) {
        unordered_set<int> visited;
        int n = matrix.size();
        int m = 0;
        if (n > 0)
            m = matrix[0].size();

        queue<pair<int, int>> q;
        q.push(start);
        visited.insert(start.first * m + start.second);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            cout << matrix[u.first][u.second] << " ";

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j)) {
                        pair<int, int> v = {u.first + i, u.second + j};
                        if (v.first >= 0 && v.second >= 0 && v.first < n && v.second < m &&
                            visited.find(v.first * m + v.second) == visited.end()) {
                            visited.insert(v.first * m + v.second);
                            q.push(v);
                        }
                    }
                }
            }
        }
        cout << endl;
    }

   private:
    /*
    Give a adj list graph, we can do dfs by looking at next set of vertex at each level and depth order traversal.
    Using the recursion, it uses system stack to do top-down recursion (if vertex isn't already visited).
    we can implement same using explicit stack as well. Only thing is that, we can't exactly mimic the top-down recursion using stack
    so we need to check if vertex is visited on not at the top in traversal and if already visited, skip it.
    */
    void dfsTest() {
        Graph g;
        g.addEdge(0, 1);
        g.addEdge(0, 4);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 3);
        g.addEdge(3, 4);

        dfs(g, 0);
    }

    void dfs(Graph g, int src) {
        unordered_set<int> visited;
        dfs(g, 0, 0, visited);
    }

    void dfs(Graph g, int src, int dst, unordered_set<int> &visited) {
        if (visited.find(src) != visited.end())
            return;

        cout << "{" << src << "," << dst << "}, ";
        visited.insert(src);

        for (auto v : g.edges[src]) {
            if (visited.find(v) == visited.end()) {
                dfs(g, v, dst + 1, visited);
            }
        }
    }

   private:
    /*
    Given a matrix, do dfs from a start vertex. we can only move up-down, left-right. We explore all 4 members on next level and depth order traversal.
    */
    void dfsMatrixTest() {
        vector<vector<int>> matrix = {
            {-1, 2, 3},
            {0, 9, 8},
            {1, 0, 1}};

        dfsMatrix(matrix, {0, 0});
    }

    void dfsMatrix(vector<vector<int>> &matrix, pair<int, int> start) {
        unordered_set<int> visited;
        int n = matrix.size();
        int m = 0;
        if (n > 0)
            m = matrix[0].size();

        stack<pair<int, int>> st;
        st.push(start);

        while (!st.empty()) {
            auto u = st.top();
            st.pop();

            if (visited.find(u.first * m + u.second) != visited.end())
                continue;

            cout << matrix[u.first][u.second] << " ";
            visited.insert(u.first * m + u.second);

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j)) {
                        pair<int, int> v = {u.first + i, u.second + j};
                        if (v.first >= 0 && v.second >= 0 && v.first < n && v.second < m &&
                            (visited.find(v.first * m + v.second) == visited.end())) {
                            st.push(v);
                        }
                    }
                }
            }
        }
    }

   private:
    /*
    We can use bfs or dfs for reachablility check. By reachability it means that given 2 vertices, find out that dst vertex is reachable
    from source vertex (may be with some distance limit).
    BFS: always gives the shorted distance between src and dst as it expands by exploring each level so if we have reached destination in a level
    that means, it the shortest path. BFS only works for non-weighted graph (uniform weight to each vertex). For weighted graph, we use the modified
    version (dijkastra, bfs with priority queue). BFS uses simple queue to explore vertices in the order. Time Complexity: O(V+E).
    Its useful for the cases, then graph breadth is not a lot and we are interested to find the shortest path.
    DFS: dfs checks for the connectivity or any path between 2 vertices of a graph. It starts exploring the vertices in depth order (using stack)
    until reaches the end of graph and traces back and starts from next. Time Complexity: O(V+E)
    It is not useful incase if the depth of graph is a lot.

    It depends if there's any apparent heuristic function that you could use or if you don't have any further usable information about your graph.
    Your options are:
        BFS: in general case or if you don't care about computation time that much.
        Dijkstra (Dijkstra "is" BFS with priority queue): if your edges have weights/prices (non negative) and you care about CPU time.
        A* (A* "is" Dijkstra with heuristic function - e.g. distance on a city map): if you want it to be really fast in average case, but you have to provide good heuristic function.
    */
    void dfsIsReachableTest() {
        Graph g;
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 5);
        g.addEdge(2, 6);

        int dst = 6, maxDepth = 3, src = 0;
        unordered_set<int> visited;
        auto result = isReachable(g, src, dst, maxDepth, visited);
        if (result.first) {
            cout << "Distance from " << src << " to " << dst << " is " << maxDepth - result.second << endl;
        }
    }

    pair<bool, int> isReachable(Graph g, int src, int dst, int depth, unordered_set<int> &visited) {
        if (depth <= 0)
            return {false, -1};
        if (src == dst)
            return {true, depth};

        visited.insert(src);
        for (auto v : g.edges[src]) {
            if (visited.find(v) == visited.end()) {
                auto result = isReachable(g, v, dst, depth - 1, visited);
                if (result.first)
                    return result;
            }
        }

        return {false, -1};
    }

   private:
    /*
    A directed graph is strongly connected if the number of strongly connected components is 1.
    To check that, we first do dfs from any vertex and see that all the vertices can be visited.
    Then, reverse the graph (transponse) and do dfs again from any vertex and it should be still reachable to
    all the vertices.
    */
    struct DirectedGraph {
        unordered_map<int, unordered_set<int>> adjMap;
        unordered_set<int> vertices;

        void addEdge(int src, int dst) {
            vertices.insert(src);
            vertices.insert(dst);

            adjMap[src].insert(dst);
        }
    };
    void testIsDirectedGraphStronglyConnected() {
        DirectedGraph g;
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge(3, 0);
        g.addEdge(2, 4);
        g.addEdge(4, 2);

        bool result = isStronglyConnected(g);
        if (result) {
            cout << "Graph is strongly connected" << endl;
        }

        DirectedGraph g2;
        g2.addEdge(0, 1);
        g2.addEdge(1, 2);
        g2.addEdge(2, 3);
        bool result2 = isStronglyConnected(g2);
        if (result2) {
            cout << "Graph is strongly connected" << endl;
        }
    }

    bool isStronglyConnected(DirectedGraph g) {
        vector<bool> visited(g.vertices.size(), false);
        dfs(g, 0, visited);

        for (int i = 0; i < g.vertices.size(); i++) {
            if (!visited[i])
                return false;
        }

        DirectedGraph gr = getTransponse(g);
        for (int i = 0; i < g.vertices.size(); i++) {
            visited[i] = false;
        }

        dfs(gr, 0, visited);
        for (int i = 0; i < g.vertices.size(); i++) {
            if (!visited[i])
                return false;
        }

        return true;
    }

    void dfs(DirectedGraph g, int u, vector<bool> &visited) {
        visited[u] = true;

        for (auto v : g.adjMap[u]) {
            if (!visited[v]) {
                dfs(g, v, visited);
            }
        }
    }

    DirectedGraph getTransponse(DirectedGraph g) {
        DirectedGraph gr;
        for (auto edges : g.adjMap) {
            for (auto v : edges.second) {
                gr.addEdge(v, edges.first);
            }
        }

        return gr;
    }

   private:
    // print strongly connected components in a directed graph
    /*
    For directed graph, just checking connecting between vertices isn't good enough to check for strong connectivity
    as the same vertex might not be reachable from a different (as edges are unidirectional).
    So, for directed graph, we need to first find the topological order of vertices (in which they are visited, dependency order).
    Then, from that topo order, we can do dfs on transponse of graph. This will give the minimum strongly connected component set.
    */
    void testDirectedGraphStronglyConnectedComponents() {
        DirectedGraph g;
        g.addEdge(1, 0);
        g.addEdge(0, 2);
        g.addEdge(2, 1);
        g.addEdge(0, 3);
        g.addEdge(3, 4);

        cout << "Strongly connected components in a directed graph: ";
        printStrongConnectedComponents(g);
        cout << endl;
    }

    void printStrongConnectedComponents(DirectedGraph g) {
        vector<bool> visited(g.vertices.size(), false);
        stack<int> dependencyOrder;
        for (auto u : g.vertices) {
            if (!visited[u]) {
                dfs(g, u, dependencyOrder, visited);
            }
        }

        DirectedGraph gr = getTransponse(g);
        for (int i = 0; i < g.vertices.size(); i++) {
            visited[i] = false;
        }

        while (!dependencyOrder.empty()) {
            auto u = dependencyOrder.top();
            dependencyOrder.pop();
            if (!visited[u]) {
                printComponents(gr, u, visited);
                cout << endl;
            }
        }
    }

    void dfs(DirectedGraph g, int u, stack<int> &dependencyOrder, vector<bool> &visited) {
        visited[u] = true;

        for (auto v : g.adjMap[u]) {
            if (!visited[v]) {
                dfs(g, v, dependencyOrder, visited);
            }
        }

        dependencyOrder.push(u);
    }

    void printComponents(DirectedGraph g, int u, vector<bool> &visited) {
        cout << u << " ";
        visited[u] = true;

        for (auto v : g.adjMap[u]) {
            if (!visited[v]) {
                printComponents(g, v, visited);
            }
        }
    }

   private:
    /*
    For connected components in a undirected graph, just do dfs from every unvisited vertex and print the graph component
    that can be visited from a start vertex.
    */
    struct UndirectedGraph {
        unordered_map<int, unordered_set<int>> adjMap;
        unordered_set<int> vertices;

        void addEdge(int src, int dst) {
            vertices.insert(src);
            vertices.insert(dst);

            adjMap[src].insert(dst);
            adjMap[dst].insert(src);
        }
    };

    void testConnectedComponentsInUndirectedGraph() {
        UndirectedGraph g;
        g.addEdge(1, 0);
        g.addEdge(2, 1);
        g.addEdge(3, 4);

        cout << "Following are connected components \n";
        connectedComponents(g);
    }

    void connectedComponents(UndirectedGraph g) {
        unordered_set<int> visited;
        for (auto u : g.vertices) {
            if (visited.find(u) == visited.end()) {
                dfs(g, u, visited);
                cout << endl;
            }
        }
    }

    void dfs(UndirectedGraph g, int u, unordered_set<int> &visited) {
        cout << u << " ";
        visited.insert(u);

        for (auto v : g.adjMap[u]) {
            if (visited.find(v) == visited.end()) {
                dfs(g, v, visited);
            }
        }
    }
};