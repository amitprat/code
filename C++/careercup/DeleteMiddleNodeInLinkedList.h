#include "../header.h"

class DeleteMiddleNodeInLinkedList {
    struct Node {
        int val;
        Node *next = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        DeleteMiddleNodeInLinkedList obj;
        {
            Node *root = new Node(1);
            cout << "Original list: " << root << endl;
            root = obj.deleteMiddleNode(root);
            cout << "Updated list: " << root << endl;
            cout << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            cout << "Original list: " << root << endl;
            root = obj.deleteMiddleNode(root);
            cout << "Updated list: " << root << endl;
            cout << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            root->next->next = new Node(3);
            cout << "Original list: " << root << endl;
            root = obj.deleteMiddleNode(root);
            cout << "Updated list: " << root << endl;
            cout << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            root->next->next = new Node(3);
            root->next->next->next = new Node(4);
            cout << "Original list: " << root << endl;
            root = obj.deleteMiddleNode(root);
            cout << "Updated list: " << root << endl;
            cout << endl;
        }
    }

   private:
    Node *deleteMiddleNode(Node *root) {
        Node *slowPrev = nullptr;
        Node *slow = root;
        Node *fast = root;

        while (fast && fast->next && fast->next->next) {
            slowPrev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        if (slowPrev) {
            slowPrev->next = slow->next;
            delete slow;
        } else {
            if (root)
                root = root->next;
            else
                root = nullptr;

            delete slow;
        }

        return root;
    }

    friend std::ostream &operator<<(std::ostream &out, Node *root) {
        while (root) {
            out << root->val << " ";
            root = root->next;
        }

        return out;
    }
};