#pragma once
#include "../Header.h"

class BinaryTreeViews {
   public:
    static void test() {
        BinaryTreeViews obj;
        BinaryTreeNode<int>* root = new BinaryTreeNode<int>(1);
        root->left = new BinaryTreeNode<int>(2);
        root->right = new BinaryTreeNode<int>(3);
        root->left->right = new BinaryTreeNode<int>(4);
        root->left->right->right = new BinaryTreeNode<int>(5);
        root->left->right->right->right = new BinaryTreeNode<int>(6);

        cout << to_string(root) << endl;

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
    void printLeftView(BinaryTreeNode<int>* node) {
        int mxLevel = -1;
        printLeftView(node, 0, mxLevel);
    }
    void printLeftView(BinaryTreeNode<int>* node, int curLevel, int& maxLevelSeenSoFar) {
        if (!node) return;
        if (maxLevelSeenSoFar < curLevel) {
            cout << node->val << " ";
            maxLevelSeenSoFar = curLevel;
        }
        printLeftView(node->left, curLevel + 1, maxLevelSeenSoFar);
        printLeftView(node->right, curLevel + 1, maxLevelSeenSoFar);
    }

   private:
    void printRightView(BinaryTreeNode<int>* node) {
        int mxLevel = -1;
        printRightView(node, 0, mxLevel);
    }
    void printRightView(BinaryTreeNode<int>* node, int curLevel, int& maxLevelSeenSoFar) {
        if (!node) return;
        if (maxLevelSeenSoFar < curLevel) {
            cout << node->val << " ";
            maxLevelSeenSoFar = curLevel;
        }
        printRightView(node->right, curLevel + 1, maxLevelSeenSoFar);
        printRightView(node->left, curLevel + 1, maxLevelSeenSoFar);
    }

   private:
    void printBottomView(BinaryTreeNode<int>* node) {
        unordered_map<int, pair<int, BinaryTreeNode<int>*>> nodeMap;
        printBottomView(node, 0, 0, nodeMap);
        print(nodeMap);
    }
    void printBottomView(BinaryTreeNode<int>* node, int hd, int vd,
                         unordered_map<int, pair<int, BinaryTreeNode<int>*>>& nodeMap) {
        if (!node) return;
        if (nodeMap.find(hd) == nodeMap.end() || vd > nodeMap[hd].first) nodeMap[hd] = {vd, node};

        printBottomView(node->left, hd - 1, vd + 1, nodeMap);
        printBottomView(node->right, hd + 1, vd + 1, nodeMap);
    }

   private:
    void printTopView(BinaryTreeNode<int>* node) {
        unordered_map<int, pair<int, BinaryTreeNode<int>*>> nodeMap;
        printTopView(node, 0, 0, nodeMap);
        print(nodeMap);
    }
    void printTopView(BinaryTreeNode<int>* node, int hd, int vd,
                      unordered_map<int, pair<int, BinaryTreeNode<int>*>>& nodeMap) {
        if (!node) return;
        if (nodeMap.find(hd) == nodeMap.end() || vd < nodeMap[hd].first) nodeMap[hd] = {vd, node};
        printTopView(node->left, hd - 1, vd + 1, nodeMap);
        printTopView(node->right, hd + 1, vd + 1, nodeMap);
    }

   private:
    void printVertical(BinaryTreeNode<int>* node) {
        unordered_map<int, vector<BinaryTreeNode<int>*>> nodeMap;
        printVertical(node, 0, nodeMap);
        print(nodeMap);
    }
    void printVertical(BinaryTreeNode<int>* node, int hd, unordered_map<int, vector<BinaryTreeNode<int>*>>& nodeMap) {
        if (!node) return;
        nodeMap[hd].push_back(node);
        printVertical(node->left, hd - 1, nodeMap);
        printVertical(node->right, hd + 1, nodeMap);
    }

   private:
    void print(unordered_map<int, pair<int, BinaryTreeNode<int>*>> nodeMap) {
        vector<pair<int, int>> v;
        for (auto& e : nodeMap) v.push_back({e.first, e.second.second->val});
        sort(v.begin(), v.end(), [](auto f, auto s) { return (f.first < s.second); });
        for (auto& e : v) cout << e.second << " ";
        cout << endl;
    }

    void print(unordered_map<int, vector<BinaryTreeNode<int>*>>& nodeMap) {
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