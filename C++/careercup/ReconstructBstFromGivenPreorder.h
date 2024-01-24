#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=14419694
Given preorder traversal array of a BST, recontruct the BST.

This can be solved in O(n) only. The approach am using is, keep a separate stack of node pointers. Push on the 1st node. Keep on traversing the preorder traversal
1. if the value of stack top is more than the current node value, then make the current node left pointer of stack top.
2. if the value of stack top is less that current node value, keep popping from the stack till value of stack top is more than current node. Then make current node the right child of last popped element.
Push the current node on stack in both the cases.

It may seem like an O(n^2) algo, but we are pushing and popping every element on stack only once so this is O(n) time and space.

*/
class ReconstructBstFromGivenPreorder
{
	class Node {
	public:
		int val;
		Node* left, * right;
		Node(int val, Node* left = nullptr, Node* right = nullptr) :val(val), left(left), right(right) {}
	};

public:
	static void test() {
		Node* root = new Node(5);
		root->left = new Node(2);
		root->left->left = new Node(1);
		root->left->right = new Node(3);
		root->right = new Node(7);
		root->right->left = new Node(6);
		root->right->right = new Node(8);

		vector<int> result;
		preorder(root, result);
		cout << to_string(result) << endl;

		Node* newRoot = constructBST(result);
		vector<int> newResult;
		preorder(newRoot, newResult);
		cout << to_string(newResult) << endl;
	}

	static void preorder(Node* root, vector<int>& result)
	{
		if (!root) return;
		result.push_back(root->val);
		preorder(root->left, result);
		preorder(root->right, result);
	}

	static Node* constructBst(vector<int>& newResult)
	{
		if (newResult.empty()) return nullptr;
		Node* newNode = new Node(newResult[0]);
		stack<Node*> st;
		st.push(newNode);

		for (int i = 1; i < newResult.size(); i++) {
			Node* cur = new Node(newResult[i]);
			if (st.top()->val > cur->val) {
				st.top()->left = cur;
			}
			else {
				Node* prev = nullptr;
				while (!st.empty() && st.top()->val < cur->val) {
					prev = st.top(); st.pop();
				}
				prev->right = cur;
			}
			st.push(cur);
		}

		return newNode;
	}

	static Node* constructBST(vector<int>& preorder) {
		if (preorder.empty()) return nullptr;
		Node* root = new Node(preorder[0]);

		stack<Node*> st;
		st.push(root);

		for (int i = 1; i < preorder.size(); i++) {
			auto newNode = new Node(preorder[i]);
			if (newNode->val < st.top()->val) {
				st.top()->left = newNode;
			}
			else {
				Node* prev = nullptr;
				while (!st.empty() && st.top()->val < newNode->val) {
					prev = st.top(); st.pop();
				}
				prev->right = newNode;
			}
			st.push(newNode);
		}

		return root;
	}
};