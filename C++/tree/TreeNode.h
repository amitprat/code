#pragma once
#include "../header.h"

template <class T>
class TreeNode {
public:
    T val;
    TreeNode* left, * right;
    TreeNode(T val) : val(val), left(nullptr), right(nullptr) {}

    string to_string() {
        return std::to_string(val);
    }
};

template <class T>
void printLevelOrder(TreeNode<T>* root) {
    queue<TreeNode<T>*> q;
    if (root) q.push(root);
    int level = 0;
    while (!q.empty()) {
        queue<TreeNode<T>*> tmp;
        int sz = q.size();
        cout << "Level " << level++ << " : ";
        while (sz--) {
            auto* cur = q.front(); q.pop();
            cout << cur->to_string() << " ";
            if (cur->left) tmp.push(cur->left);
            if (cur->right) tmp.push(cur->right);
        }
        cout << endl;
        swap(q, tmp);
    }
}
