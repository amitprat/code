#include "../header.h"

class FlatternBinaryTreeToLinkedList {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        FlatternBinaryTreeToLinkedList obj;
        Node *root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(5);
        root->left->left = new Node(3);
        root->left->right = new Node(4);
        root->right->right = new Node(6);

        obj.flatten2(root);

        obj.printList(root);
    }

   private:
    void flattenBinaryTreeUsingPreorder(ITNode *root) {
        stack<ITNode *> st;
        preOrder(root, st);

        ITNode *last = nullptr;
        while (!st.empty()) {
            auto cur = st.top();
            st.pop();
            cur->right = last;
            cur->left = nullptr;
            last = cur;
        }
    }

    void preOrder(ITNode *root, stack<ITNode *> &st) {
        if (!root) return;
        st.push(root);
        preOrder(root->left, st);
        preOrder(root->right, st);
    }

   private:
    ITNode *flattenRecurse(ITNode *root) {
        if (!root) return root;
        ITNode *right = flattenRecurse(root->right);
        ITNode *left = flattenRecurse(root->left);

        if (right) right->left = nullptr;
        ITNode *tmp = left;
        while (tmp && tmp->right) tmp = tmp->right;
        if (tmp) {
            tmp->right = right;
            tmp->left = nullptr;
        }
        if (left)
            root->right = left;
        else
            root->right = right;
        root->left = nullptr;

        return root;
    }

   private:
    void flatten(Node *root) {
        while (root) {
            if (root->left) {
                auto right = root->right;
                root->right = root->left;
                root->left = nullptr;

                Node *next = root->right;
                while (next && next->right) {
                    next = next->right;
                }

                next->right = right;
            }

            root = root->right;
        }
    }

   private:
    void flatten2(Node *root) {
        Node *prev = nullptr;

        stack<Node *> st;
        st.push(root);

        while (!st.empty()) {
            auto cur = st.top();
            st.pop();

            if (cur->right) st.push(cur->right);
            if (cur->left) st.push(cur->left);

            if (!prev)
                prev = cur;
            else
                prev->right = cur;
            cur->left = nullptr;

            prev = cur;
        }
    }

    void flattenUsingIterativePreorderTraversal(ITNode *root) {
        stack<ITNode *> st;
        st.push(root);

        while (!st.empty()) {
            auto cur = st.top();
            st.pop();
            auto left = cur->left;
            auto right = cur->right;

            if (cur->right) cur->right->left = nullptr;
            if (cur->left) {
                cur->left->right = cur->right;
                cur->left->left = nullptr;
            }
            if (cur->left)
                cur->right = cur->left;
            else
                cur->right = cur->right;
            cur->left = nullptr;

            if (right) st.push(right);
            if (left) st.push(left);
        }
    }

   private:
    void flatten3(Node *root) {
        if (!root) return;
        if (root->left) {
            // flatten the lef tree first
            flatten3(root->left);

            // connect the root->left as root->right and set left pointer as null
            auto right = root->right;
            root->right = root->left;
            root->left = nullptr;

            // find rightmost node in left tree and connect the original right node to its end
            auto *tmp = root->right;
            while (tmp && tmp->right) tmp = tmp->right;
            tmp->right = right;
        }

        // flatten the right node.
        flatten3(root->right);
    }

   private:
    ITNode *flatten(ITNode *node) {
        if (!node) return node;

        ITNode *left = flatten(node->left);
        ITNode *right = flatten(node->right);

        node->left = nullptr;
        node->right = left;
        getRightMostNode(node)->right = right;

        return node;
    }

    ITNode *getRightMostNode(ITNode *node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

   private:
    void printList(Node *root) {
        while (root) {
            cout << root->val << " ";
            root = root->right;
        }
        cout << endl;
    }
};