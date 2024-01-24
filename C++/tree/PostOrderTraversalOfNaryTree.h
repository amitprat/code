#include "../header.h"
/*
https://careercup.com/question?id=5682612859305984

Post order traversal for an N-ary tree iterative way.
Given,
struct Node {
  int val;
  vector<Node*> children;
};

Without modifying original structure.
*/
class PostOrderTraversalOfNaryTree {
    /*Recursive*/
    void postOrder(Node *root) {
        if (!root) return;
        for (auto node : root->children) {
            postOrder(node);
        }
        cout << root->val << " ";
    }

    /*Itervative*/
    void postOrder(Node *root) {
        if (!root) return;
        stack<Node *> st1, st2;
        st1.push(root);

        while (!st1.empty()) {
            Node *tmp = st1.top();
            st1.pop();

            for (auto node : tmp->children)
                st1.push(node);
            st2.push(tmp);
        }

        while (!st2.empty()) {
            cout << st2.top()->val << " ";
            st2.pop();
        }
    }
};