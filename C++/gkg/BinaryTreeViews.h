#pragma once
#include "../header.h"

class BinaryTreeViews {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        BinaryTreeViews obj;
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->right = new Node(4);
        root->left->right->right = new Node(5);
        root->left->right->right->right = new Node(6);

        cout << "Left View:" << endl;
        obj.printLeftViewRecursive(root);
        obj.printLeftViewUsingLevelOrder(root);
        cout << endl;

        cout << "Right View:" << endl;
        obj.printRightViewRecursive(root);
        obj.printRightViewUsingLevelOrder(root);
        cout << endl;

        cout << "Bottom View:" << endl;
        obj.printBottomViewRecursive(root);
        obj.printBottomViewIterative(root);
        cout << endl;

        cout << "Top View:" << endl;
        obj.printTopViewRecursive(root);
        obj.printTopViewIterative(root);
        cout << endl;

        cout << "Vertical View:" << endl;
        obj.printVerticalRecursive(root);
        obj.printVerticalIterative(root);
        cout << endl;

        cout << "Boundary View:" << endl;
        obj.printBoundaryViewIterative(root);
        obj.printBoundaryViewRecursive(root);

        cout << endl;
    }

   private:
    void printLeftViewRecursive(Node* node) {
        int mxLevel = -1;
        printLeftViewRecursive(node, 0, mxLevel);
    }
    void printLeftViewRecursive(Node* node, int curLevel, int& maxLevelSeenSoFar) {
        if (!node) return;
        if (maxLevelSeenSoFar < curLevel) {
            cout << node->val << " ";
            maxLevelSeenSoFar = curLevel;
        }

        printLeftViewRecursive(node->left, curLevel + 1, maxLevelSeenSoFar);
        printLeftViewRecursive(node->right, curLevel + 1, maxLevelSeenSoFar);
    }

   private:
    void printLeftViewUsingLevelOrder(Node* root) {
        queue<Node*> q;
        q.push(root);

        vector<int> result;
        while (!q.empty()) {
            auto sz = q.size();

            result.push_back(q.front()->val);

            while (sz--) {
                auto front = q.front();
                q.pop();

                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }
        }

        cout << result << endl;
    }

   private:
    void printRightViewRecursive(Node* node) {
        int mxLevel = -1;
        printRightViewRecursive(node, 0, mxLevel);
    }
    void printRightViewRecursive(Node* node, int curLevel, int& maxLevelSeenSoFar) {
        if (!node) return;
        if (maxLevelSeenSoFar < curLevel) {
            cout << node->val << " ";
            maxLevelSeenSoFar = curLevel;
        }
        printRightViewRecursive(node->right, curLevel + 1, maxLevelSeenSoFar);
        printRightViewRecursive(node->left, curLevel + 1, maxLevelSeenSoFar);
    }

   private:
    void printRightViewUsingLevelOrder(Node* root) {
        queue<Node*> q;
        q.push(root);

        vector<int> result;
        while (!q.empty()) {
            auto sz = q.size();

            for (int i = 0; i < sz; i++) {
                auto front = q.front();
                q.pop();

                if (i == sz - 1) {
                    result.push_back(front->val);
                }

                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }
        }

        cout << result << endl;
    }

   private:
    void printBottomViewRecursive(Node* node) {
        unordered_map<int, pair<int, Node*>> nodeMap;
        printBottomViewRecursive(node, 0, 0, nodeMap);
        print(nodeMap);
    }
    void printBottomViewRecursive(Node* node, int hd, int vd,
                                  unordered_map<int, pair<int, Node*>>& nodeMap) {
        if (!node) return;
        if (nodeMap.find(hd) == nodeMap.end() || vd > nodeMap[hd].first) nodeMap[hd] = {vd, node};

        printBottomViewRecursive(node->left, hd - 1, vd + 1, nodeMap);
        printBottomViewRecursive(node->right, hd + 1, vd + 1, nodeMap);
    }

   private:
    void printBottomViewIterative(Node* root) {
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        map<int, int> result;

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            result[cur.second] = cur.first->val;

            if (cur.first->left)
                q.push({cur.first->left, cur.second - 1});
            if (cur.first->right)
                q.push({cur.first->right, cur.second + 1});
        }

        cout << "Bottom view: ";
        for (auto& e : result)
            cout << e.second << ", ";
        cout << endl;
    }

   private:
    void printTopViewRecursive(Node* node) {
        unordered_map<int, pair<int, Node*>> nodeMap;
        printTopViewRecursive(node, 0, 0, nodeMap);
        print(nodeMap);
    }
    void printTopViewRecursive(Node* node, int hd, int vd,
                               unordered_map<int, pair<int, Node*>>& nodeMap) {
        if (!node) return;
        if (nodeMap.find(hd) == nodeMap.end() || vd < nodeMap[hd].first) nodeMap[hd] = {vd, node};

        printTopViewRecursive(node->left, hd - 1, vd + 1, nodeMap);
        printTopViewRecursive(node->right, hd + 1, vd + 1, nodeMap);
    }

   private:
    void printTopViewIterative(Node* root) {
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        map<int, int> result;

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            if (result.find(cur.second) == result.end()) result[cur.second] = cur.first->val;

            if (cur.first->left) q.push({cur.first->left, cur.second - 1});
            if (cur.first->right) q.push({cur.first->right, cur.second + 1});
        }

        cout << "Top view: ";
        for (auto& e : result) cout << e.second << ", ";
        cout << endl;
    }

   private:
    void printVerticalRecursive(Node* node) {
        unordered_map<int, vector<Node*>> nodeMap;
        printVerticalRecursive(node, 0, nodeMap);
        print(nodeMap);
    }
    void printVerticalRecursive(Node* node, int hd, unordered_map<int, vector<Node*>>& nodeMap) {
        if (!node) return;

        nodeMap[hd].push_back(node);
        printVerticalRecursive(node->left, hd - 1, nodeMap);
        printVerticalRecursive(node->right, hd + 1, nodeMap);
    }

   private:
    void printVerticalIterative(Node* root) {
        if (root == nullptr) {
            return;
        }

        map<int, vector<int>> verticalOrder;
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            Node* node = p.first;
            int hd = p.second;  // horizontal distance

            verticalOrder[hd].push_back(node->val);

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        // Print the vertical order traversal
        for (auto it : verticalOrder) {
            for (int val : it.second) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

   private:
    void printBoundaryViewIterative(Node* root) {
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        map<int, int> bottomView;
        vector<int> leftView;
        vector<int> rightView;

        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto cur = q.front();
                q.pop();

                if (i == 0) leftView.push_back(cur.first->val);
                if (i == n - 1) rightView.push_back(cur.first->val);
                bottomView[cur.second] = cur.first->val;

                if (cur.first->left) q.push({cur.first->left, cur.second - 1});
                if (cur.first->right) q.push({cur.first->right, cur.second + 1});
            }
        }

        vector<int> result;

        result.insert(result.end(), leftView.begin(), leftView.end());
        result.pop_back();

        for (auto& e : bottomView) result.push_back(e.second);
        result.pop_back();

        result.insert(result.end(), rightView.rbegin(), rightView.rend());
        result.pop_back();

        cout << "Boundary View: " << result << endl;
    }

   private:
    void printBoundaryViewRecursive(Node* root) {
        vector<int> result = getBoundaryViewRecursive(root);
        cout << result << endl;
    }
    vector<int> getBoundaryViewRecursive(Node* root) {
        vector<int> result;
        if (!root) return result;

        result.push_back(root->val);

        this->printLeftBoundary(root->left, result);
        this->printBottomBoundary(root, result);
        this->printRightBoundary(root->right, result);

        return result;
    }

    void printLeftBoundary(Node* root, vector<int>& result) {
        if (!root) return;
        if (!root->left && !root->right) return;

        result.push_back(root->val);

        if (root->left)
            printLeftBoundary(root->left, result);
        else if (root->right)
            printLeftBoundary(root->right, result);
    }

    void printRightBoundary(Node* root, vector<int>& result) {
        if (!root) return;
        if (!root->left && !root->right) return;

        if (root->right)
            printRightBoundary(root->right, result);
        else if (root->left)
            printRightBoundary(root->left, result);

        result.push_back(root->val);
    }

    void printBottomBoundary(Node* root, vector<int>& result) {
        if (!root) return;

        if (!root->left && !root->right) result.push_back(root->val);

        printBottomBoundary(root->left, result);
        printBottomBoundary(root->right, result);
    }

   private:
    void print(unordered_map<int, pair<int, Node*>> nodeMap) {
        vector<pair<int, int>> v;
        for (auto& e : nodeMap) v.push_back({e.first, e.second.second->val});
        sort(v.begin(), v.end(), [](auto f, auto s) { return (f.first < s.second); });
        for (auto& e : v) cout << e.second << " ";
        cout << endl;
    }

    void print(unordered_map<int, vector<Node*>>& nodeMap) {
        vector<pair<int, int>> v;
        for (auto& e : nodeMap) {
            for (auto& s : e.second) {
                v.push_back({e.first, s->val});
            }
        }
        sort(v.begin(), v.end(), [](const auto& f, const auto& s) { return (f.first <= s.second); });
        for (auto& e : v) cout << e.second << " ";
        cout << endl;
    }
};