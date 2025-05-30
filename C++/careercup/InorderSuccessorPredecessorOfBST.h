#include "../header.h"

class InorderSuccessorPredecessorOfBST {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        Node *root = new Node(5);
        root->left = new Node(3);
        root->left->parent = root;
        root->right = new Node(10);
        root->right->parent = root;
        root->left->left = new Node(1);
        root->left->left->parent = root->left;
        root->right->left = new Node(7);
        root->right->left->parent = root->right;
        root->right->right = new Node(20);
        root->right->right->parent = root->right;

        InorderSuccessorPredecessorOfBST obj;
        obj.inorder(root, cout);
        cout << endl;

        Node *suc1 = obj.inorderSuccesssor(root, root->right->left->val);
        Node *suc2 = obj.inorderSuccesssorUsingParentPointer(root->right->left);
        Node *suc3 = nullptr, *pred3 = nullptr;
        obj.inorderSuccessorAndPredecessor(root, pred3, suc3, root->right->left->val);
        assert(suc1 == suc2);
        assert(suc1 == suc3);
        cout << format("Successor of {} is {}", root->right->left->val, suc1->val) << endl;

        Node *suc = obj.inorderSuccesssor(root, root->right->val);
        cout << format("Successor of {} is {}", root->right->val, suc->val) << endl;

        suc = obj.inorderSuccesssor(root, root->left->val);
        cout << format("Successor of {} is {}", root->left->val, suc->val) << endl;

        suc = obj.inorderSuccesssor(root, root->right->right->val);
        cout << format("Successor of {} is {}", root->right->right->val, suc ? suc->val : -1) << endl;

        Node *pre = obj.inorderPredecessor(root, root->val);
        cout << format("Predecessor of {} is {}", root->val, pre->val) << endl;

        pre = obj.inorderPredecessor(root, root->right->val);
        cout << format("Predecessor of {} is {}", root->right->val, pre->val) << endl;

        pre = obj.inorderPredecessor(root, root->right->left->val);
        cout << format("Predecessor of {} is {}", root->right->left->val, pre->val) << endl;

        pre = obj.inorderPredecessor(root, root->right->val);
        cout << format("Predecessor of {} is {}", root->right->val, pre->val) << endl;

        pre = obj.inorderPredecessor(root, root->left->val);
        cout << format("Predecessor of {} is {}", root->left->val, pre->val) << endl;

        pre = obj.inorderPredecessor(root, root->left->left->val);
        cout << format("Predecessor of {} is {}", root->left->left->val, pre ? pre->val : -1) << endl;

        pre = obj.inorderPredecessor(root, root->right->right->val);
        cout << format("Predecessor of {} is {}", root->right->right->val, pre ? pre->val : -1) << endl;
    }

   private:
    Node *inorderSuccesssorUsingParentPointer(Node *root) {
        if (!root) return nullptr;

        Node *suc = nullptr;
        if (root->right) {
            suc = root->right;
            while (suc->left) suc = suc->left;
        } else {
            Node *parent = root->parent;
            while (parent && parent->right == root) {
                root = root->parent;
                parent = root->parent;
            }
            suc = parent;
        }

        return suc;
    }

    Node *inorderPredecessorUsingParentPointer(Node *root) {
        if (!root) return root;

        Node *pre = nullptr;
        if (root->left) {
            pre = root->left;
            while (pre->right) pre = pre->right;
        } else {
            Node *parent = root->parent;
            while (parent && parent->left == root) {
                root = root->parent;
                parent = parent->parent;
            }
            pre = parent;
        }

        return pre;
    }

   private:
    Node *inorderSuccesssor(Node *root, int val) {
        Node *suc = nullptr;

        while (root) {
            if (val < root->val) {
                suc = root;
                root = root->left;
            } else {
                root = root->right;
            }
        }

        return suc;
    }

    Node *inorderPredecessor(Node *root, int val) {
        Node *pre = nullptr;

        while (root) {
            if (val <= root->val) {
                root = root->left;
            } else {
                pre = root;
                root = root->right;
            }
        }

        return pre;
    }

   private:
    void inorderSuccessorAndPredecessor(Node *root, Node *&pred, Node *&succ, int key) {
        if (!root) return;

        if (key < root->val) {
            succ = root;
            inorderSuccessorAndPredecessor(root->left, pred, succ, key);
        } else {
            pred = root;
            inorderSuccessorAndPredecessor(root->right, pred, succ, key);
        }
    }

   private:
    void inorder(Node *root, std::ostream &out) {
        if (!root) return;

        inorder(root->left, out);
        out << root->val << " ";
        inorder(root->right, out);
    }

   private:
    Node *inorder_suc(Node *root, Node *node) {
        if (!root || !node) return NULL;
        if (root->right) return min(root->right);

        Node *parent = root->parent;
        while (parent && parent->left != root) {
            root = parent;
            parent = root->parent;
        }
        return parent;
    }

    Node *min(Node *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
};