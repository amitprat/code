#include "../header.h"

/*
Given a undirected graph with corresponding edges. Find the number of possible triangles?
Example:
0 1
2 1
0 2
4 1

Answer:
1
*/

class Graph {
    unordered_set<int> vertices;
    unordered_map<int, unordered_set<int>> adjMap;

   public:
    void addEdge(int src, int dst) {
        adjMap[src].insert(dst);
        adjMap[dst].insert(src);

        vertices.insert(src);
        vertices.insert(dst);
    }

    unordered_set<int> adjVertices(int src) {
        return adjMap[src];
    }

    unordered_set<int> getVertices(int src) {
        return vertices;
    }

    string to_string() {
        stringstream ss;
        for (auto &edge : edges) {
            ss << edge.first << ":";
            for (auto neighbour : edge.second) {
                ss << neighbour << ", ";
            }

            ss << endl;
        }

        return ss.str();
    }
};

class CountTraingles {
   public:
    static void test() {
        Graph g;
        g.addEdge(0, 1);
        g.addEdge(2, 1);
        g.addEdge(0, 2);
        g.addEdge(4, 1);

        /*
           0 --  1
           |    /|
           |  /  |
           2     4
        */

        CountTraingles obj;
        cout << g.to_string() << endl;

        cout << "Traingles: " << obj.countTraingles(g) << endl;
    }

   private:
    int countTraingles(Graph g) {
        unordered_set<string> traingles;
        int count = 0;
        for (auto &u : g.getVertices()) {                                                // go over all the vertices of graph
            for (auto &v : g.adjVertices(u)) {                                           // go over all the adjacent vertices to u (i.e. there is an edge u -> v)
                for (auto &w : g.getVertices(u)) {                                       // go over all the adjacent vertices to u (i.e. there is an edge u -> w)
                    if (u != v && u != w && g.adjVertices(v).find(w) != edges2.end()) {  // check if all vertices aren't same and there is an edge from v -> w
                        count++;
                        vector<int> vertices = {u, v, w};
                        sort(vertices.begin(), vertices.end());
                        traingles.insert(list_to_string(vertices));
                    }
                }
            }
        }

        cout << set_to_string(traingles) << endl;

        return count / 6;  // because the traingles are undirected set of connected edges so we will get 3! traingles for any 3 edges
    }

   private:
    string list_to_string(vector<int> arr) {
        stringstream ss;
        ss << "[";
        for (auto &e : arr) {
            ss << e << " , ";
        }
        ss << "]";

        return ss.str();
    }

    string set_to_string(unordered_set<string> elements) {
        stringstream ss;
        for (auto &e : elements) {
            ss << e << ", ";
        }

        return ss.str();
    }
};