#pragma once
#include "../header.h"
#include "BinaryTree.h"

class NearestLeafNode {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        NearestLeafNode obj;
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->right->left = new Node(31);
        root->right->right = new Node(32);
        root->left->left = new Node(4);
        root->left->right = new Node(5);
        root->left->left->left = new Node(6);
        root->left->left->right = new Node(7);
        root->left->right->left = new Node(8);
        root->left->right->right = new Node(9);
        root->left->left->left->left = new Node(10);
        root->left->left->left->right = new Node(11);
        root->left->left->right->left = new Node(12);
        root->left->left->right->right = new Node(13);

        vector<int> testVals = {1, 2, 3, 4, 5, 6};
        for (int v : testVals) {
            auto [leafVal, dist] = obj.findNearestLeafRecur(root, v);
            cout << "Nearest leaf to " << v << " = " << leafVal->val
                 << " (distance = " << dist << ")" << endl;
        }
    }

   public:
    pair<Node*, int> findNearestLeafRecur(Node* root, int targetVal) {
        if (!root) return {nullptr, INT_MAX};
        if (!root->left && !root->right) return {root, 1};

        auto left = findNearestLeafRecur(root->left, targetVal);
        auto right = findNearestLeafRecur(root->right, targetVal);

        if (root->val == targetVal) return left.second < right.second ? left : right;

        return (left.second < right.second) ? make_pair(left.first, left.second + 1) : make_pair(right.first, right.second + 1);
    }

   public:
    // Returns {nearest leaf value, distance}
    pair<Node*, int> findNearestLeaf(Node* root, int targetVal) {
        if (!root) return {nullptr, -1};

        unordered_map<Node*, Node*> parent;
        Node* target = nullptr;

        // Step 1: Build parent map + find target node
        fillParent(root, nullptr, targetVal, target, parent);
        if (!target) return {nullptr, -1};

        // Step 2: BFS outward from target
        queue<pair<Node*, int>> q;  // node + distance
        unordered_set<Node*> visited;
        q.push({target, 0});
        visited.insert(target);

        while (!q.empty()) {
            auto [curr, dist] = q.front();
            q.pop();

            // Found a leaf node
            if (!curr->left && !curr->right)
                return {curr, dist};

            if (curr->left && !visited.count(curr->left)) {
                visited.insert(curr->left);
                q.push({curr->left, dist + 1});
            }

            if (curr->right && !visited.count(curr->right)) {
                visited.insert(curr->right);
                q.push({curr->right, dist + 1});
            }

            if (parent[curr] && !visited.count(parent[curr])) {
                visited.insert(parent[curr]);
                q.push({parent[curr], dist + 1});
            }
        }

        return {nullptr, -1};
    }

   private:
    void fillParent(Node* node, Node* parent, int targetVal, Node*& target,
                    unordered_map<Node*, Node*>& parentMap) {
        if (!node) return;

        parentMap[node] = parent;

        if (node->val == targetVal) target = node;

        fillParent(node->left, node, targetVal, target, parentMap);
        fillParent(node->right, node, targetVal, target, parentMap);
    }
};