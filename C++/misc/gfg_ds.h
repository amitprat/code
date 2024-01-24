#pragma once
#include "../header.h"

class SwapLinkedListNodes {
public:
    template <class T>
    class Node {
    public:
        T val;
        Node* next;

        Node(T val) : val(val), next(nullptr) {}
        string to_string() {
            return std::to_string(val);
        }
    };

    template <class T>
    class LinkedList {
    private:
        Node<int>* root = nullptr;
        int sz = 0;
    public:
        void add(int val) {
            if (root == nullptr) root = new Node<int>(val);
            else {
                auto cur = root;
                while (cur->next) cur = cur->next;
                cur->next = new Node<int>(val);
            }
            sz++;
        }
        void add(Node<T>* node) {
            if (root == nullptr) root = node;
            else {
                auto cur = root;
                while (cur->next) cur = cur->next;
                cur->next = node;
            }
            sz++;
        }

        bool empty() {
            return root == nullptr;
        }

        bool hasNext() {
            return root != nullptr && root->next != nullptr;
        }

        string to_string() {
            stringstream ss;
            auto cur = root;
            ss << "{";
            while (cur) {
                ss << cur->to_string();
                ss << " ";
                cur = cur->next;
            }
            ss << "}";

            return ss.str();
        }

        Node<T>* getPrev(Node<T>* node) {
            auto cur = root;
            while (cur != nullptr && cur->next != node) {
                cur = cur->next;
            }
            return cur;
        }

        Node<T>* getRoot() {
            return root;
        }

        void setRoot(Node<T>* node) {
            root = node;
        }

        int size()
        {
            return sz;
        }
    };

    template <class T>
    class TreeNode {
    public:
        T val;
        TreeNode<T>* left, * right;
        TreeNode(T val) : val(val), left(nullptr), right(nullptr) {}
    };
public:
    static void test() {
        SwapLinkedListNodes obj;
        LinkedList<int> ll;
        Node<int>* node1 = new Node<int>(1);
        Node<int>* node2 = new Node<int>(2);
        Node<int>* node3 = new Node<int>(3);
        Node<int>* node4 = new Node<int>(4);
        Node<int>* node5 = new Node<int>(5);
        ll.add(node4);
        ll.add(node5);
        ll.add(node1);
        ll.add(node2);
        ll.add(node3);

        cout << "LinkedList Before Swapping Nodes:";
        print(ll);

        obj.swapNodes(ll, node1, node3);

        cout << "LinkedList After Swapping Nodes:";
        print(ll);

        auto cur = ll.getRoot();
        cur = obj.reverseRecur(cur);
        ll.setRoot(cur);
        cout << "Reversed LinkedList: ";
        print(ll);

        obj.sort(ll);

        cout << "Sorted LinkedList: ";
        print(ll);

        // reverse in groups
        obj.reverseInGroup(ll, 3);
        cout << "ReverseGroups LinkedList: ";
        print(ll);

        // remove loop
        {
            LinkedList<int> faultyList;
            Node<int>* node1 = new Node<int>(1);
            Node<int>* node2 = new Node<int>(2);
            Node<int>* node3 = new Node<int>(3);
            Node<int>* node4 = new Node<int>(4);
            Node<int>* node5 = new Node<int>(5);
            faultyList.add(node4);
            faultyList.add(node5);
            faultyList.add(node1);
            faultyList.add(node2);
            faultyList.add(node3);
            faultyList.add(node5);
            obj.detectAndRemoveLoop(faultyList);

            cout << "corrected LinkedList: ";
            print(faultyList);
        }

        // add linkedlist
        {
            LinkedList<int> ll1;
            Node<int>* node1 = new Node<int>(9);
            Node<int>* node2 = new Node<int>(7);
            Node<int>* node3 = new Node<int>(8);
            ll1.add(node1);
            ll1.add(node2);
            ll1.add(node3);

            LinkedList<int> ll2;
            Node<int>* node4 = new Node<int>(8);
            Node<int>* node5 = new Node<int>(9);
            Node<int>* node6 = new Node<int>(9);
            ll2.add(node4);
            ll2.add(node5);
            ll2.add(node6);

            LinkedList<int> ll3 = obj.add(ll1, ll2);

            cout << "Sum of LinkedList: ";
            obj.reverseIter(ll3);
            print(ll3);
        }

        // flatten tree
        TreeNode<int>* treeRoot = new TreeNode<int>(1);
        treeRoot->left = new TreeNode<int>(2);
        treeRoot->right = new TreeNode<int>(5);
        treeRoot->left->left = new TreeNode<int>(3);
        treeRoot->right->right = new TreeNode<int>(6);
        treeRoot->left->right = new TreeNode<int>(4);
        treeRoot->right->right->left = new TreeNode<int>(7);

        auto head = obj.flatten(treeRoot);
        cout << "Flattened List:";
        print(head);
        cout << endl;
    }

