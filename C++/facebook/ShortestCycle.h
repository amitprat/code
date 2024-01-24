#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5744699292778496

given a target node in a directed graph, find the shortest cycle including this node, return the whole path.

Straight forward BFS to find shortest path from s to s. Just ensure, the start node is not put into the visited nodes at first. Since there is no relaxation (unweighted graph) needed, the order of first discovery from BFS is as well the shortest path to that node. Store it's parent and don't care about rediscovery (as usually). If I get back to S, I have the shortest cycle.

Runtime is O(|V|+|E|), especially if there is no cycle, this might happen (e.g. if you
give me the root of a tree as start). Space is O(|V|).

The core of the algo is this code, assuming s is the given node:


unordered_map<Node*, Node*> parents;
deque<Node*> q{ 1, s };

while (!q.empty()) {
    Node* u = q.back();
    q.pop_back();
    for (auto v : u->adjacents_) {
        if (parents.count(v) > 0) continue;
        parents[v] = u;
        if (v == s) {
            q.clear();
            break;
        } else {
            q.push_front(v);
        }
    }
}

*/

class ShortestCycle {
    struct Node {
        int val;
        vector<Node*> neighbours;
        Node(int val) :val(val) {}
    };
public:
    static void test() {
        ShortestCycle obj;
        Node* root = new Node(1);
        Node* node3 = new Node(3);
        Node* node5 = new Node(5);
        Node* node6 = new Node(6);
        Node* node7 = new Node(7);
        root->neighbours.push_back(new Node(2));
        root->neighbours.push_back(node3);
        root->neighbours.push_back(new Node(4));

        root->neighbours[0]->neighbours.push_back(node5);
        root->neighbours[1]->neighbours.push_back(node5);
        root->neighbours[1]->neighbours.push_back(node6);
        root->neighbours[2]->neighbours.push_back(node6);

        root->neighbours[1]->neighbours[0]->neighbours.push_back(node7);
        root->neighbours[1]->neighbours[1]->neighbours.push_back(node7);

        root->neighbours[1]->neighbours[0]->neighbours[0]->neighbours.push_back(node3);

        vector<int> nodes = obj.findShortestCycle(root->neighbours[1]);
        cout << to_string(nodes) << endl;
    }

    vector<int> findShortestCycle(Node* node) {
        queue<Node*> q;
        q.push(node);
        unordered_map<Node*, Node*> parent;
        bool cycle = false;
        while (!q.empty()) {
            auto f = q.front(); q.pop();

            for (auto& neighbour : f->neighbours) {
                if (parent.find(neighbour) != parent.end()) continue;
                parent[neighbour] = f;
                if (neighbour->val == node->val) {
                    cycle = true;
                    break;
                }
                else
                    q.push(neighbour);
            }
        }

        if (cycle) {
            vector<int> result;
            auto cur = node;
            do {
                result.push_back(cur->val);
                cur = parent[cur];
            } while (cur != node);
            result.push_back(cur->val);
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }
};