#include "../header.h"

class FindLongestBranch {
    using Node = BinaryTree<int>::Node;

    static void test() {
        Node *root;
    }

   public:
    vector<Node *> longestBranch(Node *root) {
        if (!root) return {};

        auto leftMax = longestBranch(root->left);
        auto rightMax = longestBranch(root->right);

        if (leftMax.size() > rightMax.size()) {
            leftMax.push_back(root);
            return leftMax;
        } else {
            rightMax.push_back(root);
            return rightMax;
        }
    }
};