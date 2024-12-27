#pragma once
#include "../header.h"

class BinarySearchTreeQuestions {
   private:
    class BinarySearchTree {
       private:
        struct Node {
            int key, val;
            Node *left, *right;
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

        Node* insert(Node* root, int key, int val) {
            if (!root) return new Node(key, val);

            if (key < root->key)
                root->left = insert(root->left, key, val);
            else if (key > root->key)
                root->right = insert(root->right, key, val);

            return root;
        }

       public:
        void remove(int key) {
            cout << "Removing node " << key << endl;
            root = remove(root, key);
        }

        Node* remove(Node* root, int key) {
            if (!root) return root;

            if (key < root->key)
                root->left = remove(root->left, key);
            else if (key > root->key)
                root->right = remove(root->right, key);
            else {
                if (!root->left)
                    return root->right;
                else if (!root->right)
                    return root->left;
                else {
                    Node* successor = minValueNode(root->right);
                    root->key = successor->key;
                    root->val = successor->val;

                    root->right = remove(root->right, successor->key);
                }
            }

            return root;
        }

        Node* minValueNode(Node* root) {
            while (root && root->left) root = root->left;
            return root;
        }

       public:
        int find(int key) {
            return find(root, key);
        }

        int find(Node* root, int key) {
            if (!root) return INT_MAX;

            if (key == root->key)
                return root->val;
            else if (key < root->key)
                return find(root->left, key);
            else
                return find(root->right, key);
        }

       public:
        void inorder() {
            cout << "Inorder: ";
            inorder(root);
            cout << endl;
        }

        void inorder(Node* root) {
            if (root) {
                inorder(root->left);
                cout << root->to_string() << ", ";
                inorder(root->right);
            }
        }

       public:
        Node* findSuccessor(int key) {
            return findSuccessor(root, key);
        }

        Node* findSuccessor(Node* root, int key) {
            if (!root) return root;

            Node* succ = nullptr;
            if (key <= root->key) {
                succ = root;
                auto maxOnLeft = findSuccessor(root->left, key);
                if (maxOnLeft != nullptr) succ = maxOnLeft;
            } else if (key > root->key) {
                succ = findSuccessor(root->right, key);
            }

            return succ;
        }

       public:
        void convertToDLL() {
            cout << "Convert BST to DLL: ";
            root = convertToDLL(root);

            while (root) {
                cout << root->to_string() << ", ";
                root = root->right;
            }
            cout << endl;
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

            if (!head)
                head = root;
            else
                prev->right = root;
            root->left = prev;
            prev = root;

            convertToDLL(root->right, head);
        }

       public:
        Node* successor(int key) {
            Node* succ = nullptr;
            successor(root, key, succ);

            return succ;
        }

        void successor(Node* root, int key, Node* succ) {
            if (!root) return;

            if (key < root->key) {
                succ = root;
                successor(root->left, key, succ);
            } else {
                successor(root->right, key, succ);
            }
        }

       public:
        Node* successor2(int key) {
            return successor(root, key);
        }

        Node* successor2(Node* root, int key) {
            if (!root) return nullptr;

            if (key < root->key) {
                auto succ = successor2(root->left, key);
                if (!succ) return root;
            } else {
                return successor2(root->right, key);
            }
        }

       public:
        pair<int, int> findNodesWithGivenSumInBSTUsingExtraSpace(int sum) {
            vector<int> inorderArray;

            inorder(root, inorderArray);

            int i = 0, j = inorderArray.size() - 1;
            while (i < j) {
                if (inorderArray[i] + inorderArray[j] == sum)
                    return {inorderArray[i], inorderArray[j]};
                else if (inorderArray[i] + inorderArray[j] < sum)
                    i++;
                else
                    j--;
            }

            return {-1, -1};
        }

        void inorder(Node* root, vector<int>& inorderArr) {
            if (!root) return;

            inorder(root->left, inorderArr);
            inorderArr.push_back(root->key);
            inorder(root->right, inorderArr);
        }

       public:
        pair<int, int> findNodesWithGivenSumInBSTWithoutExtraSpace(int sum) {
            stack<Node*> leftSt, rightSt;
            Node *left = root, *right = root;
            bool moveLeft = true, moveRight = true;

            while (true) {
                if (moveLeft) {
                    while (left) {
                        leftSt.push(left);
                        left = left->left;
                    }
                    if (!leftSt.empty()) {
                        left = leftSt.top();
                        leftSt.pop();
                    }
                }
                moveLeft = false;

                if (moveRight) {
                    while (right) {
                        rightSt.push(right);
                        right = right->right;
                    }
                    if (!rightSt.empty()) {
                        right = rightSt.top();
                        rightSt.pop();
                    }
                }
                moveRight = false;

                if (left == nullptr || right == nullptr || left == right) return {-1, -1};

                if (left->key + right->key == sum)
                    return {left->key, right->key};
                else if (left->key + right->key < sum) {
                    left = left->right;
                    moveLeft = true;
                } else {
                    right = right->left;
                    moveRight = true;
                }
            }

            return {-1, -1};
        }

       public:
        pair<int, int> findNodesWithGivenSumInBST(Node* root, int sum, pair<int, int>& result) {
            if (!root) return;

            BSTIterator left(root, true);
            BSTIterator right(root, false);

            while (left && right) {
                if (left->val + right->val == sum)
                    return {root->left, root->right};
                else if (left->val + right->val < sum) {
                    if (!left.hasNext()) return {-1, -1};
                    left = left.next();
                } else {
                    if (!right.hasNext()) return {-1, -1};
                    right = right.next();
                }
            }
        }

        class BSTIterator {
            stack<Node*> st;
            Node* root = nullptr;
            bool leftToRight = true;

           public:
            BSTIterator(Node* root, bool leftToRight) : root(root), leftToRight(leftToRight) {
                this->moveToEnd();
            }

            void moveToEnd() {
                if (leftToRight) {
                    while (root) {
                        st.push(root);
                        root = root->left;
                    }
                    if (!st.empty()) {
                        root = st.top();
                        st.pop();
                    }
                } else {
                    while (root) {
                        st.push(root);
                        root = root->right;
                    }
                    if (!st.empty()) {
                        root = st.top();
                        st.pop();
                    }
                }
            }

            bool hasNext() {
                return !root || !st.empty();
            }

            Node* next() {
                auto res = root;

                if (leftToRight)
                    root = root->right;
                else
                    root = root->left;

                this->moveToEnd();

                return res;
            }
        }
    };

   public:
    static void test() {
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
        // cout << bst.findSuccessor(10)->key << ":" << bst.findSuccessor(10)->val << endl;

        bst.remove(2);
        bst.remove(4);
        bst.remove(3);

        bst.inorder();

        // bst.convertToDLL();

        for (int i = 0; i < 20; i++) {
            cout << "Find pair sum for " << i << ", ";
            auto res = bst.findNodesWithGivenSumInBSTWithoutExtraSpace(i);
            cout << "Pair = " << to_string(res) << endl;
        }
    }
};