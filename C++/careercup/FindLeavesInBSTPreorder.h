#include "../header.h"

/*
https://careercup.com/question?id=5749516234915840

given preorder traversal [5,3,2,4,8,7,9] of a BST, how do we identify the leaf nodes without building the tree ?

@Anonymous Thanks for the reply!
Please try other use cases like, only single leaf node

In fact, as a node, I am a leaf i.i.f. the node following me in the preorder traversal array is greater than the first of my ancestors which is greater than me. So while traversing the BST, we need to maintain the stack of the ancestors that are greater than the current node.

In java, something like:

public static List<Integer> getLeaves(List<Integer> bst) {
    List<Integer> leaves = new ArrayList<>();

    Stack<Integer> greaterAncestors = new Stack<>();

    int previous = 0;

    for (int i: bst) {
        int ancestor = 0;
        // Find the first ancestor which is greater than the current node.
        while (!greaterAncestors.isEmpty() && greaterAncesters.peek() < i) {
            ancestor = greaterAncestors.pop();
        }
        greaterAncestors.push(i);
        if (ancestor > previous) {
            leaves.add(previous);
        }
        previous = i;
    }

    if (!bst.isEmpty()) {
        // The last node is always a leaf.
        leaves.add(previous);
    }

    return leaves;
}
*/

class FindLeavesInBSTPreorder {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        vector<int> pre = {10, 5, 1, 7, 40, 50};
        //    10
        //  5   40
        // 1   7    50
        // 5 , 1, 7 ; 40, 50
        // 1,7 ; 40,50
        // 7 ; 40, 50
        // 50

        FindLeavesInBSTPreorder obj;
        obj.printLeaves(pre);
        cout << endl;

        obj.constructBstFromPreorder3(pre);
        cout << endl;

        auto leaves = obj.getLeaves(pre);
        cout << "Leaves: " << leaves << endl;
    }

   private:
    void printLeaves(vector<int> pre) {
        auto root = constructBSTFromPreorder2(pre);

        printLeaves(root);
    }

    void printLeaves(Node *root) {
        if (!root) return;
        if (!root->left && !root->right) {
            cout << root->val << " ";
            return;
        }

        printLeaves(root->left);
        printLeaves(root->right);
    }

    Node *constructBSTFromPreorder(vector<int> pre) {
        int n = pre.size();

        int preIndex = 0;
        return constructBSTFromPreorder(pre, preIndex, 0, n - 1);
    }

    Node *constructBSTFromPreorder(vector<int> pre, int &preIndex, int l, int r) {
        if (l > r) return nullptr;

        Node *root = new Node(pre[preIndex++]);

        int greaterIndex = preIndex;
        for (; greaterIndex < r && pre[greaterIndex] <= root->val; greaterIndex++)
            ;

        root->left = constructBSTFromPreorder(pre, preIndex, preIndex, greaterIndex - 1);
        root->right = constructBSTFromPreorder(pre, preIndex, greaterIndex, r);

        return root;
    }

    void inorder(Node *root) {
        if (!root) return;

        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }

   private:
    Node *constructBSTFromPreorder2(vector<int> &pre) {
        Node *root = nullptr;
        for (auto e : pre) {
            root = insert(root, e);
        }

        inorder(root);

        return root;
    }

    Node *insert(Node *root, int val) {
        if (!root) return new Node(val);
        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);

        return root;
    }

   private:
    Node *constructBstFromPreorder3(vector<int> &pre) {
        int preIndex = 0;
        int sz = pre.size();

        auto root = constructBstFromPreorder3(pre, preIndex, pre[0], INT_MIN, INT_MAX, sz);
        inorder(root);

        return root;
    }

    Node *constructBstFromPreorder3(vector<int> &pre, int &preIndex, int key, int mn, int mx, int sz) {
        if (preIndex >= sz) return nullptr;

        Node *root = nullptr;

        if (key > mn && key < mx) {
            root = new Node(key);
            preIndex++;

            if (preIndex < sz) root->left = constructBstFromPreorder3(pre, preIndex, pre[preIndex], mn, key, sz);
            if (preIndex < sz) root->right = constructBstFromPreorder3(pre, preIndex, pre[preIndex], key, mx, sz);
        }

        return root;
    }

   private:
    vector<int> getLeaves(vector<int> &pre) {
        vector<int> leaves;
        stack<int> st;

        int prev = 0;
        for (auto &e : pre) {
            // find the ancestor of current node which is greater than current node.
            int ancestor = 0;
            while (!st.empty() && st.top() < e) {
                ancestor = st.top();
                st.pop();
            }

            // if ancestor is greater than prev node, add it to leaves.
            if (ancestor > prev) {
                leaves.push_back(prev);
            }

            // push the current node to stack and set it to prev.
            st.push(e);
            prev = e;
        }

        // insert the last node.
        if (!st.empty()) {
            leaves.push_back(prev);
        }

        return leaves;
    }
};