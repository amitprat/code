#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int val;
    Node *left, *right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

Node *getNode(Node *node, bool &shouldMove, stack<Node *> &st, bool isRight)
{
    if (!shouldMove)
        return node;
    while (node)
    {
        st.push(node);
        node = isRight ? node->right : node->left;
    }
    if (!st.empty())
    {
        node = st.top();
        st.pop();
    }
    shouldMove = false;

    return node;
}

void findSum(Node *root, int sum)
{
    stack<Node *> left, right;
    Node *leftNode = root, *rightNode = root;
    bool moveLeft = true, moveRight = true;
    bool found = false;
    while (true)
    {
        leftNode = getNode(leftNode, moveLeft, left, false);
        rightNode = getNode(rightNode, moveRight, right, true);
        if (leftNode == nullptr || rightNode == nullptr)
            break;
        if (leftNode->val + rightNode->val == sum)
        {
            cout << "Found sum " << leftNode->val << " + " << rightNode->val << " = " << sum << endl;
            found = true;
            break;
        }
        else if (leftNode->val + rightNode->val < sum)
        {
            moveLeft = true;
            leftNode = leftNode->right;
        }
        else
        {
            moveRight = true;
            rightNode = rightNode->left;
        }
    }
    if (!found)
        cout << "Sum not found!" << endl;
}

int main()
{
    Node *root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(8);
    root->left->left = new Node(2);
    root->left->left->left = new Node(1);
    root->left->right = new Node(4);
    root->right->left = new Node(7);
    root->right->right = new Node(20);

    for (int sum = 0; sum < 40; sum++)
    {
        findSum(root, sum);
    }

    return 0;
}