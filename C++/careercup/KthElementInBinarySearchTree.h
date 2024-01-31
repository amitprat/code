#include "../header.h"

/*
You are given a binary search tree and a positive integer K. Return the K-th element of the tree.
No pre-processing or modifying of the tree is allowed.
*/
class KthElementInBinarySearchTree {
    struct Node {
        int val;
        int size = 0;
        Node *left, *right;
        Node(int val, int size) : val(val), size(size), left(nullptr), right(nullptr) {}
        string to_string() {
            return std::to_string(val);
        }
    };

   public:
    int kthElement(Node *root, int &k) {
        if (!root) return INT_MIN;
        int left = kthElement(root->left, k);
        if (left != INT_MIN) return left;
        k--;
        if (k == 0) return root->val;
        return kthElement(root->right, k);
    }

    int kthElement(Node *root, int k) {
        stack<Node *> st;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            if (st.empty()) break;
            root = st.top();
            st.pop();
            k--;
            if (k == 0) return root->val;
            root = root->right;
        }
        return INT_MIN;
    }

    int kthElement(Node *root, int k) {
        if (!root) return INT_MIN;
        int sz = size(root->left) + 1;
        if (sz == k) return root->val;
        if (k < sz) return kthElement(root->left, k);
        return kthElement(root->right, k - sz);
    }

    Node *insert(Node *root, int element) {
        if (!root) return new Node(element, 1);
        if (element == root->val) return root;

        root->size++;
        if (element < root->val) return insert(root->left, element);
        return insert(root->right, element);
    }

   private:
    int size(Node *node) {
        if (!node) return 0;
        return node->size;
    }
};