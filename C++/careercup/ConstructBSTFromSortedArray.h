#include "../header.h"

class ConstructBSTFromSortedArray {
    struct Node {
        int val;
        Node *left, *right;
        Node(int val) : val(val), left(nullptr), right(nullptr) {}
    };

   public:
    static void test() {
        vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
        ConstructBSTFromSortedArray obj;
        Node *root = obj.constructBST(arr, 0, arr.size() - 1);

        vector<int> result;
        obj.inorder(root, result);
        cout << "Inorder: " << result << endl;

        result.clear();
        obj.preorder(root, result);
        cout << "Preorder: " << result << endl;
    }

    Node *constructBST(vector<int> &arr, int l, int r) {
        if (l > r)
            return nullptr;
        int m = (l + r) / 2;
        Node *root = new Node(arr[m]);
        root->left = constructBST(arr, l, m - 1);
        root->right = constructBST(arr, m + 1, r);

        return root;
    }

    void inorder(Node *root, vector<int> &result) {
        if (!root)
            return;

        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right, result);
    }

    /*
            4
        2        6
    1     3  5     7

    4 2 1 3 6 5 7
    */
    void preorder(Node *root, vector<int> &result) {
        if (!root)
            return;

        result.push_back(root->val);
        preorder(root->left, result);
        preorder(root->right, result);
    }
};