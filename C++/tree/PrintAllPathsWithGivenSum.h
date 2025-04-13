#pragma once
#include "../header.h"
#include "BinaryTree.h"

class PrintAllPathsWithGivenSum {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        PrintAllPathsWithGivenSum obj;
        Node* root = new Node(1);
        root->left = new Node(3);
        root->right = new Node(-1);
        root->left->left = new Node(2);
        root->left->right = new Node(1);
        root->left->right->left = new Node(1);
        root->right->left = new Node(4);
        root->right->left->left = new Node(1);
        root->right->left->right = new Node(2);
        root->right->right = new Node(5);
        root->right->right->right = new Node(6);

        // printLevelOrder(root);

        int sum = 5;
        cout << "Number of paths with sum = " << sum << ":" << obj.countPathsWithSum(root, sum) << endl;

        vector<vector<Node*>> res = obj.getPathWithGivenSum(root, sum);
    }

   public:
    int countPathsWithGivenSumBruteForce(Node* root, int sum) {
        if (!root) return 0;

        int cnt = countPathsWithGivenSumBruteForceFromThisNode(root, sum, 0);

        cnt += countPathsWithGivenSumBruteForce(root->left, sum);
        cnt += countPathsWithGivenSumBruteForce(root->right, sum);

        return cnt;
    }

    int countPathsWithGivenSumBruteForceFromThisNode(Node* root, int sum, int cur) {
        if (!root) return 0;

        int total = 0;
        cur += root->val;
        if (cur == sum) total++;

        total += countPathsWithGivenSumBruteForceFromThisNode(root->left, sum, cur);
        total += countPathsWithGivenSumBruteForceFromThisNode(root->right, sum, cur);

        return total;
    }

   public:
    int countPathsWithSum(Node* root, int sum) {
        unordered_map<int, int> map;

        map[0] = 1;  // for the 0 sum case
        return countPaths(root, sum, 0, map);
    }

    int countPaths(Node* root, int total, int curSum, unordered_map<int, int>& map) {
        if (!root) return 0;

        curSum += root->val;

        int result = map[curSum - total];  // find existing paths with given sum
        map[curSum]++;                     // count this as prefix path with this sum

        result += countPaths(root->left, total, curSum, map);
        result += countPaths(root->right, total, curSum, map);

        // backtrack
        map[curSum]--;

        return result;
    }

   public:
    // TODO
    vector<vector<Node*>> getPathWithGivenSum(Node* root, int sum) {
        vector<vector<Node*>> res;
        unordered_map<int, vector<vector<Node*>>> map;

        getPathWithGivenSum(root, sum, 0, map, {});

        return map[sum];
    }

    // TODO
    void getPathWithGivenSum(
        Node* root, int total, int curSum,
        unordered_map<int, vector<vector<Node*>>> map,
        vector<Node*> prefixPath) {
        if (!root) return;

        if (map.find(total - (curSum + root->val)) != map.end()) {
            // map[total - (curSum + root->val)]
        }
    }
};
