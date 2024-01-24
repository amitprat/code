#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left=nullptr, *right = nullptr;
    Node(int val):val(val) {}
};

int maxPathSum(Node *root, int& sum) {
    if(!root) return 0;
    
    int leftSum = INT_MIN, rightSum = INT_MIN;
    auto left = maxPathSum(root->left, leftSum);
    auto right = maxPathSum(root->right, rightSum);
    
    sum = max(sum, max(leftSum, rightSum));
    auto cur = root->val + (left > 0 ? left : 0) + (right > 0 ? right : 0);
    sum = max(sum, cur);
    
    return cur;
}

int main()
{
    Node *root = new Node(-1);
    root->left = new Node(-2);
    root->right = new Node(3);
    root->right->left = new Node(3);
    root->right->right = new Node(2);
    
    auto sum = INT_MIN;
    maxPathSum(root, sum);
    cout<<sum<<endl;
    
    return 0;
}
