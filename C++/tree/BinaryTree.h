#pragma once
#include "../header.h"

template <typename T>
class BinaryTree {
   public:
    struct Node {
        T val;
        int sz;
        Node* left;
        Node* right;

        Node(T val) : val(val), sz(0), left(nullptr), right(nullptr) {}

        string to_string() const {
            return std::to_string(val);
        }
    };

   public:
    Node* root = nullptr;
    BinaryTree(Node* root = nullptr) : root(root) {}

   public:
    string preorder() const {
        stringstream ss;
        preorder(root, ss);
        return ss.str();
    }

    void preorder(Node* node, stringstream& ss) const {
        if (!node) return;

        ss << node->val << " ";
        preorder(node->left, ss);
        preorder(node->right, ss);
    }

   public:
    list<Node*> preorder_list() const {
        list<Node*> out;
        preorder(root, out);
        return out;
    }

    void preorder(Node* node, list<Node*>& out) const {
        if (!node) return;

        out.push_back(node);
        preorder(node->left, out);
        preorder(node->right, out);
    }

   public:
    string postorder() const {
        stringstream ss;
        postorder(root, ss);
        return ss.str();
    }

    void postorder(Node* node, stringstream& ss) const {
        if (!node) return;

        postorder(node->left, ss);
        postorder(node->right, ss);
        ss << node->val << " ";
    }

   public:
    string inorder() const {
        stringstream ss;
        inorder(root, ss);
        return ss.str();
    }

    void inorder(Node* node, stringstream& ss) const {
        if (!node) return;

        inorder(node->left, ss);
        ss << node->val << " ";
        inorder(node->right, ss);
    }

   public:
    string levelOrder() const {
        map<int, vector<T>> out;
        levelOrder(out);
        return stringifyMap(out);
    }

    void levelOrder(map<int, vector<T>>& out) const {
        queue<Node*> q;
        if (root) q.push(root);

        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            out[level] = {};

            for (int i = 0; i < sz; ++i) {
                Node* cur = q.front();
                q.pop();

                out[level].push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            ++level;
        }
    }

   public:
    string stringifyMap(const map<int, vector<T>>& m) const {
        ostringstream oss;
        oss << "{";
        bool first = true;
        for (const auto& [k, v] : m) {
            if (!first) oss << ", ";
            first = false;

            oss << k << ": [";
            for (size_t i = 0; i < v.size(); ++i) {
                oss << v[i];
                if (i < v.size() - 1) oss << ", ";
            }
            oss << "]";
        }
        oss << "}";
        return oss.str();
    }

   public:
    int height() const {
        return height(root);
    }
    int height(Node* node) const {
        if (!node) return 0;

        return 1 + max(height(node->left), height(node->right));
    }

   public:
    void test() {
        using Tree = BinaryTree<int>;
        Tree::Node* n1 = new Tree::Node(1);
        Tree::Node* n2 = new Tree::Node(2);
        Tree::Node* n3 = new Tree::Node(3);
        Tree::Node* n4 = new Tree::Node(4);
        Tree::Node* n5 = new Tree::Node(5);

        n1->left = n2;
        n1->right = n3;
        n2->left = n4;
        n2->right = n5;

        Tree tree(n1);

        assert(tree.preorder() == "1 2 4 5 3 ");
        assert(tree.postorder() == "4 5 2 3 1 ");
        assert(tree.inorder() == "4 2 5 1 3 ");
        assert(tree.levelOrder() == "{0: [1], 1: [2, 3], 2: [4, 5]}");
        assert(tree.height() == 3);

        delete n4;
        delete n5;
        delete n2;
        delete n3;
        delete n1;
    }
};