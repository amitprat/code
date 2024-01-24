#pragma once
#include "../Header.h"

class SerializeDeserializeTree {
public:
	static void test() {
		cout << "First tree:" << endl;
		{
			ITNode* root = new ITNode(1);
			root->left = new ITNode(2);
			root->right = new ITNode(3);
			root->left->right = new ITNode(5);
			root->left->right->left = new ITNode(6);
			root->right = new ITNode(7);
			root->right->left = new ITNode(8);
			root->right->right = new ITNode(9);
			root->right->right->right = new ITNode(11);
			cout << to_string(root) << endl;

			{
				vector<int> res;
				serialize(root, res);
				int index = 0;
				ITNode* node = deserialize(res, index);
				cout << to_string(node) << endl;
			}

			{
				vector<int> res = serialize(root);
				ITNode* node = deserialize(res);
				cout << to_string(node) << endl;
			}

			{
				SerializeDeserializeTree1 obj;
				string serialized = obj.serialize(root);
				cout << serialized << endl;
				ITNode* newTree = obj.deserialize(serialized);
				cout << to_string(newTree) << endl;
			}

			{
				SerializeDeserializeTree2 obj;
				string serialized = obj.serialize(root);
				cout << serialized << endl;
				ITNode* newTree = obj.deserialize(serialized);
				cout << to_string(newTree) << endl;
			}
		}
		cout << endl;

		cout << "Second tree:" << endl;
		{
			ITNode* root = new ITNode(1);
			root->left = new ITNode(2);
			root->right = new ITNode(3);
			root->left->left = new ITNode(4);
			root->left->right = new ITNode(5);
			root->left->left->left = new ITNode(6);
			root->right = new ITNode(7);
			root->right->left = new ITNode(8);
			root->right->right = new ITNode(9);
			root->right->right->left = new ITNode(10);
			root->right->right->right = new ITNode(11);
			cout << to_string(root) << endl;

			{
				vector<int> res;
				serialize(root, res);
				int index = 0;
				ITNode* node = deserialize(res, index);
				cout << to_string(node) << endl;
			}

			{
				vector<int> res = serialize(root);
				ITNode* node = deserialize(res);
				cout << to_string(node) << endl;
			}
		}
		cout << endl;

		cout << "Third tree:" << endl;
		{
			ITNode* root = new ITNode(1);
			root->left = new ITNode(2);
			root->right = new ITNode(3);
			root->left->left = new ITNode(4);
			root->right->left = new ITNode(5);
			root->right->right = new ITNode(6);
			cout << to_string(root) << endl;

			{
				vector<int> res;
				serialize(root, res);
				int index = 0;
				ITNode* node = deserialize(res, index);
				cout << to_string(node) << endl;
			}

			{
				vector<int> res = serialize(root);
				ITNode* node = deserialize(res);
				cout << to_string(node) << endl;
			}
		}
	}

	static void serialize(ITNode* root, vector<int>& res) {
		if (!root) {
			res.push_back(INT_MIN);
			return;
		}

		res.push_back(root->val);

		serialize(root->left, res);
		serialize(root->right, res);
	}

	static ITNode* deserialize(vector<int>& res, int& index) {
		if (index >= res.size()) return nullptr;

		auto cur = res[index++];
		if (cur == INT_MIN) return nullptr;

		auto root = new ITNode(cur);
		root->left = deserialize(res, index);
		root->right = deserialize(res, index);

		return root;
	}

	static vector<int> serialize(ITNode* root) {
		vector<int> result;
		if (!root) return result;

		queue<ITNode*> q;
		q.push(root);

		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			if (cur == nullptr) result.push_back(INT_MIN);
			else result.push_back(cur->val);

			if (cur != nullptr) {
				q.push(cur->left);
				q.push(cur->right);
			}
		}

		return result;
	}

	static ITNode* deserialize(vector<int> result) {
		if (result.empty()) return nullptr;
		queue<ITNode*> q;
		int index = 0;
		ITNode* root = new ITNode(result[index++]);
		q.push(root);

		while (!q.empty()) {
			auto cur = q.front(); q.pop();

			auto val = result[index++];
			cur->left = val != INT_MIN ? new ITNode(val) : nullptr;

			val = result[index++];
			cur->right = val != INT_MIN ? new ITNode(val) : nullptr;

			if (cur->left) q.push(cur->left);
			if (cur->right) q.push(cur->right);
		}

		return root;
	}

	class SerializeDeserializeTree1 {
	public:
		string serialize(ITNode* root) {
			string serialized;
			serialize(root, serialized);

			if (!serialized.empty()) serialized.erase(0, 1);

			return serialized;
		}

		void serialize(ITNode* root, string& serialized) {
			if (!root) { serialized = serialized + "," + "#"; return; }

			serialized += "," + std::to_string(root->val);

			serialize(root->left, serialized);
			serialize(root->right, serialized);
		}

		ITNode* deserialize(string& serialized) {
			stringstream ss(serialized);
			char delim = ',';

			ITNode* root = deserialize(serialized, ss, delim);
			return root;
		}

		ITNode* deserialize(string& serialized, stringstream& ss, char delim) {
			string cur;
			if (!getline(ss, cur, delim)) return nullptr;
			if (cur == "#") return nullptr;

			ITNode* node = new ITNode(stoi(cur));
			node->left = deserialize(serialized, ss, delim);
			node->right = deserialize(serialized, ss, delim);

			return node;
		}
	};

	class SerializeDeserializeTree2 {
	public:
		string serialize(ITNode* root) {
			string serialized;

			queue<ITNode*> q;
			q.push(root);

			while (!q.empty()) {
				auto cur = q.front(); q.pop();
				if (cur == nullptr) serialized = serialized + "," + "#";
				else serialized += "," + std::to_string(cur->val);

				if (cur) {
					q.push(cur->left);
					q.push(cur->right);
				}
			}

			if (!serialized.empty()) serialized.erase(0, 1);

			return serialized;
		}

		ITNode* deserialize(string& serialized) {
			stringstream ss(serialized);
			char delim = ',';
			int index = 0;

			string cur;
			if (!getline(ss, cur, delim) || cur == "#") return nullptr;

			queue<ITNode*> q;
			q.push(new ITNode(stoi(cur)));
			ITNode* root = q.front();

			while (!q.empty()) {
				auto curNode = q.front(); q.pop();

				if (getline(ss, cur, delim) && cur != "#") curNode->left = new ITNode(stoi(cur));
				if (getline(ss, cur, delim) && cur != "#") curNode->right = new ITNode(stoi(cur));

				if (curNode->left) q.push(curNode->left);
				if (curNode->right) q.push(curNode->right);
			}

			return root;
		}
	};
};