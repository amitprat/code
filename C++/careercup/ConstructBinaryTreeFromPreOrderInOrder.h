#pragma once
#include "../header.h"
#include "../tree/BinaryTree.h"

class ConstructBinaryTreeFromPreOrderInOrder {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
    }

   public:
    Node* contructTree(vector<int>& preorder, vector<int>& inorder) {
        int index = 0;

        unordered_map<int, int> valToIndexMap;
        for (int i = 0; i < inorder.size(); i++) {
            valToIndexMap[inorder[i]] = i;
        }

        return contructTree(preorder, index, valToIndexMap, 0, preorder.size() - 1);
    }

    Node* contructTree(vector<int>& preorder, int& index, unordered_map<int, int>& valToIndexMap, int l, int r) {
        if (l > r) return nullptr;

        int val = preorder[index++];
        int pos = valToIndexMap[val];

        auto root = new Node(val);
        root->left = contructTree(preorder, index, valToIndexMap, l, pos - 1);
        root->right = contructTree(preorder, index, valToIndexMap, pos + 1, r);

        return root;
    }
};