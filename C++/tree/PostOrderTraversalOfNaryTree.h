#pragma once
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
   private:
    struct Node {
        int val;
        vector<Node *> children;
    };

   public:
    /*Recursive*/
    void postOrderRecursive(Node *root) {
        if (!root) return;

        for (auto node : root->children) {
            postOrderRecursive(node);
        }
        cout << root->val << " ";
    }

    /*Itervative*/
    void postOrderIter(Node *root) {
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

   public:
    static void test() {
        Node *root = new Node(1);
        root->children.push_back(new Node(2));
        root->children.push_back(new Node(3));
        root->children.push_back(new Node(4));
        root->children[0]->children.push_back(new Node(5));
        root->children[0]->children.push_back(new Node(6));
        root->children[0]->children.push_back(new Node(7));

        PostOrderTraversalOfNaryTree obj;

        cout << "Post order traversal using iterative: ";
        obj.postOrderIter(root);
        cout << endl;

        cout << "Post order traversal using recursive: ";
        obj.postOrderRecursive(root);
        cout << endl;
    }
};