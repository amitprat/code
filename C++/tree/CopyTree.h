#pragma once
#include "../header.h"

class CopyTree {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        CopyTree obj;

        Node* root1 = new Node(1);
        root1->left = new Node(2);
        root1->left->left = new Node(3);
        root1->left->left->right = new Node(4);
        root1->right = new Node(5);
        root1->right->left = new Node(6);
        root1->right->right = new Node(7);

        cout << "Original tree before copy" << endl;
        {
            auto levelOrderStr = (new BinaryTree<int>(root1))->levelOrder();
            println("Level order traversal: ");
            println("{0}", levelOrderStr);
        }

        Node* root2;
        root2 = obj.copyTree(root1);

        cout << "Original tree after copy" << endl;
        {
            auto levelOrderStr = (new BinaryTree<int>(root1))->levelOrder();
            println("Level order traversal: ");
            println("{0}", levelOrderStr);
        }

        cout << "New tree after copy" << endl;
        {
            auto levelOrderStr = (new BinaryTree<int>(root2))->levelOrder();
            println("Level order traversal: ");
            println("{0}", levelOrderStr);
        }

        Node* root3;
        root3 = obj.deleteTree(root2);

        cout << "Original tree after delete of new tree" << endl;
        {
            auto levelOrderStr = (new BinaryTree<int>(root1))->levelOrder();
            println("Level order traversal: ");
            println("{0}", levelOrderStr);
        }

        cout << "New tree after delete of new tree" << endl;
        {
            auto levelOrderStr = (new BinaryTree<int>(root3))->levelOrder();
            println("Level order traversal: ");
            println("{0}", levelOrderStr);
        }
    }

   public:
    Node* copyTree(Node* root) {
        if (!root) return nullptr;

        Node* newRoot = new Node(root->val);

        newRoot->left = copyTree(root->left);
        newRoot->right = copyTree(root->right);

        return newRoot;
    }

    Node* deleteTree(Node* root) {
        if (!root) return nullptr;

        root->left = deleteTree(root->left);
        root->right = deleteTree(root->right);

        delete root;
        root = nullptr;

        return root;
    }
};

class CopyTreeUsingUniquePtr {
    struct Node {
        int val;
        unique_ptr<Node> left, right;
        Node(int val) : val(val) {}
    };

    std::vector<std::vector<int>> levelOrder(Node* root) const {
        std::vector<std::vector<int>> result;
        if (!root) return result;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            std::vector<int> currentLevel;

            for (int i = 0; i < levelSize; ++i) {
                Node* node = q.front();
                q.pop();

                currentLevel.push_back(node->val);

                if (node->left) q.push(node->left.get());
                if (node->right) q.push(node->right.get());
            }

            result.push_back(std::move(currentLevel));
        }

        return result;
    }

   public:
    static void test() {
        CopyTreeUsingUniquePtr obj;

        auto root1 = std::make_unique<Node>(1);
        root1->left = std::make_unique<Node>(2);
        root1->left->left = std::make_unique<Node>(3);
        root1->left->left->right = std::make_unique<Node>(4);
        root1->right = std::make_unique<Node>(5);
        root1->right->left = std::make_unique<Node>(6);
        root1->right->right = std::make_unique<Node>(7);

        std::cout << "Original tree before copy" << std::endl;
        {
            auto levelOrderStr = obj.levelOrder(root1.get());
            println("Level order traversal: {0}", levelOrderStr);
        }

        auto root2 = obj.copyTree(root1.get());

        std::cout << "Original tree after copy" << std::endl;
        {
            auto levelOrderStr = obj.levelOrder(root1.get());
            println("Level order traversal: {0}", levelOrderStr);
        }

        std::cout << "New tree after copy" << std::endl;
        {
            auto levelOrderStr = obj.levelOrder(root2.get());
            println("Level order traversal: {0}", levelOrderStr);
        }

        obj.deleteTree(root2);

        std::cout << "Original tree after delete of new tree" << std::endl;
        {
            auto levelOrderStr = obj.levelOrder(root1.get());
            println("Level order traversal: {0}", levelOrderStr);
        }

        std::cout << "New tree after delete of new tree" << std::endl;
        {
            auto levelOrderStr = obj.levelOrder(root2.get());
            println("Level order traversal: {0}", levelOrderStr);
        }
    }

    std::unique_ptr<Node> copyTree(const Node* root) {
        if (!root) return nullptr;

        auto newRoot = std::make_unique<Node>(root->val);
        newRoot->left = copyTree(root->left.get());
        newRoot->right = copyTree(root->right.get());

        return newRoot;
    }

    void deleteTree(std::unique_ptr<Node>& root) {
        root.reset();  // Automatically deletes the subtree
    }
};