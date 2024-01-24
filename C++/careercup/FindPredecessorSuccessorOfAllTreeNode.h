#include "../Header.h"

struct Node
{
    int val;
    Node *left, *right;
    Node *predecessor = nullptr;
    Node *successor = nullptr;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

Node *min(Node *root)
{
    if (!root)
        return root;
    while (root->left)
        root = root->left;
    return root;
}

void successor(Node *root, int val, Node *&suc)
{
    if (!root)
        return;
    if (root->val == val)
    {
        if (root->right)
            suc = min(root->right);
        return;
    }

    if (val > root->val)
    {
        successor(root->right, val, suc);
    }
    else
    {
        suc = root;
        successor(root->left, val, suc);
    }
}

int successor(Node *root, int val)
{
    Node *result = nullptr;
    successor(root, val, result);

    if (result != nullptr)
        return result->val;
    return -1;
}

Node *fillSuccessor(Node *root, Node *successor)
{
    if (!root)
        return nullptr;

    auto right = fillSuccessor(root->right, successor);
    auto left = fillSuccessor(root->left, root);

    if (right)
        root->successor = right;
    else
        root->successor = successor;

    return left ? left : root;
}

Node *fillPredecessor(Node *root, Node *predecessor)
{
    if (!root)
        return nullptr;

    auto left = fillPredecessor(root->left, predecessor);
    auto right = fillPredecessor(root->right, root);

    if (left)
        root->predecessor = left;
    else
        root->predecessor = predecessor;

    return right ? right : root;
}

void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->val << " " << (root->successor ? root->successor->val : -1) << endl;
    inorder(root->right);
}

void inorderP(Node *root)
{
    if (!root)
        return;
    inorderP(root->left);
    cout << root->val << " " << (root->predecessor ? root->predecessor->val : -1) << endl;
    inorderP(root->right);
}

int test()
{
    Node *root = new Node(4);
    root->left = new Node(2);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right = new Node(6);
    root->right->left = new Node(5);
    root->right->right = new Node(7);

    cout << "---" << endl;
    fillSuccessor(root, nullptr);

    inorder(root);

    cout << "---" << endl;
    fillPredecessor(root, nullptr);

    inorderP(root);

    cout << "---" << endl;
    cout << "Successor of 0 ->" << successor(root, 0) << endl;
    cout << "Successor of 1 ->" << successor(root, 1) << endl;
    cout << "Successor of 2 ->" << successor(root, 2) << endl;
    cout << "Successor of 3 ->" << successor(root, 3) << endl;
    cout << "Successor of 4 ->" << successor(root, 4) << endl;
    cout << "Successor of 5 ->" << successor(root, 5) << endl;
    cout << "Successor of 6 ->" << successor(root, 6) << endl;

    return 0;
}
