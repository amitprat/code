#include "../header.h"

class SortedListToBST {
    class Node {
       public:
        int val;
        Node *left, *right;
        Node(int val) : val(val), left(nullptr), right(nullptr) {}
    };

   public:
    static void test() {
    }

    // list has right pointer populated as next pointer
    Node *sortedListToBSTRecur(Node *&head, int n) {
        if (n <= 0) return nullptr;

        /* Recursively construct the left subtree */
        Node *left = sortedListToBSTRecur(head, n / 2);

        /* head_ref now refers to middle node, make middle node as root of BST*/
        Node *root = new Node(head->val);

        // Set pointer to left subtree
        root->left = left;

        /* Change head pointer of Linked List for parent recursive calls */
        head = head->right;

        root->right = sortedListToBSTRecur(head, n - n / 2 - 1);

        return root;
    }
};
