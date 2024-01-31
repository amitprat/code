#pragma once
#include "../Header.h"

class BinaryTreeViews {
   public:
    static void test() {
        BinaryTreeViews obj;
        Tree::Node* root = new Tree::Node(1);
        root->left = new Tree::Node(2);
        root->right = new Tree::Node(3);
        root->left->right = new Tree::Node(4);
        root->left->right->right = new Tree::Node(5);
        root->left->right->right->right = new Tree::Node(6);

        cout << "Left View:" << endl;
        obj.printLeftView(root);
        cout << endl;

        cout << "Right View:" << endl;
        obj.printRightView(root);
        cout << endl;

        cout << "Bottom View:" << endl;
        obj.printBottomView(root);
        cout << endl;

        cout << "Top View:" << endl;
        obj.printTopView(root);
        cout << endl;

        cout << "Vertical View:" << endl;
        obj.printVertical(root);
        cout << endl;
    }

   private:
    void printLeftView(Tree::Node* node) {
        int mxLevel = -1;
        printLeftView(node, 0, mxLevel);
    }
    void printLeftView(Tree::Node* node, int curLevel, int& maxLevelSeenSoFar) {
        if (!node) return;
        if (maxLevelSeenSoFar < curLevel) {
            cout << node->val << " ";
            maxLevelSeenSoFar = curLevel;
        }
        printLeftView(node->left, curLevel + 1, maxLevelSeenSoFar);
        printLeftView(node->right, curLevel + 1, maxLevelSeenSoFar);
    }

   private:
    void printRightView(Tree::Node* node) {
        int mxLevel = -1;
        printRightView(node, 0, mxLevel);
    }
    void printRightView(Tree::Node* node, int curLevel, int& maxLevelSeenSoFar) {
        if (!node) return;
        if (maxLevelSeenSoFar < curLevel) {
            cout << node->val << " ";
            maxLevelSeenSoFar = curLevel;
        }
        printRightView(node->right, curLevel + 1, maxLevelSeenSoFar);
        printRightView(node->left, curLevel + 1, maxLevelSeenSoFar);
    }

   private:
    void printBottomView(Tree::Node* node) {
        unordered_map<int, pair<int, Tree::Node*>> nodeMap;
        printBottomView(node, 0, 0, nodeMap);
        print(nodeMap);
    }
    void printBottomView(Tree::Node* node, int hd, int vd,
                         unordered_map<int, pair<int, Tree::Node*>>& nodeMap) {
        if (!node) return;
        if (nodeMap.find(hd) == nodeMap.end() || vd > nodeMap[hd].first) nodeMap[hd] = {vd, node};

        printBottomView(node->left, hd - 1, vd + 1, nodeMap);
        printBottomView(node->right, hd + 1, vd + 1, nodeMap);
    }

   private:
    void printTopView(Tree::Node* node) {
        unordered_map<int, pair<int, Tree::Node*>> nodeMap;
        printTopView(node, 0, 0, nodeMap);
        print(nodeMap);
    }
    void printTopView(Tree::Node* node, int hd, int vd,
                      unordered_map<int, pair<int, Tree::Node*>>& nodeMap) {
        if (!node) return;
        if (nodeMap.find(hd) == nodeMap.end() || vd < nodeMap[hd].first) nodeMap[hd] = {vd, node};
        printTopView(node->left, hd - 1, vd + 1, nodeMap);
        printTopView(node->right, hd + 1, vd + 1, nodeMap);
    }

   private:
    void printVertical(Tree::Node* node) {
        unordered_map<int, vector<Tree::Node*>> nodeMap;
        printVertical(node, 0, nodeMap);
        print(nodeMap);
    }
    void printVertical(Tree::Node* node, int hd, unordered_map<int, vector<Tree::Node*>>& nodeMap) {
        if (!node) return;
        nodeMap[hd].push_back(node);
        printVertical(node->left, hd - 1, nodeMap);
        printVertical(node->right, hd + 1, nodeMap);
    }

   private:
    void print(unordered_map<int, pair<int, Tree::Node*>> nodeMap) {
        vector<pair<int, int>> v;
        for (auto& e : nodeMap) v.push_back({e.first, e.second.second->val});
        sort(v.begin(), v.end(), [](auto f, auto s) { return (f.first < s.second); });
        for (auto& e : v) cout << e.second << " ";
        cout << endl;
    }

    void print(unordered_map<int, vector<Tree::Node*>>& nodeMap) {
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