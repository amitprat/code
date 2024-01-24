#include "../header.h"

class BoundaryTraversal {
    struct Node {
        int val;
        Node *left, *right;
        Node(int val) : val(val), left(nullptr), right(nullptr) {}
    };

   public:
    static void test() {
        /*
                       20
                8            22
            4      12   10         25
                11            21
        */
        Node *root = new Node(20);

        root->left = new Node(8);
        root->right = new Node(22);

        root->left->left = new Node(4);
        root->left->right = new Node(12);
        root->left->right->left = new Node(11);

        root->right->left = new Node(10);
        root->right->right = new Node(25);
        root->right->right->left = new Node(21);

        BoundaryTraversal obj;
        // obj.boundaryTraversal(root);

        cout << "Printing left views: " << endl;
        obj.leftMostNodesIterative(root);
        obj.leftMostNodesRecursive(root);
        cout << endl;

        cout << "Printing right views: " << endl;
        obj.rightMostNodesIterative(root);
        obj.rightMostNodesRecursive(root);
        cout << endl;

        cout << "Printing top views: " << endl;
        obj.topViewIterative(root);
        obj.topViewRecursive(root);
        cout << endl;

        cout << "Printing bottom views: " << endl;
        obj.bottomViewIterative(root);
        obj.bottomViewRecursive(root);
        cout << endl;

        cout << "Printing boundary views: " << endl;
        obj.boundaryViewIterative(root);
        obj.boundaryViewRecursive(root);
        cout << endl;

        cout << "Boundary view: " << endl;
        auto result = obj.boundaryView(root);
        cout << result << endl;
    }

   private:
    void leftMostNodesIterative(Node *root) {
        queue<Node *> q;
        q.push(root);

        vector<int> result;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto node = q.front();
                q.pop();

                if (i == 0)
                    result.push_back(node->val);

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }

