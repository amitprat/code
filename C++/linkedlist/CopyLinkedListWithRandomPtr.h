#include "../header.h"

/*
https://careercup.com/question?id=5412018236424192
Given a linked list where apart from the next pointer, every node also has a pointer named random which can point to
any other node in the linked list. Make a copy of the linked list.
*/

class CopyLinkedListWithRandomPointers {
    class Node {
    public:
        int val;
        Node *next = nullptr;
        Node *random = nullptr;

        Node(int val, Node *next = nullptr, Node *random = nullptr) : val(val), next(next), random(random) {}
    };

public:
    static void test() {
        CopyLinkedListWithRandomPointers obj;

        Node *root = new Node(1);
        root->next = new Node(2);
        root->next->next = new Node(3);
        root->next->next->next = new Node(4);
        root->next->next->next->next = new Node(5);

        root->random = root->next->next->next;
        root->next->random = root;
        root->next->next->random = root->next;
        root->next->next->next->random = root->next->next->next->next;
        root->next->next->next->next->random = root->next->next;

        string res = obj.str(root);
        cout << "Original list: " << res << endl;

        Node *copy1 = obj.copyList1(root);
        Node *copy2 = obj.copyList2(root);
        Node *copy3 = obj.copyList3(root);

        assert(str(copy1) == str(copy2));
        assert(str(copy1) == str(copy3));

        cout << "Delete original list." << endl;
        remove(root);

        cout << "Copy list: " << str(copy1) << endl;
    }

public:
    static Node *copyList1(Node *root) {
        Node *head = nullptr, *copy = nullptr;
        unordered_map<Node *, Node *> map;

        while (root) {
            if (!head) head = copy = new Node(root->val, nullptr, root->random);
            else {
                copy->next = new Node(root->val, NULL, root->random);
                copy = copy->next;
            }

            map[root] = copy;
            root = root->next;
        }

        copy = head;
        while (copy) {
            copy->random = map[copy->random];
            copy = copy->next;
        }

        return head;
    }

public:
    Node *copyList2(Node *root) {
        if (root == nullptr) return root;

        unordered_map<Node *, Node *> map;

        Node *cur = root;
        Node *newRoot = new Node(cur->val);
        Node *newCur = newRoot;

        map[cur] = newCur;

        cur = cur->next;
        while (cur) {
            newCur->next = new Node(cur->val);
            newCur = newCur->next;
            map[cur] = newCur;

            cur = cur->next;
        }

        cur = root;
        newCur = newRoot;
        while (cur) {
            newCur->random = map[cur->random];

            cur = cur->next;
            newCur = newCur->next;
        }

        return newRoot;
    }

public:
    Node *copyList3(Node *root) {
        if (!root) return root;

        unordered_map<Node *, Node *> map;

        Node *cur = root;
        Node *newRoot = new Node(-1);

        Node *newCur = newRoot;
        while (cur) {
            newCur->next = new Node(cur->val);
            newCur = newCur->next;

            map[cur] = newCur;

            cur = cur->next;
        }

        newCur = newRoot->next;
        delete newRoot;

        newRoot = newCur;

        // set random pointers.
        cur = root;
        while (cur) {
            newCur->random = map[cur->random];

            cur = cur->next;
            newCur = newCur->next;
        }

        return newRoot;
    }

private:
    static string str(Node *root) {
        stringstream ss;
        Node *tmp = root;
        while (tmp) {
            ss << "[" << tmp->val << "," << (tmp->next ? tmp->next->val : -1) << "," << tmp->random->val << "], ";
            tmp = tmp->next;
        }
        ss.seekg(-2);

        return ss.str();
    }

    static void remove(Node *root) {
        Node *next;
        while (root) {
            next = root->next;
            delete root;
            root = next;
        }
    }
};