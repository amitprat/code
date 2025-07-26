#pragma once
#include "../header.h"

class CloneUndirectedGraph2 {
   private:
    class Node {
       public:
        int val;
        vector<Node*> neighbors;

        Node() {
            val = 0;
            neighbors = vector<Node*>();
        }

        Node(int _val) {
            val = _val;
            neighbors = vector<Node*>();
        }

        Node(int _val, vector<Node*> _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    };

   public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        unordered_map<Node*, Node*> nodeMap;
        return cloneGraph(node, nodeMap);
    }

   private:
    Node* cloneGraph(Node* node, unordered_map<Node*, Node*>& nodeMap) {
        if (!node) return nullptr;
        auto cloned = new Node(node->val);
        nodeMap[node] = cloned;

        for (auto& nb : node->neighbors) {
            if (nodeMap.contains(nb)) {
                cloned->neighbors.push_back(nodeMap[nb]);
            } else {
                cloned->neighbors.push_back(cloneGraph(nb, nodeMap));
            }
        }

        return cloned;
    }

    void bfs(Node* node) {
        if (!node) return;

        unordered_set<Node*> visited;
        queue<Node*> q;

        q.push(node);
        visited.insert(node);

        while (!q.empty()) {
            auto f = q.front();
            q.pop();
            cout << f->val << " ";

            for (auto& nb : f->neighbors) {
                if (!visited.contains(nb)) {
                    q.push(nb);
                    visited.insert(nb);
                }
            }
        }
    }

   public:
    static void test() {
        Node* n1 = new Node(1);
        Node* n2 = new Node(2);
        Node* n3 = new Node(3);
        Node* n4 = new Node(4);

        n1->neighbors.push_back(n2);
        n1->neighbors.push_back(n3);
        n2->neighbors.push_back(n1);
        n2->neighbors.push_back(n3);
        n3->neighbors.push_back(n2);
        n3->neighbors.push_back(n4);
        n4->neighbors.push_back(n1);
        n4->neighbors.push_back(n3);

        CloneUndirectedGraph2 obj;
        cout << "Bfs: ";
        obj.bfs(n1);
        cout << endl;

        cout << "Bfs: ";
        auto cloned = obj.cloneGraph(n1);
        obj.bfs(cloned);
        cout << endl;
    }
};