#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> left, right;

    Node(int value) : data(value) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() = default;

    std::unique_ptr<Node> insert_node(std::unique_ptr<Node> node, int value) {
        if (!node) {
            return std::make_unique<Node>(value);
        }
        if (value < node->data) {
            node->left = insert_node(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = insert_node(std::move(node->right), value);
        }
        return node;
    }

    void inorder_traversal(Node* node) {
        if (node) {
            inorder_traversal(node->left.get());
            std::cout << node->data << " ";
            inorder_traversal(node->right.get());
        }
    }

    std::unique_ptr<Node> root = nullptr;
};

int main() {
    BinarySearchTree bst;
    bst.root = bst.insert_node(std::move(bst.root), 50);
    bst.root = bst.insert_node(std::move(bst.root), 30);
    bst.root = bst.insert_node(std::move(bst.root), 20);
    bst.root = bst.insert_node(std::move(bst.root), 40);
    bst.root = bst.insert_node(std::move(bst.root), 60);
    bst.root = bst.insert_node(std::move(bst.root), 10);

    bst.inorder_traversal(bst.root.get());
    std::cout << std::endl;

    return 0;
}