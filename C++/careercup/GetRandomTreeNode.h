#include "../header.h"

class GetRandomTreeNode {
    struct Node {
        int val;
        int size = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val), size(1) {}
    };

    class BinarySearchTree {
       public:
        BinarySearchTree() {
            srand(time(nullptr));
        }

        Node *root = nullptr;

       public:
        void insert(int val) {
            root = insert(root, val);
        }

        Node *insert(Node *root, int val) {
            if (!root) return new Node(val);

            if (val < root->val) {
                root->size += 1;
                root->left = insert(root->left, val);
            } else if (val > root->val) {
                root->size += 1;
                root->right = insert(root->right, val);
            } else
                root->val = val;

            return root;
        }

       public:
        Node *find(int key) {
            if (!root) return nullptr;

            return find(root, key);
        }

        Node *find(Node *root, int key) {
            if (!root) return nullptr;

            if (key == root->val)
                return root;
            else if (key < root->val)
                return find(root->left, key);
            else
                return find(root->right, key);
        }

       public:
        bool remove(int key) {
            root = remove(root, key);

            return true;
        }

        Node *remove(Node *root, int key) {
            if (!root) return root;

            if (key < root->val) {
                root->size--;
                root->left = remove(root->left, key);
            } else if (key > root->val) {
                root->size--;
                root->right = remove(root->right, key);
            } else {
                if (!root->left || !root->right) {
                    Node *newRoot = root->left ? root->left : root->right;
                    delete root;

                    root = newRoot;
                } else {
                    Node *suc = getMin(root->right);
                    root->val = suc->val;

                    root->size--;
                    root->right = remove(root->right, suc->val);
                }
            }

            return root;
        }

        Node *getMin(Node *root) {
            if (!root) return root;

            while (root->left) {
                root = root->left;
            }

            return root;
        }

       public:
        Node *getRandom() {
            int sz = size(root);
            int r = 1 + (rand() % sz);

            return findNode(root, r);
        }

        Node *findNode(Node *root, int pos) {
            if (!root) return root;

            int lsz = size(root->left);
            if (pos == 1 + lsz)
                return root;
            else if (pos < 1 + lsz)
                return findNode(root->left, pos);
            else
                return findNode(root->right, pos - 1 - lsz);
        }

        int size(Node *root) {
            if (!root) return 0;
            return root->size;
        }

       public:
        void inorder() {
            cout << "Inorder: ";
            this->inorder(root);
            cout << endl;
        }

        void inorder(Node *root) {
            if (!root) return;

            inorder(root->left);
            cout << root->val << " ";
            inorder(root->right);
        }
    };

   public:
    static void test() {
        BinarySearchTree tree;
        tree.insert(4);
        tree.insert(1);
        tree.insert(3);
        tree.insert(5);
        tree.insert(2);
        tree.insert(6);

        tree.inorder();

        Node *node = nullptr;
        vector<int> keys = {3, 4, 1, 6, 6};
        bool res = false;
        for (auto &key : keys) {
            node = tree.find(key);
            cout << format("Key={} is found in tree, Result={}", key, (node ? "TRUE" : "FALSE")) << endl;

            node = tree.getRandom();
            cout << format("Random node is = {}", node ? node->val : -1) << endl;

            res = tree.remove(key);
            cout << format("Key={} is removed from tree, Result={}", key, (res ? "TRUE" : "FALSE")) << endl;

            node = tree.find(key);
            cout << format("Key={} is found in tree, Result={}", key, (node ? "TRUE" : "FALSE")) << endl;
        }

        tree.inorder();
        cout << endl;
    }
};