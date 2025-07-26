#include "../header.h"

class FindLongestBranch {
    using Node = BinaryTree<int>::Node;

    static void test() {
        Node* root;
    }

   public:
    vector<Node*> longestBranch(Node* root) {
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

   public:
    std::vector<Node*> longestBranch2(Node* root) {
        if (!root) return {};

        auto leftMax = longestBranch2(root->left);
        auto rightMax = longestBranch2(root->right);

        // Choose the longer branch
        std::vector<Node*> longer =
            (leftMax.size() > rightMax.size()) ? std::move(leftMax) : std::move(rightMax);

        // Add current node at the front (so result is root -> leaf)
        longer.insert(longer.begin(), root);
        return longer;
    }
};