#include "../header.h"

class RawPtrTreeReadExp {
    struct Node {
        int key;
        int val;
        Node *left, *right;
        Node(int key, int val) : key(key), val(val), left(left), right(right) {}
    };

    class RawTree {
        Node *root = nullptr;

       public:
        void insert(int key, int val) {
            root = insertInternal(root, key, val);
        }

        int search(int key) {
            auto val = search(root, key);
        }

        bool remove(int key) {
            return true;
        }

        void inorder() {
            inorderInternal(root);
        }

       private:
        Node *insertInternal(Node *root, int key, int val) {
            if (!root) return new Node(key, val);

            if (key == root->key)
                root->val = val;
            else if (key < root->key)
                root->left = insertInternal(root->left, key, val);
            else
                root->right = insertInternal(root->right, key, val);

            return root;
        }

        void inorderInternal(Node *root) {
            if (!root) return;

            inorderInternal(root->left);
            // cout<<root->to_string()<<" ";
            int key = root->key;
            int val = root->val;
            inorderInternal(root->right);
        }

        int search(Node *root, int key) {
            if (!root) return INT_MIN;

            if (key == root->key) return root->val;

            if (key < root->key)
                return search(root->left, key);
            else
                return search(root->right, key);
        }
    };

    class PerformanceTester {
        static void test() {
            RawTree *tree = new RawTree();
            tree->insert(0,0);
            tree->insert(1,1);
            tree->inorder(2,2);
            tree->insert(3,3);

            atomic<int> readPerSecond = 0;

            auto start = chrono::system_clock::now();
            auto end = chrono::system_clock::now();
            while(!done) {
                tree->inorder();
                readPerSecond++;

                if(readPerSecond/1000 == 0) {
                    end = chrono::system_clock::now();
                }
            }
        }
    };
}