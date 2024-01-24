#include "../header.h"

class IsSubTree {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        Node *root1 = new Node(3);
        root1->left = new Node(4);
        root1->right = new Node(5);
        root1->right->left = new Node(6);
        root1->right->right = new Node(7);

        Node *root2 = new Node(5);
        root2->left = new Node(6);
        root2->right = new Node(7);

        IsSubTree obj;
        bool res = obj.isSubTreeWithSerializedPreorder(root1, root2);
        cout << "Is sub tree: " << res << endl;
    }

    bool isSubTree(Node *root1, Node *root2) {
        if (!root1 && !root2) return true;
        if (!root1) return false;

        if (isSubTreeStartsFromHere(root1, root2)) return true;

        return isSubTree(root1->left, root2) || isSubTree(root1->right, root2);
    }

    bool isSubTreeStartsFromHere(Node *root1, Node *root2) {
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;

        if (root1->val == root2->val &&
            isSubTreeStartsFromHere(root1->left, root2->left) &&
            isSubTreeStartsFromHere(root1->right, root2->right)) {
            return true;
        }

        return false;
    }

    bool isSubTreeWithInorderAndPreorder(Node *root1, Node *root2) {
        string inorder1, preorder1;
        inorder(root1, inorder1);
        preorder(root1, preorder1);

        string inorder2, preorder2;
        inorder(root2, inorder2);
        preorder(root2, preorder2);

        return inorder1.find(inorder2) != string::npos && preorder1.find(preorder2) != string::npos;
    }

    void inorder(Node *root, string &order) {
        if (!root) return;

        inorder(root->left, order);
        order += std::to_string(root->val);
        inorder(root->right, order);
    }

    void preorder(Node *root, string &order) {
        if (!root) return;

        order += std::to_string(root->val);
        preorder(root->left, order);
        preorder(root->right, order);
    }

    bool isSubTreeWithSerializedPreorder(Node *root1, Node *root2) {
        string order1;
        serializedPreorder(root1, order1);

        string order2;
        serializedPreorder(root2, order2);

        return order1.find(order2) != string::npos;
    }

    void serializedPreorder(Node *root, string &order) {
        if (!root) {
            order += "#";
            return;
        }

        order += std::to_string(root->val);
        serializedPreorder(root->left, order);
        serializedPreorder(root->right, order);
    }
};