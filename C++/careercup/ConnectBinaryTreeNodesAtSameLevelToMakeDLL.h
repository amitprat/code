#include "../header.h"

class ConnectBinaryTreeNodesAtSameLevelToMakeDLL {
    struct Node {
        int val;
        Node *left, *right;
        Node *nextRight = nullptr;

        Node(int x) : val(x), left(nullptr), right(nullptr) {}
    };

   public:
    static void test() {
        {
            Node *root = new Node(10);
            root->left = new Node(8);
            root->right = new Node(2);
            root->left->left = new Node(3);
            root->right->right = new Node(4);

            ConnectBinaryTreeNodesAtSameLevelToMakeDLL obj;
            obj.printLevelOrder(root, cout);

            // auto head = obj.connectNodesUsingLevelOrder(root);
            // auto head = obj.connectNodesWithoutExtraSpace(root);
            obj.connectNodesUsingRecursionForCompleteBinaryTree(root);

            obj.printDLL(root, cout);
        }

        {
            Node *root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->left->left = new Node(4);
            root->left->right = new Node(5);
            root->right->left = new Node(6);
            root->right->right = new Node(7);
            root->left->left->left = new Node(8);
            root->left->left->right = new Node(9);
            root->left->right->left = new Node(10);
            root->left->right->right = new Node(11);
            root->right->left->left = new Node(12);
            root->right->left->right = new Node(13);
            root->right->right->left = new Node(14);
            root->right->right->left = new Node(15);

            Node *node = obj.binaryTreeToDll2(root);
            while (node) {
                cout << node->val << " ";
                node = node->next;
            }
            cout << endl;
        }
    }

   private:
    void printLevelOrder(Node *root, ostream &out) {
        if (!root) return;

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            while (levelSize--) {
                auto front = q.front();
                q.pop();

                out << front->val << " ";

                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }
            out << '\n';
        }
        out << '\n';
    }

   private:
    Node *connectNodesUsingLevelOrder(Node *root) {
        if (!root) return root;

        queue<Node *> q;
        q.push(root);

        Node *head = nullptr;
        Node *prev = nullptr;

        while (!q.empty()) {
            int levelSize = q.size();

            while (levelSize--) {
                auto front = q.front();
                q.pop();

                if (!prev)
                    prev = head = front;
                else {
                    prev->right = front;
                    prev = front;
                }

                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }
        }

        return head;
    }

    void printDLL(Node *root, ostream &out) {
        while (root) {
            out << root->val << " ";
            root = root->right;
        }
        out << endl;
    }

   private:
    Node *connectNodesWithoutExtraSpace(Node *root) {
        if (!root) return root;

        Node *nextLevelLeftMostNode = root;

        while (nextLevelLeftMostNode) {
            Node *current = nextLevelLeftMostNode;
            Node *currentPrev = nullptr;

            Node *nextLevelPrev = nullptr;
            Node *nextLevelLeftMost = nullptr;

            while (current) {
                // connect nodes at next level
                if (current->left) {
                    if (!nextLevelPrev)
                        nextLevelLeftMost = current->left;
                    else
                        nextLevelPrev->right = current->left;

                    current->left->left = nextLevelPrev;
                    nextLevelPrev = current->left;
                }
                if (current->right) {
                    if (!nextLevelPrev)
                        nextLevelLeftMost = current->right;
                    else
                        nextLevelPrev->right = current->right;

                    current->right->left = nextLevelPrev;
                    nextLevelPrev = current->right;
                }

                currentPrev = current;
                current = current->right;
            }

            // connect prevLevel last node to next level left most node.
            if (currentPrev)
                currentPrev->right = nextLevelLeftMost;
            if (nextLevelLeftMost)
                nextLevelLeftMost->left = currentPrev;

            nextLevelLeftMostNode = nextLevelLeftMost;
        }

        return root;
    }

    Node *findNextNode(Node *curr) {
        while (curr) {
            if (curr->left)
                return curr->left;
            if (curr->right)
                return curr->right;

            curr = curr->right;
        }

        return nullptr;
    }

   private:
    // This only connects nodes at same level
    void connectNodesUsingRecursionForCompleteBinaryTree(Node *root) {
        if (!root) return;

        if (root->left) root->left->nextRight = root->right;
        if (root->right) root->right->nextRight = root->nextRight ? root->nextRight->left : nullptr;

        connectNodesUsingRecursionForCompleteBinaryTree(root->left);
        connectNodesUsingRecursionForCompleteBinaryTree(root->right);
    }

   private:
    Node *binaryTreeToDll1(Node *root) {
        Node *prev = nullptr;
        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            cur->prev = prev;
            if (prev) prev->next = cur;
            prev = cur;

            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }

        return root;
    }

   private:
    Node *binaryTreeToDll2(Node *root) {
        Node *last = root;
        Node *cur = root;

        while (cur) {
            if (cur->left) {
                last->next = cur->left;
                cur->left->prev = last;
                last = cur->left;
            }
            if (cur->right) {
                last->next = cur->right;
                cur->right->prev = last;
                last = cur->right;
            }

            cur = cur->next;
        }

        return root;
    }
};