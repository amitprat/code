#pragma once
#include "../header.h"

namespace dag {
    class Graph {
    private:
        unordered_map<int, vector<int>> nodes;

    public:
        void addNode(int node) {
            nodes.insert({ node,{} });
        }
        void addEdge(int src, int dst) {
            nodes[src].push_back(dst);
        }
        int size() {
            return nodes.size();
        }
        vector<int> getNodes() {
            vector<int> res;
            for (auto& e : nodes) {
                res.push_back(e.first);
            }
            return res;
        }
        vector<int> adjNodes(int u) {
            return nodes[u];
        }
    };

    class DetectCycleInDag {
    public:
        static void test() {
            DetectCycleInDag obj;
            Graph g;
            g.addNode(1);
            g.addNode(2);
            g.addNode(3);
            g.addNode(4);
            g.addNode(5);

            g.addEdge(1, 2);
            g.addEdge(2, 3);
            g.addEdge(3, 4);
            g.addEdge(1, 4);
            g.addEdge(5, 1);
            g.addEdge(4, 5);

            bool res = obj.hasCycle(g);
            cout << "Has Cycle = " << res << endl;
        }

        bool hasCycle(Graph g) {
            unordered_set<int> visited, recstack;

            for (auto node : g.getNodes()) {
                if (hasCycle(g, recstack, node)) return true;
            }
            return false;
        }

    private:
        bool hasCycle(Graph g, unordered_set<int>& visited, unordered_set<int>& recstack, int node) {
            if (visited.find(node) == visited.end()) {
                visited.insert(node);
                recstack.insert(node);

                for (auto v : g.adjNodes(node)) {
                    if (visited.find(v) == visited.end()) {
                        if (hasCycle(g, visited, recstack, v)) return true;
                    }
                    else if (recstack.find(v) != recstack.end()) {
                        return true;
                    }
                }
            }
            recstack.erase(node);
            return false;
        }

        bool hasCycle(Graph g, unordered_set<int>& recstack, int u) {
            if (recstack.find(u) != recstack.end()) return true;
            recstack.insert(u);

            for (auto v : g.adjNodes(u)) {
                if (hasCycle(g, recstack, v)) return true;
            }
            recstack.erase(u);
        }
    };
}