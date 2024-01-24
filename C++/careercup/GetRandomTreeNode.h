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

        void insert(int val) {
            root = insert(root, val);
        }

        Node *find(int key) {
            if (!root) return nullptr;

            return find(root, key);
        }

        bool remove(int key) {
            root = remove(root, key);

            return true;
        }

        Node *getRandom() {
            int sz = size(root);
            int r = 1 + (rand() % sz);

            return findNode(root, r);
        }

        void inorder() {
            cout << "Inorder: ";
            this->inorder(root);
            cout << endl;
        }

       private:
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
                    swap(root->val, suc->val);

                    root->size--;
                    root->right = remove(root->right, suc->val);
                }
            }

            return root;
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

        Node *getMin(Node *root) {
            if (!root) return root;

            while (root->left) {
                root = root->left;
            }

            return root;
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
        int key = 3;
        bool res = false;
        {
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

        key = 4;
        {
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

        key = 1;
        {
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

        key = 6;
        {
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

        key = 6;
        {
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