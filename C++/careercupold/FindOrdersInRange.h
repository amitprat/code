#pragma once
#include "../Header.h"

class FindOrdersInRange {
	struct Node {
		double time;
		int val;
		int leftSum = 0;
		Node* left, * right;
		Node(double time, int val) :time(time), val(val), left(nullptr), right(nullptr) {}
	};
	struct Node1 {
		double time;
		int val;
		int leftSum = 0;
		Node1(double time, int val) :time(time), val(val) {}
	};
	Node* root = nullptr;
	vector<Node1> nodes;
public:
	void add(double time, int val) {
		root = add(root, time, val);
	}
	static void test() {
		FindOrdersInRange obj;
		obj.add1(1.15, 15);
		obj.add1(1.30, 20);
		obj.add1(1.45, 5);
		obj.add1(2.00, 10);
		obj.add1(3, 100);
		obj.add1(5, 200);

		cout << "Orders in range 1-2 = " << obj.findOrders1(1, 2) << endl;
		cout << "Orders in range 2-3 = " << obj.findOrders1(2, 3) << endl;
		cout << "Orders in range 3-5 = " << obj.findOrders1(3, 5) << endl;
		cout << "Orders in range 1-2.30 = " << obj.findOrders1(1, 2.30) << endl;
	}

	Node* add(Node* cur, double time, int val) {
		if (!cur) return new Node(time, val);
		if (time < cur->time) {
			cur->leftSum += val;
			cur->left = add(cur->left, time, val);
		}
		else cur->right = add(cur->right, time, val);

		return cur;
	}

	int findOrders(double start, double end) {
		int startVal = lessThan(start);
		int endVal = equalTo(end);

		return endVal - startVal;
	}

	int lessThan(double start) {
		return lessThan(root, start);
	}

	int lessThan(Node* cur, double start) {
		if (!cur) return 0;
		if (start < cur->time) return lessThan(cur->left, start);
		else if (start > cur->time) return cur->val + lessThan(cur->right, start);
		else return cur->leftSum;
	}

	int equalTo(double start) {
		return equalTo(root, start);
	}

	int equalTo(Node* cur, double start) {
		if (!cur) return 0;
		if (start < cur->time) return equalTo(cur->left, start);
		else if (start > cur->time) return cur->val + equalTo(cur->right, start);
		else return cur->val + cur->leftSum;
	}

	void add1(double time, int val) {
		nodes.push_back(Node1(time, val));
		int sz = nodes.size();
		if (sz > 1) {
			nodes[sz - 1].leftSum += nodes[sz - 2].leftSum + nodes[sz - 2].val;
		}
	}
	int findOrders1(double start, double end) {
		int index1 = bsearch(nodes, 0, nodes.size() - 1, start);
		int index2 = bsearch(nodes, 0, nodes.size() - 1, end);
		int leftVal = nodes[index1].time != start ? (!index1 ? 0 : nodes[index1 - 1].val) : nodes[index1].leftSum;
		int rightVal = nodes[index2].time != end ? nodes[index2].leftSum : (nodes[index2].leftSum + nodes[index2].val);
		return rightVal - leftVal;
	}

	int bsearch(vector<Node1> nodes, int l, int r, double time) {
		if (l <= r) {
			int m = (l + r) / 2;
			if (time < nodes[m].time) return bsearch(nodes, l, m - 1, time);
			else if (time > nodes[m].time) return bsearch(nodes, m + 1, r, time);
			else return m;
		}
		return l;
	}
};