#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=6040159610994688


Find the nearest leaf node from given node in binary tree.

A node might not be an ancestor to its nearest leaf node.
*/
class NearestLeafNodeFromGivenNode
{
public:
	static void test() {
		ITNode* root = new ITNode(1);
		root->left = new ITNode(2);
		root->right = new ITNode(3);
		root->left->left = new ITNode(4);
		root->left->right = new ITNode(5);
		root->left->left->left = new ITNode(6);
		root->left->left->right = new ITNode(7);
		root->left->left->left->left = new ITNode(10);
		root->left->left->left->right = new ITNode(11);
		root->left->left->right->left = new ITNode(12);
		root->left->left->right->right = new ITNode(13);
		root->left->right->left = new ITNode(8);
		root->left->right->right = new ITNode(9);
		root->left->right->left->left = new ITNode(14);
		root->left->right->left->right = new ITNode(15);
		root->left->right->right->left = new ITNode(16);
		root->left->right->right->right = new ITNode(17);

		unordered_map<ITNode*, pair<int, ITNode*>> distanceToNearestLeafNode;
		distanceToLeafNode(root, distanceToNearestLeafNode);

		{
			ITNode* target = root->left;
			unordered_map<ITNode*, int> nodesInPath;
			fillNodesInPath(root, target, nodesInPath);

			int minDistance = INT_MAX;
			auto res1 = getMinimumDistanceToLeafNode(root, target, minDistance);

			auto res = getMinimumDistance(target, nodesInPath, distanceToNearestLeafNode);
			assert(res.second == minDistance);

			cout << "Nearest leaf node from " << target->val << " is " << res.first->val << " and its distance: " << res.second << endl;
		}

		{
			ITNode* target = root->right;
			unordered_map<ITNode*, int> nodesInPath;
			fillNodesInPath(root, target, nodesInPath);

			int minDistance = INT_MAX;
			auto res1 = getMinimumDistanceToLeafNode(root, target, minDistance);

			auto res = getMinimumDistance(target, nodesInPath, distanceToNearestLeafNode);
			assert(res.second == minDistance);

			cout << "Nearest leaf node from " << target->val << " is " << res.first->val << " and its distance: " << res.second << endl;
		}

		{
			ITNode* target = root->left->left;
			unordered_map<ITNode*, int> nodesInPath;
			fillNodesInPath(root, target, nodesInPath);

			int minDistance = INT_MAX;
			auto res1 = getMinimumDistanceToLeafNode(root, target, minDistance);

			auto res = getMinimumDistance(target, nodesInPath, distanceToNearestLeafNode);
			assert(res.second == minDistance);

			cout << "Nearest leaf node from " << target->val << " is " << res.first->val << " and its distance: " << res.second << endl;
		}

		{
			ITNode* target = root->left->right;
			unordered_map<ITNode*, int> nodesInPath;
			fillNodesInPath(root, target, nodesInPath);

			int minDistance = INT_MAX;
			auto res1 = getMinimumDistanceToLeafNode(root, target, minDistance);

			auto res = getMinimumDistance(target, nodesInPath, distanceToNearestLeafNode);
			assert(res.second == minDistance);

			cout << "Nearest leaf node from " << target->val << " is " << res.first->val << " and its distance: " << res.second << endl;
		}
	}

	static pair<ITNode*, int> distanceToLeafNode(ITNode* root, unordered_map<ITNode*, pair<int, ITNode*>>& distanceToNearestLeafNode)
	{
		if (!root) return { nullptr,0 };
		if (!root->left && !root->right) {
			distanceToNearestLeafNode.insert({ root, {1,root} });
			return { root,1 };
		}

		auto left = distanceToLeafNode(root->left, distanceToNearestLeafNode);
		auto right = distanceToLeafNode(root->right, distanceToNearestLeafNode);
		ITNode* target = nullptr;
		if (left.second <= right.second)target = left.first;
		else target = right.first;

		distanceToNearestLeafNode.insert({ root, {1 + min(left.second, right.second), target} });

		return { root, 1 + min(left.second, right.second) };
	}

	static int fillNodesInPath(ITNode* root, ITNode* target, unordered_map<ITNode*, int>& nodesInPath)
	{
		if (!root) return INT_MAX;
		if (root == target) {
			nodesInPath.insert({ root,0 });
			return 1;
		}

		int left = fillNodesInPath(root->left, target, nodesInPath);
		int right = fillNodesInPath(root->right, target, nodesInPath);

		if (left != INT_MAX || right != INT_MAX) nodesInPath.insert({ root,1 + min(left,right) });

		return (left != INT_MAX || right != INT_MAX) ? 1 + min(left, right) : INT_MAX;
	}

	static pair<ITNode*, int> getMinimumDistance(ITNode* target, unordered_map<ITNode*, int> nodesInPath,
		unordered_map<ITNode*, pair<int, ITNode*>> distanceToNearestLeafNode)
	{
		int distance = INT_MAX;
		ITNode* result = nullptr;
		for (auto node : nodesInPath) {
			int leafDistance = 0;
			if (target != node.first) leafDistance = node.second + distanceToNearestLeafNode[node.first].first - 1;
			else leafDistance = distanceToNearestLeafNode[node.first].first;

			if (leafDistance < distance) {
				distance = leafDistance;
				result = distanceToNearestLeafNode[node.first].second;
			}
		}

		return { result, distance };
	}

	static pair<int, int> getMinimumDistanceToLeafNode(ITNode* root, ITNode* target, int& minDistance)
	{
		if (!root) return { INT_MAX, 0 }; // {distanceToTarget, distanceToLeafNode}

		auto left = getMinimumDistanceToLeafNode(root->left, target, minDistance);
		auto right = getMinimumDistanceToLeafNode(root->right, target, minDistance);

		bool isOnLeft = false, isOnRight = false;
		if (left.first != INT_MAX) isOnLeft = true;
		else if (right.first != INT_MAX) isOnRight = true;

		int distanceToTarget = INT_MAX;
		if (root == target) {
			// if the node is same as target node, then the minimum distance must be min(leftDistance, rightDistance)
			int curMin = 1 + min(left.second, right.second);
			minDistance = min(minDistance, curMin);
			distanceToTarget = 1;
		}
		else if (isOnLeft && left.first + 1 + right.second < minDistance) {
			// if the targetNode is on left, the minDistance is min of old min distance and (distance from current node to target node on left + 1(root) + distance on right)
			int curMin = left.first + 1 + right.second;
			distanceToTarget = left.first + 1;
			minDistance = min(minDistance, curMin);
		}
		else if (isOnRight && right.first + 1 + left.second < minDistance) {
			int curMin = right.first + 1 + left.second;
			distanceToTarget = right.first + 1;
			minDistance = min(minDistance, curMin);
		}

		return { distanceToTarget, 1 + min(left.second, right.second) };
	}
};