        cout << "Left View: " << result << endl;
    }

    void leftMostNodesRecursive(Node *root) {
        int maxLevel = -1;
        vector<int> result;
        this->leftMostNodesRecursive(root, 0, maxLevel, result);

        cout << "Left View: " << result << endl;
    }

    void leftMostNodesRecursive(Node *root, int level, int &maxLevel, vector<int> &result) {
        if (!root)
            return;
        if (level > maxLevel) {
            result.push_back(root->val);
            maxLevel = level;
        }

        leftMostNodesRecursive(root->left, level + 1, maxLevel, result);
        leftMostNodesRecursive(root->right, level + 1, maxLevel, result);
    }

   private:
    void rightMostNodesRecursive(Node *root) {
        int maxLevel = -1;
        vector<int> result;

        this->rightMostNodesRecursive(root, 0, maxLevel, result);
        cout << "Right view: " << result << endl;
    }
    void rightMostNodesRecursive(Node *root, int level, int &maxLevel, vector<int> &result) {
        if (!root)
            return;
        if (level > maxLevel) {
            maxLevel = level;
            result.push_back(root->val);
        }

        rightMostNodesRecursive(root->right, level + 1, maxLevel, result);
        rightMostNodesRecursive(root->left, level + 1, maxLevel, result);
    }

    void rightMostNodesIterative(Node *root) {
        queue<Node *> q;
        q.push(root);

        vector<int> result;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto cur = q.front();
                q.pop();
                if (i == n - 1) {
                    result.push_back(cur->val);
                }

                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }

        cout << "Right view: " << result << endl;
    }

   private:
    void bottomViewRecursive(Node *root) {
        map<int, pair<int, int>> result;
        this->bottomViewRecursive(root, 0, 0, result);

        cout << "Bottom view: ";
        for (auto &e : result)
            cout << e.second.first << ", ";
        cout << endl;
    }
    void bottomViewRecursive(Node *root, int hd, int vd, map<int, pair<int, int>> &result) {
        if (!root)
            return;
        if (result.find(hd) == result.end() || result[hd].second < vd) {
            result[hd] = {root->val, vd};
        }

        bottomViewRecursive(root->left, hd - 1, vd + 1, result);
        bottomViewRecursive(root->right, hd + 1, vd + 1, result);
    }

    void bottomViewIterative(Node *root) {
        queue<pair<Node *, int>> q;
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
        for (auto &e : result)
            cout << e.second << ", ";
        cout << endl;
    }

   private:
    void topViewRecursive(Node *root) {
        map<int, pair<int, int>> result;
        this->topViewRecursive(root, 0, 0, result);

        cout << "Top view: ";
        for (auto &e : result)
            cout << e.second.first << ", ";
        cout << endl;
    }

    void topViewRecursive(Node *root, int hd, int vd, map<int, pair<int, int>> &result) {
        if (!root)
            return;
        if (result.find(hd) == result.end() || vd < result[hd].second) {
            result[hd] = {root->val, vd};
        }

        topViewRecursive(root->left, hd - 1, vd + 1, result);
        topViewRecursive(root->right, hd + 1, vd + 1, result);
    }

    void topViewIterative(Node *root) {
        queue<pair<Node *, int>> q;
        q.push({root, 0});
        map<int, int> result;

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            if (result.find(cur.second) == result.end()) {
                result[cur.second] = cur.first->val;
            }

            if (cur.first->left)
                q.push({cur.first->left, cur.second - 1});
            if (cur.first->right)
                q.push({cur.first->right, cur.second + 1});
        }

        cout << "Top view: ";
        for (auto &e : result)
            cout << e.second << ", ";
        cout << endl;
    }

   private:
    void boundaryViewRecursive(Node *root) {
        if (!root)
            return;

        vector<int> result;

        int maxLevel = 0;
        this->leftMostNodesRecursive(root, 0, maxLevel, result);
        result.pop_back();

        map<int, pair<int, int>> bottomView;
        this->bottomViewRecursive(root, 0, 0, bottomView);
        for (auto &e : bottomView)
            result.push_back(e.second.first);
        result.pop_back();

        maxLevel = 0;
        vector<int> rightView;
        if (root->right)
            this->rightMostNodesRecursive(root->right, 0, maxLevel, rightView);
        result.insert(result.end(), rightView.rbegin(), rightView.rend());
        result.pop_back();

        cout << "Boundary View: " << result << endl;
    }

    void boundaryViewIterative(Node *root) {
        queue<pair<Node *, int>> q;
        q.push({root, 0});

        map<int, int> bottomView;
        vector<int> leftView;
        vector<int> rightView;

        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto cur = q.front();
                q.pop();

                if (i == 0)
                    leftView.push_back(cur.first->val);
                if (i == n - 1)
                    rightView.push_back(cur.first->val);

                bottomView[cur.second] = cur.first->val;

                if (cur.first->left)
                    q.push({cur.first->left, cur.second - 1});
                if (cur.first->right)
                    q.push({cur.first->right, cur.second + 1});
            }
        }

        vector<int> result;
        result.insert(result.end(), leftView.begin(), leftView.end());
        result.pop_back();
        for (auto &e : bottomView)
            result.push_back(e.second);
        result.pop_back();
        result.insert(result.end(), rightView.rbegin(), rightView.rend());
        result.pop_back();

        cout << "Boundary View: " << result << endl;
    }

   private:
    void printLeftBoundary(Node *root, vector<int> &result) {
        if (!root)
            return;
        if (!root->left && !root->right)
            return;

        result.push_back(root->val);

        if (root->left)
            printLeftBoundary(root->left, result);
        else if (root->right)
            printLeftBoundary(root->right, result);
    }

    void printRightBoundary(Node *root, vector<int> &result) {
        if (!root)
            return;
        if (!root->left && !root->right)
            return;

        if (root->right)
            printRightBoundary(root->right, result);
        else if (root->left)
            printRightBoundary(root->left, result);

        result.push_back(root->val);
    }

    void printBoundary(Node *root, vector<int> &result) {
        if (!root)
            return;

        if (!root->left && !root->right)
            result.push_back(root->val);

        printBoundary(root->left, result);
        printBoundary(root->right, result);
    }

    vector<int> boundaryView(Node *root) {
        vector<int> result;
        if (!root)
            return result;

        result.push_back(root->val);

        this->printLeftBoundary(root->left, result);
        this->printBoundary(root, result);
        this->printRightBoundary(root->right, result);

        return result;
    }
};