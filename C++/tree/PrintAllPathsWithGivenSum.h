#pragma once
#include "../header.h"
#include "TreeNode.h"

class PrintAllPathsWithGivenSum {
public:
    static void test() {
        PrintAllPathsWithGivenSum obj;
        TreeNode<int>* root = new TreeNode<int>(1);
        root->left = new TreeNode<int>(3);
        root->right = new TreeNode<int>(-1);
        root->left->left = new TreeNode<int>(2);
        root->left->right = new TreeNode<int>(1);
        root->left->right->left = new TreeNode<int>(1);
        root->right->left = new TreeNode<int>(4);
        root->right->left->left = new TreeNode<int>(1);
        root->right->left->right = new TreeNode<int>(2);
        root->right->right = new TreeNode<int>(5);
        root->right->right->right = new TreeNode<int>(6);

        printLevelOrder(root);

        int sum = 5;
        cout << "Number of paths with sum = " << sum << ":" << obj.countPathsWithSum(root, sum) << endl;

        vector<vector<TreeNode<int>*>> res = obj.getPathWithGivenSum(root, sum);
    }

    int countPathsWithSum(TreeNode<int>* root, int sum) {
        unordered_map<int, int> map;
        int result = 0;
        countPaths(root, sum, 0, map, result);
        return result;
    }

    vector<vector<TreeNode<int>*>> getPathWithGivenSum(TreeNode<int>* root, int sum)
    {
        vector<vector<TreeNode<int>*>> res;
        unordered_map<int, vector<vector<TreeNode<int>*>>> map;

        getPathWithGivenSum(root, sum, map, {}, 0);

        return map[sum];
    }
private:
    void countPaths(TreeNode<int>* root, int sum, int cur, unordered_map<int, int>& map, int& result) {
        if (!root) return;
        if (cur + root->val == sum) result++;
        result += map[sum - (cur + root->val)];
        map[cur + root->val]++;
        countPaths(root->left, sum, cur + root->val, map, result);
        countPaths(root->right, sum, cur + root->val, map, result);
        map[cur + root->val]--;
    }

    void getPathWithGivenSum(TreeNode<int>* root, int sum, unordered_map<int, vector<vector<TreeNode<int>*>>> map, vector<TreeNode<int>*> cur, int curSum) {
        if (!root) return;
        if (curSum + root->val == sum) {
            map[sum].push_back(cur);
        }
        if (map.find(sum - (curSum + root->val)) != map.end()) {
            map[sum]
        }
    }
};
