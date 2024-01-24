#include "../header.h"

/*
https://careercup.com/question?id=5165570324430848

Given a Binary Search tree of integers, you need to return the number of nodes having values between two given integers.
You can assume that you already have some extra information at each node (number of children in left and right subtrees !!).

Interesting, this was one of the questions of my second interview. This was my answer:
- Suppose we know the size of the left subtree for each node.
- We want the number of values in the interval [A, B]. This is the same as the number of values up to B minus the number of values less than A.
- So we can reduce this question to finding the number of values up to X.
1) Start at the root
2a) If the value we search is less or equal to current node value. Then this node and all values to the right are larger or equal to this value and we can ignore them. Recurse on the left subtree
2b) The value we search is larger than the current node value. Then this node and all values in the left subtree are less than this value. Recurse on the right subtree.

On a balanced BST, this algorithm takes O(log N) time.

struct TreeNode {
    TreeNode * left, * right;
    int val, left_subtree_size;
};
int getLess(TreeNode* node, int v) {
    if (node == NULL)
        return 0;
    if (v <= node->val)
        return getLess( node->left , v);
    return 1 + node->left_subtree_size + getLess(node->right, v);
}
int Solve(TreeNode * root , int from, int to) {
    return getLess(root, to+1) - getLess(root, from);  // to+1 to get #values <= to
}
*/
class NodesBetweenTwoValuesInBST {
    struct Node {
        int val;
        int sz;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val), sz(1) {}
    };

   public:
    static void test() {
        Node *root;
    }

   private:
    int nodesBetweenValues(Node *root, int val1, int val2) {
        return nodesLessThan(root, val2) - nodesLessThan(root, val1);
    }

    int nodesLessThan(Node *root, int val) {
        if (!root) return 0;
        if (val > root->val) 1 + size(root->left) + nodesLessThan(root->right, val);
        if (val <= root->val) return nodesLessThan(root->left, val);
    }
};