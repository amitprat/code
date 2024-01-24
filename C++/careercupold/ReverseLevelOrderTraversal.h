#pragma once
#include "../Header.h"

class ReverseLevelOrderTraversal {
public:
	static void test() {
		ITNode* root = new ITNode(3);
		root->left = new ITNode(9);
		root->right = new ITNode(20);
		root->right->left = new ITNode(15);
		root->right->right = new ITNode(7);

		vector<vector<int>> result = doReverseLevelOrderUsingRecursion(root);

		print(result);
	}

	static vector<vector<int>> doReverseLevelOrderUsingRecursion(ITNode* root) {
		vector<vector<int>> result;

		doReverseLevelOrderUsingRecursion(root, result, 0);
		reverse(result.begin(), result.end());

		return result;
	}

	static void doReverseLevelOrderUsingRecursion(ITNode* root, vector<vector<int>>& result, int level) {
		if (!root) return;

		if (level >= result.size()) result.push_back({});
		result[level].push_back(root->val);

		doReverseLevelOrderUsingRecursion(root->left, result, level + 1);
		doReverseLevelOrderUsingRecursion(root->right, result, level + 1);
	}

	static vector<vector<int>> doReverseLevelOrderUsingQueue(ITNode* root) {
		queue<ITNode*> q;
		q.push(root);
		vector<vector<int>> result;
		int level = 0;

		while (!q.empty()) {
			int n = q.size();
			if (level >= result.size()) result.push_back({});
			while (n--) {
				auto f = q.front(); q.pop();
				result[level].push_back(f->val);

				if (f->left) q.push(f->left);
				if (f->right) q.push(f->right);
			}
			level++;
		}

		std::reverse(result.begin(), result.end());

		return result;
	}

	static vector<vector<int>> doReverseLevelOrderUsingStack(ITNode* root) {
		stack<ITNode*> st;
		st.push(root);
		vector<vector<int>> result;
		int level = 0;

		while (!st.empty()) {
			int n = st.size();
			if (level >= result.size()) result.push_back({});
			while (n--) {
				auto f = st.top(); st.pop();
				result[level].push_back(f->val);

				if (f->right) st.push(f->right);
				if (f->left) st.push(f->left);
			}
			level++;
		}

		std::reverse(result.begin(), result.end());

		return result;
	}
};