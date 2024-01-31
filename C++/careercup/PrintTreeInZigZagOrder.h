#include "../header.h"

/*
 * https://www.geeksforgeeks.org/zigzag-tree-traversal/
 */
class PrintTreeInZigZagOrder {
   public:
    vector<vector<int>> zigzag_order_using_reverse(TreeNode* root) {
        auto level_order = level_order_using_queue(root);

        for (int i = 1; i < level_order.size(); i += 2) {
            std::reverse(level_order[i].begin(), level_order[i].end());
        }

        return level_order;
    }

    vector<vector<int>> level_order_using_queue(TreeNode* root) {
    }

   public:
    vector<vector<int>> zigzag_order_using_two_stacks(TreeNode* root) {
        // take 2 stacks, st1 st2
        // put first element in st1, keep flag leftToRight = true
        // if leftToRight == true: put element in st2 as [left, right], so right becomes at top.
        // else leftToRight == false: put element in st2 as [right, left], so left becomes at top.
        // swap st1 and st2, flip leftToRight flag and keep iterating

        // stack method works here as stack keeps elements from [left -> right] or [right -> left] strictly.
        // Even if we use 2 queues to achieve that, it won't work as queue order for next level won't be in strict order. (unless we reverse)
    }

   public:
    vector<vector<int>> zigzag_order_using_deque(TreeNode* root) {
        if (!root) return {};

        deque<TreeNode*> dq;
        dq.push_back(root);

        vector<vector<int>> result;
        bool leftToRight = true;

        while (!dq.empty()) {
            int n = dq.size();
            vector<int> curRow;

            while (n--) {
                if (leftToRight) {
                    auto cur = dq.back();
                    curRow.push_back(cur->val);

                    if (cur->right) dq.push_front(cur->right);
                    if (cur->left) dq.push_front(cur->left);
                } else {
                    auto cur = dq.front();
                    curRow.push_back(cur->val);

                    if (cur->left) dq.push_back(cur->left);
                    if (cur->right) dq.push_back(cur->right);
                }
            }

            result.push_back(curRow);
            leftToRight = !leftToRight;
        }
    }

   public:
    vector<vector<int>> zigzag_order_using_recursion(TreeNode* root) {
        int h = height(root);

        bool ltor = false;
        for (int l = 1; l <= h; l++) {
            zigzag_order_using_recursion(root, l, ltor);
            ltor = !ltor;
        }
    }

    void zigzag_order_using_recursion(TreeNode* root, int level, int ltor) {
        if (!root) return;

        if (level == 1) {
            cout << root->val << " ";
            return;
        }

        if (ltor) {
            zigzag_order_using_recursion(root->left, level - 1, ltor);
            zigzag_order_using_recursion(root->right, level - 1, ltor);
        } else {
            zigzag_order_using_recursion(root->right, level - 1, ltor);
            zigzag_order_using_recursion(root->left, level - 1, ltor);
        }
    }
};