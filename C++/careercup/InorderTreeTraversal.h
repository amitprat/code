#include "../header.h"

class InorderTreeTraversal
{
    struct Node
    {
        int val;
        Node *left = nullptr, *right = nullptr;
        Node(int val) : val(val) {}
    };

    class IterativeTraversal
    {
        Node *root;
        bool asc;
        stack<Node *> st;

    public:
        IterativeTraversal(Node *root, bool asc) : root(root), asc(asc) {}

        bool hasNext()
        {
            return root || !st.empty();
        }

        Node *current()
        {
            while (root)
            {
                st.push(root);
                root = asc ? root->left : root->right;
            }

            return st.top();
        }

        void moveNext()
        {
            root = st.top();
            st.pop();
            root = asc ? root->right : root->left;
        }
    };

public:
    static void test()
    {
        InorderTreeTraversal obj;
        Node *root = nullptr;
        root = obj.add(root, 3);
        root = obj.add(root, 9);
        root = obj.add(root, 1);
        root = obj.add(root, 6);
        root = obj.add(root, 5);
        root = obj.add(root, 8);
        root = obj.add(root, 2);
        root = obj.add(root, 7);
        root = obj.add(root, 4);

        obj.inorderRecursive(root);
        cout << endl;

        obj.inorderIterative(root);
        cout << endl;

        for (int sum = 0; sum <= 20; sum++)
        {
            auto res = obj.findNodesWithGivenSum2(root, sum);
            if (!res.empty())
            {
                for (auto &val : res)
                {
                    cout << val.first->val << " + " << val.second->val << " = " << sum << ", ";
                }
                cout << endl;
            }
        }
    }

private:
    Node *add(Node *root, int val)
    {
        if (!root)
            return new Node(val);
        if (val < root->val)
            root->left = add(root->left, val);
        else
            root->right = add(root->right, val);

        return root;
    }

    void inorderRecursive(Node *root)
    {
        if (!root)
            return;

        inorderRecursive(root->left);
        cout << root->val << " ";
        inorderRecursive(root->right);
    }

private:
    void inorderIterative(Node *root)
    {
        stack<Node *> st;

        while (root || !st.empty())
        {
            while (root)
            {
                st.push(root);
                root = root->left;
            }

            if (st.empty())
                break;
            root = st.top();
            st.pop();

            cout << root->val << " ";
            root = root->right;
        }
    }

private:
    vector<pair<Node *, Node *>> findNodesWithGivenSum(Node *root, int sum)
    {
        stack<Node *> left, right;
        Node *leftPtr = root, *rightPtr = root;

        vector<pair<Node *, Node *>> result;
        while (true)
        {
            while (leftPtr)
            {
                left.push(leftPtr);
                leftPtr = leftPtr->left;
            }
            while (rightPtr)
            {
                right.push(rightPtr);
                rightPtr = rightPtr->right;
            }

            if (left.empty() || right.empty())
                break;

            leftPtr = left.top();
            left.pop();
            rightPtr = right.top();
            right.pop();

            if (leftPtr->val >= rightPtr->val)
                break;

            if (leftPtr->val + rightPtr->val == sum)
            {
                result.push_back({leftPtr, rightPtr});
                leftPtr = leftPtr->right;
                rightPtr = rightPtr->left;
            }
            else if (leftPtr->val + rightPtr->val < sum)
            {
                leftPtr = leftPtr->right;
                right.push(rightPtr);
                rightPtr = nullptr;
            }
            else
            {
                rightPtr = rightPtr->left;
                left.push(leftPtr);
                leftPtr = nullptr;
            }
        }

        return result;
    }

private:
    vector<pair<Node *, Node *>> findNodesWithGivenSum2(Node *root, int sum)
    {
        IterativeTraversal leftPtr(root, true);
        IterativeTraversal rightPtr(root, false);

        vector<pair<Node *, Node *>> result;
        while (leftPtr.hasNext() && rightPtr.hasNext())
        {
            Node *leftNode = leftPtr.current();
            Node *rightNode = rightPtr.current();
            if (leftNode->val >= rightNode->val)
                break;

            int cur = leftNode->val + rightNode->val;
            if (cur == sum)
            {
                result.push_back({leftNode, rightNode});

                leftPtr.moveNext();
                rightPtr.moveNext();
            }
            else if (cur < sum)
            {
                leftPtr.moveNext();
            }
            else
            {
                rightPtr.moveNext();
            }
        }

        return result;
    }
};