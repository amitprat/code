#pragma once
#include "../Header.h"

class FlattenTree {
public:
    static void test() {
        FlattenTree obj;
        ITNode* root = new ITNode(1);
        root->left = new ITNode(2);
        root->right = new ITNode(5);
        root->left->left = new ITNode(3);
        root->left->right = new ITNode(4);
        root->right->right = new ITNode(6);

        cout << to_string(root) << endl;

        //root = obj.flattenRecurse(root);
        obj.flattenUsingIterativePreorderTraversal(root);

        obj.traverse(root);
    }

    void flattenUsingIterativePreorderTraversal(ITNode* root) {
        stack<ITNode*> st;
        st.push(root);

        while (!st.empty()) {
            auto cur = st.top(); st.pop();
            auto left = cur->left;
            auto right = cur->right;

            if (cur->right) cur->right->left = nullptr;
            if (cur->left) {
                cur->left->right = cur->right;
                cur->left->left = nullptr;
            }
            if (cur->left) cur->right = cur->left;
            else cur->right = cur->right;
            cur->left = nullptr;

            if (right) st.push(right);
            if (left) st.push(left);
        }
    }

    ITNode* flattenRecurse(ITNode* root) {
        if (!root) return root;
        ITNode* right = flattenRecurse(root->right);
        ITNode* left = flattenRecurse(root->left);

        if (right) right->left = nullptr;
        ITNode* tmp = left;
        while (tmp && tmp->right) tmp = tmp->right;
        if (tmp) {
            tmp->right = right;
            tmp->left = nullptr;
        }
        if (left) root->right = left;
        else root->right = right;
        root->left = nullptr;

        return root;
    }

    void flatten(ITNode* root) {
        stack<ITNode*> st;
        preOrder(root, st);

        ITNode* last = nullptr;
        while (!st.empty()) {
            auto cur = st.top(); st.pop();
            cur->right = last;
            cur->left = nullptr;
            last = cur;
        }
    }

    void preOrder(ITNode* root, stack<ITNode*>& st) {
        if (!root) return;
        st.push(root);
        preOrder(root->left, st);
        preOrder(root->right, st);
    }

    void traverse(ITNode* head) {
        while (head) {
            cout << head->to_string() << " ";
            head = head->right;
        }
        cout << endl;
    }
};