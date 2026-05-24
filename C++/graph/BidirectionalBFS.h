#pragma once
#include "../header.h"
#include "Graph.h"

class BidirectionalBFS {
   public:
    static void test() {
        BidirectionalBFS obj;
        Graph<int> graph;
        graph.add(1);
        graph.add(2);
        graph.add(3);
        graph.add(4);
        graph.add(5);
        graph.add(6);
        graph.addEdge(1, 2);
        graph.addEdge(2, 1);
        graph.addEdge(3, 2);
        graph.addEdge(2, 3);
        graph.addEdge(2, 4);
        graph.addEdge(4, 2);
        graph.addEdge(5, 4);
        graph.addEdge(4, 5);
        graph.addEdge(6, 4);
        graph.addEdge(4, 6);
        cout << graph.str();
        int begin = 1;
        int end = 5;
        cout << obj.find(graph, begin, end) << endl;
    }

   public:
    bool find(Graph<int>& g, int begin, int end) {
        unordered_set<int> visited_left, visited_right;

        queue<int> q_left, q_right;

        unordered_map<int, int> parent_left, parent_right;

        visited_left.insert(begin);
        visited_right.insert(end);

        parent_left[begin] = -1;
        parent_right[end] = -1;

        q_left.push(begin);
        q_right.push(end);

        while (!q_left.empty() && !q_right.empty()) {
            int intersect = bfsLevel(g, q_left, visited_left, parent_left, visited_right);
            if (intersect != -1) {
                printPath(parent_left, parent_right, begin, end, intersect);
                return true;
            }

            intersect = bfsLevel(g, q_right, visited_right, parent_right, visited_left);
            if (intersect != -1) {
                printPath(parent_left, parent_right, begin, end, intersect);
                return true;
            }
        }

        return false;
    }

   private:
    int bfsLevel(
        Graph<int>& g,
        queue<int>& q,
        unordered_set<int>& visited,
        unordered_map<int, int>& parent,
        unordered_set<int>& otherVisited) {
        int size = q.size();

        while (size--) {
            int cur = q.front();
            q.pop();

            for (auto& neigh : g.getNeighbours(cur)) {
                if (!visited.count(neigh)) {
                    parent[neigh] = cur;
                    visited.insert(neigh);
                    q.push(neigh);

                    if (otherVisited.count(neigh))
                        return neigh;
                }
            }
        }

        return -1;
    }

    void printPath(
        unordered_map<int, int>& parent_left,
        unordered_map<int, int>& parent_right,
        int begin,
        int end,
        int intersect) {
        vector<int> path;

        int node = intersect;

        while (node != -1) {
            path.push_back(node);
            node = parent_left[node];
        }

        std::reverse(path.begin(), path.end());

        node = parent_right[intersect];

        while (node != -1) {
            path.push_back(node);
            node = parent_right[node];
        }

        cout << "Path: ";

        for (auto& v : path)
            cout << v << " ";

        cout << "\nDistance: " << path.size() - 1 << endl;
    }
};