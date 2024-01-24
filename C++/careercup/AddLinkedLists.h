#include "../header.h"
// https://www.careercup.com/question?id=5723406763294720

class AddLinkedLists {
   public:
    static void test() {
        ListNode* root1 = ListNode::create({9, 9, 9, 5, 6, 3});
        ListNode* root2 = ListNode::create({9, 4, 3});

        ListNode* root = add(root1, root2);
        cout << root << endl;
    }

    static ListNode* add(ListNode* root1, ListNode* root2) {
        int l1 = ListNode::length(root1);
        int l2 = ListNode::length(root2);

        if (l1 > l2) {
            swap(root1, root2);
            swap(l1, l2);
        }

        int diff = l2 - l1;
        while (diff--) {
            ListNode* newNode = new ListNode(0);  // prefix sorted list with zeros
            newNode->next = root1;
            root1 = newNode;
        }

        int carry = 0;
        ListNode* root = add(root1, root2, carry);
        if (carry) {
            ListNode* newNode = new ListNode(carry);
            newNode->next = root;
            root = newNode;
        }

        return root;
    }

    static ListNode* add(ListNode* root1, ListNode* root2, int& carry) {
        if (!root1 || !root2) return nullptr;

        if (isEnd(root1) && isEnd(root2)) {
            auto val = root1->val + root2->val;
            carry = val / 10;

            return new ListNode(val % 10);
        }

        auto next = add(root1->next, root2->next, carry);

        auto val1 = root1->val + root2->val + carry;
        carry = val1 / 10;
        auto cur = new ListNode(val1 % 10);

        cur->next = next;

        return cur;
    }

    static bool isEnd(ListNode* root) {
        return !root->next;
    }
};