#include "../header.h"

/*
https://careercup.com/question?id=24532662

You are given two array, first array contain integer which represent heights of persons and second array contain how many persons in front of him are standing who are greater than him in term of height and forming a queue. Ex
A: 3 2 1
B: 0 1 1
It means in front of person of height 3 there is no person standing, person of height 2 there is one person in front of him who has greater height then he, similar to person of height 1. Your task to arrange them
Ouput should be.
3 1 2
Here - 3 is at front, 1 has 3 in front ,2 has 1 and 3 in front.
*/

class RearrangePeopleByHeight
{
    struct Node
    {
        int val;
        int lsize = 1;
        Node *left = nullptr, *right = nullptr;
        Node(int val, int lsize) : val(val), lsize(lsize) {}
    };

    using p = pair<int, int>;

public:
    static void test()
    {
        vector<p> arrs = {{6, 0}, {5, 0}, {4, 0}, {3, 2}, {2, 2}, {1, 4}};

        RearrangePeopleByHeight obj;
        vector<p> order = obj.rearragePeople(arrs);
        vector<p> count;
        for (int i = 0; i < order.size(); i++)
        {
            int cnt = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                if (order[j].first > order[i].first)
                    cnt++;
            }
            count.push_back({order[i].first, cnt});
        }
        cout << "order: " << order << endl;
        cout << "count: " << count << endl;
    }

    vector<p> rearragePeople(vector<p> &arr)
    {
        Node *root = nullptr;
        for (auto &val : arr)
        {
            root = insert(root, val);
        }

        vector<p> output;
        inorder(root, output);

        return output;
    }

    Node *insert(Node *root, p val)
    {
        if (!root)
            return new Node(val.first, val.second + 1);
        if (val.second < root->lsize)
        {
            root->lsize++;
            root->left = insert(root->left, val);
        }
        else
        {
            root->right = insert(root->right, {val.first, val.second - root->lsize});
        }

        return root;
    }

    void inorder(Node *root, vector<p> &output)
    {
        if (!root)
            return;

        inorder(root->left, output);
        output.push_back({root->val, root->lsize});
        inorder(root->right, output);
    }
};