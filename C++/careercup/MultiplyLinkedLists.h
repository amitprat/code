#include "../header.h"

/*
https://careercup.com/question?id=5654773747417088

Given two extremely large numbers - each number is stored in a Singly Linked list, with the MSB at the head. You are not allowed to reverse the Linked lists. Write a program to multiply them in optimum space and time.

*/
class MultiplyLinkedLists {
    struct Node {
        int val;
        Node *next = nullptr;
        Node(int val) : val(val) {}
    };
    Node *createListFromArray(vector<int> arr) {
        Node *root = new Node(-1);
        Node *tmp = root;
        for (auto &e : arr) {
            tmp->next = new Node(e);
            tmp = tmp->next;
        }

        tmp = root;
        root = root->next;

        delete tmp;

        return root;
    }

    void printList(Node *root) {
        cout << "List: ";
        while (root) {
            cout << root->val << " ";
            root = root->next;
        }
        cout << endl;
    }

    int listToInt(Node *root) {
        int val = 0;
        root = cloneAndReverse(root);
        int mul = 1;
        while (root) {
            val += root->val * mul;
            root = root->next;
            mul *= 10;
        }

        return val;
    }

   public:
    static void test() {
        MultiplyLinkedLists obj;

        {
            cout << "Multiplying lists: " << endl;
            Node *root1 = obj.createListFromArray({1});
            // obj.printList(root1);

            Node *root2 = obj.createListFromArray({1});
            // obj.printList(root2);

            cout << "Result: " << endl;
            Node *res = obj.multiply(root1, root2);
            obj.printList(res);
            assert(obj.listToInt(root1) * obj.listToInt(root2), obj.listToInt(res));
        }

        {
            cout << "Multiplying lists: " << endl;
            Node *root1 = obj.createListFromArray({1, 0});
            // obj.printList(root1);

            Node *root2 = obj.createListFromArray({0});
            // obj.printList(root2);

            cout << "Result: " << endl;
            Node *res = obj.multiply(root1, root2);
            obj.printList(res);
            assert(obj.listToInt(root1) * obj.listToInt(root2), obj.listToInt(res));
        }

        {
            Node *root1 = obj.createListFromArray({9, 9});
            obj.printList(root1);

            Node *root2 = obj.createListFromArray({9});
            obj.printList(root2);

            Node *res = obj.multiply(root1, root2);
            obj.printList(res);
            assert(obj.listToInt(root1) * obj.listToInt(root2), obj.listToInt(res));
        }

        {
            Node *root1 = obj.createListFromArray({1});
            obj.printList(root1);

            Node *root2 = obj.createListFromArray({9, 9});
            obj.printList(root2);

            Node *res = obj.multiply(root1, root2);
            obj.printList(res);
            assert(obj.listToInt(root1) * obj.listToInt(root2), obj.listToInt(res));
        }

        {
            Node *root1 = obj.createListFromArray({1, 2, 8, 9});
            obj.printList(root1);

            Node *root2 = obj.createListFromArray({9, 9});
            obj.printList(root2);

            Node *res = obj.multiply(root1, root2);
            obj.printList(res);
            assert(obj.listToInt(root1) * obj.listToInt(root2), obj.listToInt(res));
        }

        {
            Node *root1 = obj.createListFromArray({1, 2});
            obj.printList(root1);

            Node *root2 = obj.createListFromArray({9, 9, 9});
            obj.printList(root2);

            Node *res = obj.multiply(root1, root2);
            obj.printList(res);
            assert(obj.listToInt(root1) * obj.listToInt(root2), obj.listToInt(res));
        }

        cout << "test successfull" << endl;
    }

   private:
    Node *multiply(Node *head1, Node *head2) {
        Node *resultTail = new Node(-1);
        Node *tail1 = cloneAndReverse(head1);
        Node *tail2 = cloneAndReverse(head2);

        Node *resultTailOrg = resultTail;
        Node *tail2Tmp = tail2;
        while (tail2Tmp) {
            Node *resultTailTmp = resultTail;
            Node *tail1Tmp = tail1;
            int carry = 0;
            while (tail1Tmp) {
                auto val = multiply(tail1Tmp->val, tail2Tmp->val, carry);
                resultTailTmp->next = sum(resultTailTmp->next, val % 10);
                carry = val / 10;

                tail1Tmp = tail1Tmp->next;
                resultTailTmp = resultTailTmp->next;
            }
            if (carry) resultTailTmp->next = new Node(carry);
            tail1Tmp = tail1;

            tail2Tmp = tail2Tmp->next;
            resultTail = resultTail->next;
        }

        Node *result = cloneAndReverse(resultTailOrg->next);

        return result;
    }

    Node *sum(Node *cur, int val) {
        if (!cur) return new Node(val);
        cur->val += val;

        return cur;
    }

    Node *cloneAndReverse(Node *head) {
        Node *rev = new Node(-1);
        while (head) {
            auto cur = new Node(head->val);
            cur->next = rev;
            rev = cur;

            head = head->next;
            rev = rev->next;
        }

        return rev;
    }

    int multiply(int val1, int val2, int carry) {
        return val1 * val2 + carry;
    }
};