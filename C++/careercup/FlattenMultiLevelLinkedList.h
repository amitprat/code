#include "../header.h"

class FlattenMultiLevelLinkedList {
    struct Node {
        int val;
        Node *prev = nullptr;
        Node *next = nullptr;
        Node *child = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        Node *root = new Node(1);
        root->next = new Node(2);
        root->next->prev = root;
        root->next->next = new Node(3);
        root->next->next->prev = root->next->next;
        root->next->next->next = new Node(4);
        root->next->next->next->prev = root->next->next->next;
        root->next->next->next->next = new Node(5);
        root->next->next->next->next->prev = root->next->next->next->next;
        root->next->next->next->next->next = new Node(6);
        root->next->next->next->next->next->prev = root->next->next->next->next->next;
        root->next->next->child = new Node(7);
        root->next->next->child->next = new Node(8);
        root->next->next->child->next->prev = root->next->next->child->next;
        root->next->next->child->next->next = new Node(9);
        root->next->next->child->next->next->prev = root->next->next->child->next->next;
        root->next->next->child->next->next->next = new Node(10);
        root->next->next->child->next->next->next->prev = root->next->next->child->next->next->next;
        root->next->next->child->next->child = new Node(11);
        root->next->next->child->next->child->next = new Node(12);
        root->next->next->child->next->child->next->prev = root->next->next->child->next->child->next;

        FlattenMultiLevelLinkedList obj;
        root = obj.flattenList2(root);

        obj.print(root);
    }

   private:
    Node *flattenList(Node *root) {
        if (!root) return root;

        auto next = root->next;
        root->next = flattenList(root->child);
        if (root->next) root->next->prev = root;

        auto tmp = root;
        while (tmp && tmp->next) tmp = tmp->next;

        tmp->next = flattenList(next);
        if (tmp->next) tmp->next->prev = tmp;

        return root;
    }

    Node *flattenList2(Node *head) {
        if (!head) return head;

        Node *headcop = head;
        stack<Node *> save;
        save.push(head);
        Node *prev = NULL;

        while (!save.empty()) {
            Node *temp = save.top();
            save.pop();

            if (temp->next)
                save.push(temp->next);
            if (temp->child)
                save.push(temp->child);

            if (prev != NULL) {
                prev->next = temp;
                prev->child = nullptr;
            }
            if (temp) temp->prev = prev;

            prev = temp;
        }

        return headcop;
    }

    void print(Node *root) {
        while (root) {
            cout << root->val << " ";
            root = root->next;
        }
    }
};