#pragma once
#include "../Header.h"

class KthSmallestElementInBst {
    class BST {
    public:
        struct Node {
            int val;
            int sz = 0;
            Node* left, * right;
            Node(int val) :val(val), left(nullptr), right(nullptr), sz(1) {}
        };

    private:
        Node* root = nullptr;

    public:
        void insert(int val) {
            root = insert(root, val);
        }

        int kthSmallestElem(int k) {
            return kthSmallestElem(root, k);
        }

        void remove(int val) {
            root = remove(root, val);
        }

    private:
        Node* insert(Node* cur, int val) {
            if (!cur) return new Node(val);

            cur->sz++;

            if (val < cur->val) cur->left = insert(cur->left, val);
            else if (val > cur->val) cur->right = insert(cur->right, val);

            return cur;
        }

        int kthSmallestElem(Node* cur, int k) {
            if (!cur) return INT_MAX;

            int sz = size(cur->left) + 1;
            if (sz == k) return cur->val;

            if (k < sz) return kthSmallestElem(cur->left, k);
            else return kthSmallestElem(cur->right, k - sz);
        }

        int size(Node* cur) {
            if (!cur) return 0;

            return cur->sz;
        }

        Node* remove(Node* cur, int val) {
            if (!cur) return cur;

            if (val < cur->val) {
                cur->sz--;
                cur->left = remove(cur->left, val);
            }
            else if (val > cur->val) {
                cur->sz--;
                cur->right = remove(cur->right, val);
            }
            else {
                if (!cur->left || !cur->right) {
                    if (!cur->left) {
                        auto r = cur->right;
                        delete cur;
                        cur = r;
                    }
                    else if (!cur->right) {
                        auto l = cur->left;
                        delete cur;
                        cur = l;
                    }
                }
                else {
                    Node* suc = succ(cur->right);
                    cur->val = suc->val;
                    cur->right = remove(cur->right, suc->val);
                    cur->sz--;
                }
            }

            return cur;
        }

        Node* succ(Node* cur) {
            while (cur && cur->left) {
                cur = cur->left;
            }
            return cur;
        }
    public:
        Node* getNode() {
            return root;
        }
    };

    class BstIterator {
        BST::Node* root = nullptr;
        stack<BST::Node*> st;
        BST::Node* cur = nullptr;
    public:
        BstIterator(BST::Node* root) : root(root) {
        }

        bool hasNext() {
            return !st.empty() || root != nullptr;
        }

        BST::Node* next() {
            if (st.empty() && root == nullptr) return nullptr;

            while (root) {
                st.push(root);
                root = root->left;
            }

            root = st.top(); st.pop();

            auto cur = root;
            root = root->right;

            return cur;
        }
    };

    class DLL {
        LinkedListNode<int>* head = nullptr;
        LinkedListNode<int>* tail = nullptr;
        int sz = 0;

    public:
        void insert(int val) {
            if (!head) head = tail = new LinkedListNode<int>(val);
            else {
                auto newNode = new LinkedListNode<int>(val);
                newNode->prev = tail;
                tail->next = newNode;

                tail = tail->next;
            }
            sz++;
        }

        LinkedListNode<int>* getRoot() {
            return head;
        }

        vector<int> values() {
            vector<int> result;
            auto* tmp = head;
            while (tmp) {
                result.push_back(tmp->val);
                tmp = tmp->next;
            }

            return result;
        }

        int size() {
            return sz;
        }
    };
public:
    static void test() {
        KthSmallestElementInBst obj;
        BST bst;
        vector<int> keys = { 20, 8, 22, 4, 12, 10, 14 };
        for (auto v : keys) bst.insert(v);

        BstIterator iter(bst.getNode());
        while (iter.hasNext()) {
            cout << iter.next()->val << " ";
        }
        cout << endl;

        bst.remove(20);
        bst.remove(12);
        bst.remove(14);

        iter = BstIterator(bst.getNode());
        while (iter.hasNext()) {
            cout << iter.next()->val << " ";
        }
        cout << endl;

        for (int i = 0; i < keys.size(); i++) {
            cout << i + 1 << "th smallest element = " << bst.kthSmallestElem(i + 1) << endl;
        }

        BST bst2;
        vector<int> keys2 = { 2, 8, 4, 6, 8, 10, 12 };
        for (auto v : keys) bst2.insert(v);
        BstIterator iter2(bst2.getNode());
        while (iter2.hasNext()) {
            cout << iter2.next()->val << " ";
        }
        cout << endl;

        auto res = obj.merge(bst.getNode(), bst2.getNode());
        cout << to_string(res) << endl;

        for (int i = 0; i < 30; i++) {
            cout << "Floor of " << i << " = " << obj.floor(bst2.getNode(), i) << endl;
            cout << "Ceil of " << i << " = " << obj.ceil(bst2.getNode(), i) << endl;
        }

        DLL dll;
        for (int i = 1; i <= 7; i++) dll.insert(i);
        cout << "DLL = " << to_string(dll.values()) << endl;

        auto* root = dll.getRoot();
        auto* converted = obj.convert(root, dll.size());
        obj.inorder(converted);
        cout << endl;
    }

    int floor(BST::Node* node, int val) {
        if (!node) return INT_MIN;

        if (val <= node->val) return floor(node->left, val);

        int f = floor(node->right, val);
        if (f == INT_MIN) return node->val;

        return f;
    }

    int ceil(BST::Node* node, int val) {
        if (!node) return INT_MAX;

        if (val >= node->val) return ceil(node->right, val);

        int c = ceil(node->left, val);
        if (c == INT_MAX) return node->val;

        return c;
    }

    vector<int> merge(BST::Node* cur1, BST::Node* cur2) {
        vector<int> res;
        stack<BST::Node*> st1, st2;
        bool process1 = true, process2 = true;

        while (true) {
            cur1 = move(st1, cur1, process1);
            process1 = false;

            cur2 = move(st2, cur2, process2);
            process2 = false;
            if (!cur1 && !cur2) break;

            if (!cur2 || (cur1 && cur1->val <= cur2->val)) {
                res.push_back(cur1->val);
                process1 = true;
                cur1 = cur1->right;
            }
            else {
                res.push_back(cur2->val);
                process2 = true;
                cur2 = cur2->right;
            }
        }

        return res;
    }

    BST::Node* move(stack<BST::Node*>& st, BST::Node*& cur, bool process) {
        if (!process) return cur;
        if (!cur && st.empty()) return cur;

        while (cur) {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top(); st.pop();

        return cur;
    }

    LinkedListNode<int>* convert(LinkedListNode<int>*& head, int n) {
        if (n <= 0) return nullptr;

        auto* left = convert(head, n / 2);
        auto root = head;
        head = head->next;

        root->prev = left;

        root->next = convert(head, n - n / 2 - 1);

        return root;
    }

    void inorder(LinkedListNode<int>* head) {
        if (!head) return;

        inorder(head->prev);
        cout << head->val << " ";
        inorder(head->next);
    }
};