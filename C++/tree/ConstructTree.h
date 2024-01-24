#pragma once
#include "../Header.h"

class ConstructTree {
public:
	static void test() {
		ConstructTree obj;

		ITNode* root = new ITNode(1);
		root->left = new ITNode(2);
		root->right = new ITNode(3);
		root->left->left = new ITNode(4);
		root->left->right = new ITNode(5);
		root->right->left = new ITNode(6);
		cout << to_string(root) << endl;

		vector<int> preorder, inorder;
		obj.getPreorder(root, preorder);
		obj.getInorder(root, inorder);

		unordered_map<int, int> map;
		for (int i = 0; i < inorder.size(); i++) {
			map[inorder[i]] = i;
		}

		ITNode* cur = obj.constructTree(preorder, inorder, 0, inorder.size() - 1, map);
		cout << to_string(cur) << endl;
	}

	ITNode* constructTree(vector<int>& preorder, vector<int>& inorder, int l, int r, unordered_map<int, int>& map)
	{
		if (l > r) return nullptr;

		static int index = 0;
		ITNode* root = new ITNode(preorder[index++]);
		if (l == r) return root;

		int pos = map[root->val];

		root->left = constructTree(preorder, inorder, l, pos - 1, map);
		root->right = constructTree(preorder, inorder, pos + 1, r, map);

		return root;
	}

	void getPreorder(ITNode* root, vector<int>& order) {
		if (!root) return;
		order.push_back(root->val);

		getPreorder(root->left, order);
		getPreorder(root->right, order);
	}

	void getInorder(ITNode* root, vector<int>& order) {
		if (!root) return;

		getInorder(root->left, order);
		order.push_back(root->val);
		getInorder(root->right, order);
	}
};