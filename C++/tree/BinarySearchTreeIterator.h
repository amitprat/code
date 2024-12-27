#pragma once
#include "../header.h"
#include "BinarySearchTree.h"

template <class T>
class BinarySearchTreeIterator {
    using TreeNode = BinarySearchTree<T>::Node;

   private:
    TreeNode *root = nullptr;

   public:
    class Iterator {
       private:
        TreeNode *root = nullptr;
        stack<TreeNode *> st;

       public:
        Iterator() : root(nullptr) {}
        Iterator(TreeNode *root) : root(root) {
            if (root) {
                while (root) {
                    st.push(root);
                    root = root->left;
                }

                root = st.top();
                st.pop();
            }
        }
        Iterator &operator=(const TreeNode &node) {
            this->root = node;
            return *this;
        }
        Iterator operator++() {
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

        Iterator operator++(int) {
            Iterator iter = *this;
            ++*this;

            return iter;
        }

        bool operator!=(const Iterator &other) {
            return root != other.root;
        }

        T operator*() {
            return root->val;
        }

        TreeNode &operator->() {
            return root;
        }

       public:
        Iterator begin() const noexcept {
            return Iterator(this->root);
        }

        Iterator end() const noexcept {
            return Iterator();
        }
    };

    void add(T val) {
        if (root == nullptr)
            root = new TreeNode(val);
        else
            add(val, root);
    }

    TreeNode *add(T val, TreeNode *cur) {
        if (cur == nullptr) {
            cur = new TreeNode(val);
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

    void inorder(TreeNode *root, stringstream &ss) {
        if (root) {
            inorder(root->left, ss);
            ss << root->val << " ";
            inorder(root->right, ss);
        }
    }

    // pretty print
    string to_string() {
        if (!root)
            return "";

        stringstream ss;
        queue<pair<TreeNode *, int>> q;
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

class BinarySearchTreeIteratorTest {
   public:
    static void test() {
        {
            BinarySearchTreeIterator<int> bst;
            bst.add(5);
            bst.add(4);
            bst.add(2);

            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (const auto &i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }
        {
            BinarySearchTreeIterator<int> bst;
            bst.add(1);

            cout << "Inorder traversal:  " << bst.inorder() << endl;

            cout << "Iterator traversal: ";
            for (const auto &i : bst) {
                cout << i << " ";
            }
            cout << endl;
        }
        {
            BinarySearchTreeIterator<int> bst;
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
            BinarySearchTreeIterator<int> bst;
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
    }
};