/*
Implementating iterator over binary search tree to print
items in sorted order.

Inorder traversal:  2 4 5
Iterator traversal: 2 4 5
Inorder traversal:  1
Iterator traversal: 1
Inorder traversal:  1 19
Iterator traversal: 1 19
Inorder traversal:  1 2 4 10 19 122 200 1000
Iterator traversal: 1 2 4 10 19 122 200 1000
Inorder traversal:
Iterator traversal:
*/
#pragma once
#include "../header.h"
using namespace std;

template <class T>
class BinarySearchTree {
    class Node;

   private:
    Node* root = nullptr;

   public:
    class Node {
       public:
        T val;
        Node* left;
        Node* right;
        Node(T val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

    class Iterator {
       private:
        Node* root = nullptr;
        stack<Node*> st;

       public:
        Iterator() : root(nullptr) {}
        Iterator(Node* otherRoot) : root(otherRoot) {
            if (root) {
                while (root) {
                    st.push(root);
                    root = root->left;
                }
                root = st.top();
                st.pop();
            }
        }
        Iterator operator=(Node& node) {
            this->root = node;
            return *this;
        }
        Iterator operator++();

        Iterator operator++(int) {
            Iterator iter = *this;
            ++*this;
            return iter;
        }

        bool operator!=(Iterator& other) {
            return root != other.root;
        }

        T operator*() {
            return root->val;
        }
    };

    void add(T val) {
        if (root == nullptr)
            root = new Node(val);
        else
            add(val, root);
    }

    Node* add(T val, Node* cur) {
        if (cur == nullptr) {
            cur = new Node(val);
        } else {
            if (val < cur->val) {
                cur->left = add(val, cur->left);
            } else if (val > cur->val) {
                cur->right = add(val, cur->right);
            }
        }
        return cur;
    }
    Iterator begin() {
        return Iterator(root);
    }
    Iterator end() {
        return Iterator(nullptr);
    }

    string inorder() {
        stringstream ss;
        inorder(root, ss);
        return ss.str();
    }

    void inorder(Node* root, stringstream& ss) {
        if (root) {
            inorder(root->left, ss);
            ss << root->val << " ";
            inorder(root->right, ss);
        }
    }

    string to_string() {
        if (!root) return "";
        stringstream ss;
        queue<pair<Node*, int>> q;
        q.push({root, 20});

        while (!q.empty()) {
            int sz = q.size();
            stringstream cur;
            stringstream next;
            int prev = 0;
            int nextprev = 0;
            while (sz--) {
                auto item = q.front();
                q.pop();
                cur << setw(item.second - prev) << item.first->val;
                if (item.first->left) {
                    next << setw(item.second - nextprev - 2) << "/";
                    nextprev = item.second - nextprev - 2;
                    q.push({item.first->left, item.second - 4});
                }
                if (item.first->right) {
                    next << setw(item.second - nextprev + 2) << "\\";
                    nextprev = item.second - nextprev + 2;
                    q.push({item.first->right, item.second + 4});
                }
                prev = item.second;
            }
            cur << endl;
            next << endl;
            ss << cur.str();
            ss << next.str();
        }

        return ss.str();
    }
};

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator++() {
    if (root == nullptr) {
        return Iterator(nullptr);
    }
    // Move to next
    root = root->right;
    while (root) {
        st.push(root);
        root = root->left;
    }
    if (!st.empty()) {
        root = st.top();
        st.pop();
    }
    return *this;
}

class BinarySearchTreeTest {
   public:
    static void test() {
        {
            BinarySearchTree<int> bst;
            bst.add(5);
            bst.add(4);
            bst.add(2);

            cout << bst.to_string() << endl;
            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (auto i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }
        {
            BinarySearchTree<int> bst;
            bst.add(1);

            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (auto i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }
        {
            BinarySearchTree<int> bst;
            bst.add(1);
            bst.add(19);

            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (auto i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }

        {
            BinarySearchTree<int> bst;
            bst.add(1);
            bst.add(200);
            bst.add(19);
            bst.add(2);
            bst.add(10);
            bst.add(1000);
            bst.add(122);
            bst.add(4);

            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (auto i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }
        {
            BinarySearchTree<int> bst;

            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (auto i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
};