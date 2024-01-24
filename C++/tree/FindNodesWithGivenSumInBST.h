#include "../header.h"

template <class K, class V>
struct Node {
    K key;
    V val;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(K key, V val) : key(key), val(val) {}
};

template <class K, class V>
class BinarySearchTree {
   private:
   public:
    Node<K, V>* root = nullptr;
    BinarySearchTree() {}
    BinarySearchTree(vector<pair<K, V>> vals) {
        for (auto val : vals) {
            root = insert(root, val.first, val.second);
        }
    }

    Node<K, V>* insert(Node<K, V>* root, K key, V val) {
        if (!root) {
            root = new Node<K, V>(key, val);
            return root;
        }
        if (key < root->key)
            root->left = insert(root->left, key, val);
        else if (key > root->key)
            root->right = insert(root->right, key, val);
        else
            root->val = val;

        return root;
    }

    string to_string() {
        stringstream ss;
        Node<K, V>* tmp = root;
        to_string(tmp, ss);

        return ss.str();
    }

    void to_string(Node<K, V>* tmp, stringstream& ss) {
        if (tmp) {
            to_string(tmp->left, ss);
            ss << "{" << tmp->key << ":" << tmp->val << "}";
            ss << ", ";
            to_string(tmp->right, ss);
        }
    }
};
class FindNodesWithGivenSuminBST {
   public:
    static void test() {
        FindNodesWithGivenSuminBST obj;
        BinarySearchTree<int, int> bst1({{1, 2}, {2, 3}, {2, 3}, {5, 3}, {8, 4}});
        BinarySearchTree<int, int> bst2({{0, 9}, {1, 4}, {5, 7}, {9, 10}, {11, 4}, {13, 20}});
        // cout << "BST1: " << bst1.to_string() << endl;
        // cout << "BST2: " << bst1.to_string() << endl;

        // for (int sum = 0; sum < 50; sum++) {
        //     auto res = obj.findPairWithSum(bst1, sum);
        //     string strres = "{" + to_string(res.first) + ", " + to_string(res.second) + "}";
        //     cout << "Found sum  = " << sum << " : " << strres.c_str() << endl;
        // }

        BinarySearchTree<int, int> bst3 = obj.makeBalancedBST(bst1, bst2);
        cout << "BST3: " << bst3.to_string() << endl;
    }

    pair<int, int> findPairWithSum(BinarySearchTree<int, int> bst1, int sum) {
        stack<Node<int, int>*> stack1;
        stack<Node<int, int>*> stack2;

        Node<int, int>* left = bst1.root;
        Node<int, int>* right = bst1.root;
        bool checkLeft = true;
        bool checkRight = true;

        while (true) {
            while (left && checkLeft) {
                stack1.push(left);
                left = left->left;
            }
            checkLeft = false;

            while (right && checkRight) {
                stack2.push(right);
                right = right->right;
            }
            checkRight = false;

            if (!left && !stack1.empty()) {
                left = stack1.top();
                stack1.pop();
            }
            if (!right && !stack2.empty()) {
                right = stack2.top();
                stack2.pop();
            }
            if (!left || !right || left->key >= right->key) return {-1, -1};
            int cursum = left->key + right->key;
            if (sum == cursum)
                return {left->key, right->key};
            else if (cursum < sum) {
                left = left->right;
                checkLeft = true;
            } else {
                right = right->left;
                checkRight = true;
            }
        }

        return {-1, -1};
    }

    BinarySearchTree<int, int> makeBalancedBST(BinarySearchTree<int, int> bst1, BinarySearchTree<int, int> bst2) {
        Node<int, int>* root1 = nullptr;
        makeDLL(bst1.root, root1);
        // cout << "DLL1 : ";
        // printDLL(root1);

        Node<int, int>* root2 = nullptr;
        makeDLL(bst2.root, root2);
        // cout << "DLL2 : ";
        // printDLL(root2);

        Node<int, int>* root3 = mergeDLLsRecur(root1, root2);
        cout << "DLL3 : ";
        printDLL(root3);

        Node<int, int>* root = makeBalanceBST(root3);

        BinarySearchTree<int, int> newBST;
        newBST.root = root;
        cout << "New BST: " << newBST.to_string() << endl;

        return newBST;
    }

    void makeDLL(Node<int, int>* root, Node<int, int>*& dllRoot) {
        static Node<int, int>* prev = nullptr;
        if (root) {
            makeDLL(root->left, dllRoot);

            root->left = prev;
            if (!dllRoot) dllRoot = root;
            if (prev) {
                prev->right = root;
            }
            prev = root;

            makeDLL(root->right, dllRoot);
        }
    }

    Node<int, int>* mergeDLLsRecur(Node<int, int>* root1, Node<int, int>* root2) {
        if (!root1) return root2;
        if (!root2) return root1;
        if (root1->key < root2->key) {
            root1->right = mergeDLLsRecur(root1->right, root2);
            if (root1->right) root1->right->left = root1;
            root1->left = nullptr;
            return root1;
        } else {
            root2->right = mergeDLLsRecur(root1, root2->right);
            if (root2->right) root2->right->left = root2;
            root2->left = nullptr;
            return root2;
        }
    }

    Node<int, int>* mergeDLLs(Node<int, int>* root1, Node<int, int>* root2) {
        Node<int, int>* dummy = new Node<int, int>(-1, -1);
        Node<int, int>* runner = dummy;
        while (root1 && root2) {
            cout << root1->key << " " << root2->key << " " << runner->key << endl;
            if (root1->key < root2->key) {
                auto next = root1->right;
                root1->right = nullptr;
                runner->right = root1;
                root1->left = runner;
                runner = runner->right;
                root1 = next;
            } else {
                auto next = root2->right;
                root2->right = nullptr;
                runner->right = root2;
                root2->left = runner;
                runner = runner->right;
                root2 = next;
            }
        }

        return dummy->right;
    }

    Node<int, int>* makeBalanceBST(Node<int, int>* root) {
        return nullptr;
    }

    void printDLL(Node<int, int>* root) {
        while (root) {
            cout << "{" << root->key << ", " << root->val << "}";
            cout << ", ";
            root = root->right;
        }
        cout << endl;
    }
};