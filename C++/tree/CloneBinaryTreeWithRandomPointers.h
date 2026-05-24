#pragma once
#include "../header.h"

class CloneBinaryTreeWithRandomPointers {
    struct Node {
        int val;
        Node *left, *right, *random;
        Node(int val) : val(val), left(nullptr), right(nullptr), random(nullptr) {}
    };

   public:
    Node* cloneTree(Node* orig) {
        unordered_map<Node*, Node*> map;

        Node* clonedNode = cloneLeftRightNodes(orig, map);

        copyRandomPointers(orig, map);
    }

    Node* cloneLeftRightNodes(Node* orig, unordered_map<Node*, Node*>& map) {
        if (!orig) return nullptr;

        map[orig] = new Node(orig->val);

        map[orig]->left = cloneLeftRightNodes(orig->left, map);
        map[orig]->right = cloneLeftRightNodes(orig->right, map);

        return map[orig];
    }

    void copyRandomPointers(Node* orig, unordered_map<Node*, Node*>& map) {
        if (!orig) return;

        map[orig]->random = map[orig->random];
        copyRandomPointers(orig->left, map);
        copyRandomPointers(orig->right, map);
    }

   private:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> oldToNewNodeMap;

        Node* newHead = new Node(-1);
        Node* org = head;
        Node* cur = newHead;
        while (org) {
            cur->next = new Node(org->val);
            oldToNewNodeMap[org] = cur->next;

            cur = cur->next;
            org = org->next;
        }

        cur = newHead->next;
        org = head;
        while (cur) {
            cur->random = oldToNewNodeMap[org->random];
            cur = cur->next;
            org = org->next;
        }

        return newHead->next;
    }
};