#pragma once
#include "../Header.h"

class BinarySearchTreeQuestions
{
private:
    class BinarySearchTree {
    private:
        struct Node {
            int key, val;
            Node* left, * right;
            Node(int key, int val) : key(key), val(val), left(nullptr), right(nullptr) {}
            string to_string() {
                return format("({}:{})", key, val);
            }
        };

        Node* root = nullptr;

    public:
        void insert(int key, int val) {
            root = insert(root, key, val);
        }

        void remove(int key) {
            cout << "Removing node " << key << endl;
            root = remove(root, key);
        }

        int find(int key) {
            return find(root, key);
        }

        void inorder() {
            cout << "Inorder: ";
            inorder(root);
            cout << endl;
        }

        Node* findSuccessor(int key) {
            return findSuccessor(root, key);
        }

        void convertToDLL() {
            cout << "Convert BST to DLL: ";
            root = convertToDLL(root);

            while (root) {
                cout << root->to_string() << ", ";
                root = root->right;
            }
            cout << endl;
        }

        Node* successor(int key) {
            Node* succ = nullptr;
            return successor(root, key, succ);
        }

        pair<int, int> findNodesWithGivenSumInBSTUsingExtraSpace(int sum) {
            vector<int> inorderArray;

            inorder(root, inorderArray);

            int i = 0, j = inorderArray.size() - 1;
            while (i < j) {
                if (inorderArray[i] + inorderArray[j] == sum) return { inorderArray[i], inorderArray[j] };
                else if (inorderArray[i] + inorderArray[j] < sum) i++;
                else j--;
            }

            return { -1, -1 };
        }

        pair<int, int> findNodesWithGivenSumInBSTWithoutExtraSpace(int sum) {
            stack<Node*> leftSt, rightSt;
            Node* left = root, * right = root;
            bool moveLeft = true, moveRight = true;

            while (true) {
                if (moveLeft) {
                    while (left) {
                        leftSt.push(left); left = left->left;
                    }
                    if (!leftSt.empty()) { left = leftSt.top(); leftSt.pop(); }
                }
                moveLeft = false;

                if (moveRight) {
                    while (right) {
                        rightSt.push(right); right = right->right;
                    }
                    if (!rightSt.empty()) { right = rightSt.top(); rightSt.pop(); }
                }
                moveRight = false;

                if (left == nullptr || right == nullptr || left == right) return { -1, -1 };

                if (left->key + right->key == sum) return { left->key, right->key };
                else if (left->key + right->key < sum) {
                    left = left->right; moveLeft = true;
                }
                else {
                    right = right->left; moveRight = true;
                }
            }

            return { -1, -1 };
        }
    private:
        Node* insert(Node* root, int key, int val) {
            if (!root) return new Node(key, val);

            if (key < root->key) root->left = insert(root->left, key, val);
            else if (key > root->key) root->right = insert(root->right, key, val);

            return root;
        }

        Node* remove(Node* root, int key) {
            if (!root) return root;

            if (key < root->key) root->left = remove(root->left, key);
            else if (key > root->key) root->right = remove(root->right, key);
            else {
                if (!root->left) return root->right;
                else if (!root->right) return root->left;
                else {
                    Node* successor = minValueNode(root->right);
                    root->key = successor->key;
                    root->val = successor->val;

                    root->right = remove(root->right, successor->key);
                }
            }

            return root;
        }

        int find(Node* root, int key) {
            if (!root) return INT_MAX;

            if (key == root->key) return root->val;
            else if (key < root->key) return find(root->left, key);
            else return find(root->right, key);
        }

        Node* findSuccessor(Node* root, int key) {
            if (!root) return root;

            Node* succ = nullptr;
            if (key <= root->key) {
                succ = root;
                auto maxOnLeft = findSuccessor(root->left, key);
                if (maxOnLeft != nullptr) succ = maxOnLeft;
            }
            else if (key > root->key) succ = findSuccessor(root->right, key);

            return succ;
        }

        Node* minValueNode(Node* root) {
            while (root && root->left) root = root->left;
            return root;
        }

        void inorder(Node* root) {
            if (root) {
                inorder(root->left);
                cout << root->to_string() << ", ";
                inorder(root->right);
            }
        }

        void inorder(Node* root, vector<int>& inorderArr) {
            if (!root) return;

            inorder(root->left, inorderArr);
            inorderArr.push_back(root->key);
            inorder(root->right, inorderArr);
        }

        Node* convertToDLL(Node* root) {
            if (!root) return root;

            static Node* next = nullptr;

            convertToDLL(root->right);

            root->right = next;
            if (next) next->left = root;
            next = root;

            convertToDLL(root->left);

            return next;
        }

        void convertToDLL(Node* root, Node*& head) {
            if (!root) return;

            static Node* prev = nullptr;

            convertToDLL(root->left, head);

            if (!head) head = root;
            else prev->right = root;
            root->left = prev;
            prev = root;

            convertToDLL(root->right, head);
        }

        Node* successor(Node* root, int key, Node* succ) {
            if (!root) return succ;

            if (key == root->key) {
                if (root->right) return minValueNode(root->right);
            }
            else if (key < root->key) {
                succ = root;
                return successor(root->left, key, succ);
            }

            return succ;
        }

        void findNodesWithGivenSumInBST(Node* root, int sum, pair<int, int>& result) {
            if (!root) return;


        }
    };
public:
    static void test()
    {
        BinarySearchTree bst;
        bst.insert(2, 2);
        bst.insert(4, 4);
        bst.insert(1, 1);
        bst.insert(6, 6);
        bst.insert(5, 5);

        bst.inorder();

        cout << "Successor of 0: " << bst.findSuccessor(0)->key << ":" << bst.findSuccessor(0)->val << endl;
        cout << "Successor of 2: " << bst.findSuccessor(2)->key << ":" << bst.findSuccessor(2)->val << endl;
        cout << "Successor of 3: " << bst.findSuccessor(3)->key << ":" << bst.findSuccessor(3)->val << endl;
        //cout << bst.findSuccessor(10)->key << ":" << bst.findSuccessor(10)->val << endl;

        bst.remove(2);
        bst.remove(4);
        bst.remove(3);

        bst.inorder();

        //bst.convertToDLL();

        for (int i = 0; i < 20; i++) {
            cout << "Find pair sum for " << i << ", ";
            auto res = bst.findNodesWithGivenSumInBSTWithoutExtraSpace(i);
            cout << "Pair = " << to_string(res) << endl;
        }
    }
};