    static void print(LinkedList<int> ll) {
        cout << ll.to_string() << endl;
    }
    static void print(TreeNode<int>* head) {
        while (head != nullptr) {
            cout << head->val << " ";
            head = head->right;
        }
    }
    void swapNodes(LinkedList<int>& ll, Node<int>* first, Node<int>* second) {
        if (first == nullptr || second == nullptr || ll.empty()) return;

        auto firstPrev = ll.getPrev(first);
        auto secondPrev = ll.getPrev(second);

        if (firstPrev == nullptr) ll.setRoot(second);
        else firstPrev->next = second;

        if (secondPrev == nullptr) ll.setRoot(first);
        else secondPrev->next = first;

        swap(first->next, second->next);
    }

    void reverseIter(LinkedList<int>& ll) {
        Node<int>* cur = ll.getRoot();
        Node<int>* prev = nullptr;

        while (cur != nullptr) {
            auto tmp = cur->next;
            cur->next = prev;

            prev = cur;
            cur = tmp;
        }

        ll.setRoot(prev);
    }

    Node<int>* reverseRecur(Node<int>* cur) {
        if (cur == nullptr || cur->next == nullptr) return cur;
        auto rest = reverseRecur(cur->next);

        cur->next->next = cur;
        cur->next = nullptr;

        return rest;
    }

    void sort(LinkedList<int>& ll) {
        auto cur = ll.getRoot();

        cur = mergeSort(cur, ll.size());

        ll.setRoot(cur);
    }

    void reverseInGroup(LinkedList<int>& ll, int k) {
        auto cur = ll.getRoot();
        cur = reverseInGroup(cur, k);
        ll.setRoot(cur);
    }

private:
    Node<int>* mergeSort(Node<int>* node, int sz) {
        if (sz <= 1) return node;
        Node<int>* second = split(node, sz / 2);
        auto left = mergeSort(node, sz / 2);
        auto right = mergeSort(second, sz - sz / 2);
        return sortedMerge(left, right);
    }

    Node<int>* split(Node<int>* node, int sz) {
        while (sz != 1) {
            node = node->next;
            sz--;
        }
        auto next = node->next;
        node->next = nullptr;
        return next;
    }

    Node<int>* sortedMerge(Node<int>* first, Node<int>* second) {
        if (first == nullptr) return second;
        if (second == nullptr) return first;
        Node<int>* dummy = new Node<int>(-1);
        Node<int>* dummyHead = dummy;
        while (first && second) {
            if (first->val < second->val) {
                dummy->next = first;
                first = first->next;
            }
            else {
                dummy->next = second;
                second = second->next;
            }
            dummy = dummy->next;
        }
        while (first) {
            dummy->next = first;
            first = first->next;
            dummy = dummy->next;
        }
        while (second) {
            dummy->next = second;
            second = second->next;
            dummy = dummy->next;
        }
        return dummyHead->next;
    }

    Node<int>* reverseInGroup(Node<int>* head, int k) {
        if (head == nullptr) return head;
        auto oldHead = head;
        Node<int>* next = nullptr;
        Node<int>* prev = nullptr;
        int tmp = k;
        while (head != nullptr && k != 0) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
            k--;
        }
        oldHead->next = reverseInGroup(next, tmp);

        return prev;
    }

    bool detectAndRemoveLoop(LinkedList<int>& ll) {
        auto head = ll.getRoot();
        auto node = detectLoop(head);
        if (node == nullptr) return false;
        auto res = removeLoop(head, node);
        return res;
    }

    Node<int>* detectLoop(Node<int>* head) {
        auto slow = head;
        auto fast = head;
        while (slow && fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                cout << "Found loop at node " << slow->val << endl;
                return slow;
            }
        }
        return nullptr;
    }

    bool removeLoop(Node<int>* head, Node<int>* node) {
        while (head && node && (head->next != node->next)) {
            head = head->next;
            node = node->next;
        }
        if (node != nullptr) {
            cout << "Removing link for node " << node->val << endl;
            node->next = nullptr;
            return true;
        }
        return false;
    }

    LinkedList<int> add(LinkedList<int> ll1, LinkedList<int> ll2) {
        auto root1 = ll1.getRoot();
        auto root2 = ll2.getRoot();

        auto s = add(root1, root2, 0);
        LinkedList<int> newll;
        newll.add(s);

        return newll;
    }

    Node<int>* add(Node<int>* node1, Node<int>* node2, int carry) {
        if (node1 == nullptr && node2 == nullptr) {
            if (carry > 0) return new Node<int>(carry);
            return nullptr;
        }
        int cur = carry;
        if (node1 != nullptr) cur += node1->val;
        if (node2 != nullptr) cur += node2->val;

        auto newnode = new Node<int>(cur % 10);
        newnode->next = add(node1 != nullptr ? node1->next : node1, node2 != nullptr ? node2->next : node2, cur / 10);

        return newnode;
    }

    TreeNode<int>* flatten(TreeNode<int>* node) {
        if (node) {
            auto prev = flatten(node->right);
            prev = flatten(node->left);

            node->right = prev;
            node->left = nullptr;

            prev = node;

            return prev;
        }
        return nullptr;
    }
};