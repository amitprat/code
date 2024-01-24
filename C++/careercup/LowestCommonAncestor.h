#include "../header.h"

class LowestCommonAncestor {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        Node *root = new Node(5);
        root->left = new Node(3);
        root->left->left = new Node(1);
        root->left->right = new Node(4);
        root->right = new Node(10);
        root->right->left = new Node(7);
        root->right->right = new Node(20);

        LowestCommonAncestor obj;
        int val1 = 7, val2 = 20;
        Node *result = obj.lcaInBT1Wrapper(root, val1, val2);
        cout << format("LCA of {} and {} is {}.", val1, val2, result ? result->val : -1) << endl;

        val1 = 1, val2 = 4;
        result = obj.lcaInBT1Wrapper(root, val1, val2);
        cout << format("LCA of {} and {} is {}.", val1, val2, result ? result->val : -1) << endl;

        val1 = 1, val2 = 5;
        result = obj.lcaInBT1Wrapper(root, val1, val2);
        cout << format("LCA of {} and {} is {}.", val1, val2, result ? result->val : -1) << endl;

        val1 = 10, val2 = 30;
        result = obj.lcaInBT1Wrapper(root, val1, val2);
        cout << format("LCA of {} and {} is {}.", val1, val2, result ? result->val : -1) << endl;
    }

    Node *lcaInBST(Node *root, int val1, int val2) {
        if (!root) return nullptr;

        if (val1 < root->val && val2 < root->val) {
            return lcaInBST(root->left, val1, val2);
        } else if (val1 > root->val && val2 > root->val) {
            return lcaInBST(root->right, val1, val2);
        } else {
            return root;
        }
    }

    Node *lcaInBT(Node *root, int val1, int val2) {
        if (!root) return root;

        if (root->val == val1 || root->val == val2) return root;

        auto left = lcaInBT(root->left, val1, val2);
        auto right = lcaInBT(root->right, val1, val2);

        if (left && right) return root;

        return left ? left : right;
    }

    Node *lcaInBT1Wrapper(Node *root, int val1, int val2) {
        bool val1Found = false, val2Found = false;

        auto result = lcaInBT1(root, val1, val2, val1Found, val2Found);

        if (result) {
            return result;
        } else if (val1Found) {
            cout << format("Only {} is found", val1) << endl;
        } else if (val2Found) {
            cout << format("Only {} is found", val2) << endl;
        } else {
            cout << format("None is found") << endl;
        }

        return nullptr;
    }

    Node *lcaInBT1(Node *root, int val1, int val2, bool &val1Found, bool &val2Found) {
        if (!root) return root;

        bool lval1 = false, lval2 = false;
        auto left = lcaInBT1(root->left, val1, val2, lval1, lval2);
        if (left) return left;

        bool rval1 = false, rval2 = false;
        auto right = lcaInBT1(root->right, val1, val2, rval1, rval2);
        if (right) return right;

        if (val1 == root->val) lval1 = true;
        if (val2 == root->val) val2Found = true;

        if (lval1 && rval2 || lval2 && rval1) {
            val1Found = val2Found = true;
            return root;
        } else if (lval1 || rval1) {
            val1Found = true;
        } else if (rval2 || lval2) {
            val2Found = true;
        }

        return nullptr;
    }
};