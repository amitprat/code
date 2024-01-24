#pragma once
#include "../Header.h"

class ReverseInGroups {
public:
    static void test() {
        LinkedListNode<int>* node = Construct<int>({ 1,2,3,4,5,6,7,8 });

        cout << to_string(node) << endl;
        int len = length(node);

        ReverseInGroups obj;
        auto newHead = obj.reverseInGroups(node, 4, len);

        cout << to_string(newHead) << endl;
    }

    LinkedListNode<int>* reverseInGroups(LinkedListNode<int>* node, int k, int len) {
        if (!node || len < k) return node;
        LinkedListNode<int>* prev = nullptr, * next = nullptr, * cur = node;

        int cnt = 0;
        while (cur && cnt++ < k) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        node->next = reverseInGroups(next, k, len - k);

        return prev;
    }
};