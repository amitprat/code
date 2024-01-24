#include "../header.h"

class IterativeTreeTraversal {
    class Node {
       public:
        int val;
        Node *left, *right;
        Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

    class IterativeInorderTraversal {
       public:
        static void test() {
            IterativeInorderTraversal obj;

            Node* node1 = new Node(10);
            node1->left = new Node(5);
            node1->left->left = new Node(3);
            node1->left->left->right = new Node(4);
            node1->right = new Node(13);
            node1->right->left = new Node(11);
            node1->right->right = new Node(15);
            node1->right->right->right = new Node(17);

            cout << "Recursive Inorder traversal:" << endl;
            obj.recursiveInorder(node1);
            cout << endl;

            cout << "Iterative Inorder traversal:" << endl;
            obj.iterativeInorder(node1);
            cout << endl;

            Node* node2 = new Node(3);
            node2->left = new Node(1);
            node2->left->right = new Node(2);
            node2->right = new Node(5);

            cout << "Recursive Inorder traversal:" << endl;
            obj.recursiveInorder(node2);
            cout << endl;

            cout << "Iterative Inorder traversal:" << endl;
            obj.iterativeInorder(node2);
            cout << endl;

            obj.mergeTrees(node1, node2);
        }

        void recursiveInorder(Node* root) {
            if (root) {
                recursiveInorder(root->left);
                cout << root->val << " ";
                recursiveInorder(root->right);
            }
        }

        void iterativeInorder(Node* root) {
            stack<Node*> st;
            while (true) {
                while (root) {
                    st.push(root);
                    root = root->left;
                }
                if (st.empty()) break;
                root = st.top();
                st.pop();
                cout << root->val << " ";
                root = root->right;
            }
        }
    };
};