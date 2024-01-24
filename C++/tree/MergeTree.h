#include "../header.h"

class MergeTree {
    class Node {
       public:
        int val;
        Node *left, *right;
        Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

   private:
    static void test() {
        IterativeInorderTraversal obj;

        Node* node1 = new Node(10);
        node1->left = new Node(5);
        node1->left->left = new Node(3);
        node1->left->left->right = new Node(4);
        node1->right = new Node(13);
        node1->right->left = new Node(11);
        node1->right->right = new Node(15);
        node1->right->right->right = new Node(17);

        obj.mergeTrees(node1, node2);
    }

   private:
    Node* mergeTree(Node* node1, Node* node2) {
        if (!node1) return node2;
        if (!node2) return node1;

        Node* newNode = new Node(node1->val + node2->val);
        newNode->left = mergeTree(node1->left, node2->left);
        newNode->right = mergeTree(node1->right, node2->right);

        return newNode;
    }

   private:
    void mergeTrees(Node* node1, Node* node2) {
        vector<int> merged;
        stack<Node*> st1;
        stack<Node*> st2;
        while (true) {
            while (node1) {
                st1.push(node1);
                node1 = node1->left;
            }

            while (node2) {
                st2.push(node2);
                node2 = node2->left;
            }

            if (st1.empty() && st2.empty()) break;
            if (st1.empty()) {
                node2 = st2.top();
                st2.pop();
                merged
            }
        }
    }
};