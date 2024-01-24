#pragma once
#include "../Header.h"

class TreeTraversal {
public:
    static void test() {
        ITNode* root = new ITNode(1);
        root->left = new ITNode(2);
        root->right = new ITNode(3);
        root->left->left = new ITNode(4);
        root->left->right = new ITNode(5);
        root->right->left = new ITNode(6);
        root->right->right = new ITNode(7);
        root->right->left->right = new ITNode(8);
        root->right->right->right = new ITNode(9);
        root->right->right->left = new ITNode(10);
        root->right->right->left->right = new ITNode(11);
        root->right->right->left->right->right = new ITNode(12);

        printVerticalOrder(root);
        printVerticalOrderReverse(root);
        printVerticalOrderUsingLevelOrder(root);
        printTopView(root);
        printBottomView(root);
        printLeftView(root);
        printRightView(root);
        printBoundary(root);
    }

    static void printBoundary(ITNode* root) {
        cout << "\nBoundary Traversal" << endl;

        cout << root->val << " ";
        printBoundaryLeft(root->left);

        printLeaves(root->left);
        printLeaves(root->right);

        printBoundaryRight(root->right);

        cout << endl;
    }

    static void printBoundaryLeft(ITNode* root) {
        if (!root) return;

        if (root->left) {
            cout << root->val << " ";
            printBoundaryLeft(root->left);
        }
        else if (root->right) {
            cout << root->val << " ";
            printBoundaryLeft(root->right);
        }
    }

    static void printBoundaryRight(ITNode* root) {
        if (!root) return;

        if (root->right) {
            printBoundaryRight(root->right);
            cout << root->val << " ";
        }
        else if (root->right) {
            printBoundaryRight(root->left);
            cout << root->val << " ";
        }
    }

    static void printLeaves(ITNode* root) {
        if (!root) return;

        printLeaves(root->left);

        if (!root->left && !root->right) {
            cout << root->val << " ";
        }

        printLeaves(root->right);
    }

    static void printReverseRightView(ITNode* root) {
        int mxLevel = 0;
        printReverseRightView(root, 0, 0, mxLevel);
    }

    static void printReverseRightView(ITNode* root, int level, int hd, int& mxLevel) {
        if (!root) return;

        printReverseRightView(root->right, level - 1, hd + 1, mxLevel);
        printReverseRightView(root->left, level - 1, hd - 1, mxLevel);

        if (level > mxLevel) {
            cout << root->val << " ";
            mxLevel = level;
        }
    }

    static void printRightView(ITNode* root) {
        cout << "\nRight View: " << endl;

        int maxLevel = -1;
        printRightView(root, 0, maxLevel);
        cout << endl;
    }

    static void printRightView(ITNode* root, int level, int& maxLevel) {
        if (!root) return;
        if (level > maxLevel) {
            cout << root->val << " ";
            maxLevel = level;
        }

        printRightView(root->right, level + 1, maxLevel);
        printRightView(root->left, level + 1, maxLevel);
    }

    static void printLeftView(ITNode* root) {
        cout << "\nLeft View: " << endl;

        int maxLevel = -1;
        printLeftView(root, 0, maxLevel);
        cout << endl;
    }

    static void printLeftView(ITNode* root, int level, int& maxLevel) {
        if (!root) return;
        if (level > maxLevel) {
            cout << root->val << " ";
            maxLevel = level;
        }

        printLeftView(root->left, level + 1, maxLevel);
        printLeftView(root->right, level + 1, maxLevel);
    }

    static void printBottomView(ITNode* root) {
        map<int, pair<int, ITNode*>> map;
        cout << "\nBottom View: " << endl;
        printBottomView(root, map, 0, 0);

        for (auto& e : map) {
            auto& val = e.second;
            cout << e.first << ":" << e.second.second->val;
            cout << endl;
        }
    }

    static void printBottomView(ITNode* root, map<int, pair<int, ITNode*>>& map, int hd, int level) {
        if (!root) return;

        if (map.find(hd) == map.end() || (map.find(hd) != map.end() && level > map[hd].first)) {
            map[hd] = { level, root };
        }
        printBottomView(root->left, map, hd - 1, level + 1);
        printBottomView(root->right, map, hd + 1, level + 1);
    }

    static void printTopView(ITNode* root) {
        map<int, pair<int, ITNode*>> map;

        cout << "\nTop View: " << endl;
        printTopView(root, map, 0, 0);

        for (auto& e : map) {
            auto& val = e.second;
            cout << e.first << ":" << e.second.second->val;
            cout << endl;
        }
    }

    static void printTopView(ITNode* root, map<int, pair<int, ITNode*>>& map, int hd, int level) {
        if (!root) return;

        if (map.find(hd) == map.end() || (map.find(hd) != map.end() && level < map[hd].first)) {
            map[hd] = { level, root };
        }
        printTopView(root->left, map, hd - 1, level + 1);
        printTopView(root->right, map, hd + 1, level + 1);
    }

    static void printVerticalOrderUsingLevelOrder(ITNode* root) {
        cout << "\nVertical Order using Level Order: " << endl;
        queue<pair<int, ITNode*>> q;
        map<int, vector<ITNode*>> map;
        q.push({ 0, root });

        while (!q.empty()) {
            auto f = q.front(); q.pop();

            map[f.first].push_back(f.second);

            if (f.second->left) q.push({ f.first - 1,f.second->left });
            if (f.second->right) q.push({ f.first + 1,f.second->right });
        }

        for (auto& e : map) {
            auto& val = e.second;
            cout << e.first << ": ";
            for (auto& v : val) {
                cout << v->val << " ";
            }
            cout << endl;
        }
    }

    static void printVerticalOrder(ITNode* root) {
        cout << "\nVertical Order using Stack: " << endl;
        map<int, vector<pair<int, ITNode*>>> map;
        printVerticalOrder(root, map, 0, 0);

        for (auto& e : map) {
            auto& val = e.second;
            sort(val.begin(), val.end(), [](const auto& f, const auto& s) {return f.first < s.first; });

            cout << e.first << ": ";
            for (auto& v : val) {
                cout << v.second->val << " ";
            }
            cout << endl;
        }
    }

    static void printVerticalOrderReverse(ITNode* root) {
        cout << "\nVertical Reverse Order using Stack: " << endl;
        map<int, vector<pair<int, ITNode*>>> map;
        printVerticalOrder(root, map, 0, 0);

        for (auto& e : map) {
            auto& val = e.second;
            sort(val.begin(), val.end(), [](const auto& f, const auto& s) {return f.first > s.first; });

            cout << e.first << ": ";
            for (auto& v : val) {
                cout << v.second->val << " ";
            }
            cout << endl;
        }
    }

    static void printVerticalOrder(ITNode* root, map<int, vector<pair<int, ITNode*>>>& map, int hd, int level) {
        if (!root) return;

        map[hd].push_back({ level, root });

        printVerticalOrder(root->left, map, hd - 1, level + 1);
        printVerticalOrder(root->right, map, hd + 1, level + 1);
    }
};