#pragma once
#include "../Header.h"

class PrintAllPathsWithGivenSumInBinaryTree {
public:
	static void test() {
		ITNode* root = new ITNode(1);
		root->left = new ITNode(3);
		root->left->left = new ITNode(1);
		root->left->right = new ITNode(2);
		root->right = new ITNode(4);
		root->right->right = new ITNode(7);
		int k = 10;
		cout << "Paths with sum " << k << " are :\n";
		vector<int> path;
		findKSumPathDownwards(root, k, path);

		cout << "All paths with sum " << k << " are :\n";
		findAllKSumPath2(root, k);
	}

	// It only print paths from top to down
	static void findKSumPathDownwards(ITNode* root, int k, vector<int>& path) {
		if (!root) return;

		path.push_back(root->val);
		findKSumPathDownwards(root->left, k, path);
		findKSumPathDownwards(root->right, k, path);

		int curSum = 0;
		for (int i = path.size() - 1; i >= 0; i--) {
			curSum += path[i];
			if (curSum == k) {
				cout << to_string(path) << endl;
			}
		}

		path.pop_back();
	}

	static void findAllKSumPath2(ITNode* root, int k) {
		unordered_map<int, vector<int>> paths;
		findAllKSumPath2(root, k, 0, {}, paths);
	}

	static int findAllKSumPath2(ITNode* root, int k, int curSum, vector<int> path, unordered_map<int, vector<int>>& paths) {
		if (!root) return 0;

		int left = findAllKSumPath2(root->left, k, curSum, path, paths);
		int right = findAllKSumPath2(root->right, k, curSum, path, paths);

		curSum += root->val;
		path.push_back(root->val);
		paths[curSum] = path;

		if (paths.find(k - curSum) != paths.end()) {
			cout << path << " ";
			cout << root->val << " ";
			cout << paths[k - curSum - root->val];
			cout << endl;
		}
	}
};