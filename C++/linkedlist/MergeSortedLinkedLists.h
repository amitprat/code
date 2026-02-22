#include "../header.h"

// https://leetcode.com/problems/merge-k-sorted-lists/description/?envType=problem-list-v2&envId=oizxjoit
class MergeSortedLinkedLists {
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };

   public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        using P = pair<int, ListNode*>;
        priority_queue<P, vector<P>, greater<P>> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i]) pq.push({lists[i]->val, lists[i]});
        }

        ListNode* result = new ListNode(-1);
        ListNode* tmp = result;
        while (!pq.empty()) {
            auto [val, head] = pq.top();
            pq.pop();
            tmp->next = head;
            tmp = tmp->next;
            if (head->next) pq.push({head->next->val, head->next});
        }

        return result->next;
    }
};