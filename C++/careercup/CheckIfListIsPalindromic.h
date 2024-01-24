#include "../header.h"

class CheckIfListIsPalindromic {
    struct Node {
        int val;
        Node *next = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        CheckIfListIsPalindromic obj;
        {
            Node *root = new Node(1);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(1);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            root->next->next = new Node(1);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            root->next->next = new Node(2);
            root->next->next->next = new Node(1);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            root->next->next = new Node(3);
            root->next->next->next = new Node(1);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }

        {
            Node *root = new Node(1);
            root->next = new Node(2);
            root->next->next = new Node(3);
            root->next->next->next = new Node(2);
            root->next->next->next->next = new Node(1);

            cout << "List: " << root << endl;

            bool res1 = obj.IsPalindromicUsingListReverse(root);
            cout << "Is list palindromic: " << res1 << endl;

            bool res2 = obj.IsPalindromicUsingStack(root);
            cout << "Is list palindromic: " << res2 << endl;

            bool res3 = obj.IsPalindromicUsingRecursion(root, root);
            cout << "Is list palindromic: " << res3 << endl;
        }
    }

   private:
    bool IsPalindromicUsingListReverse(Node *root) {
        Node *rev = reverseList(root);
        return IsSame(root, rev);
    }

    Node *reverseList(Node *root) {
        Node *newRoot = new Node(root->val);
        while (root->next) {
            Node *newRootNext = newRoot;
            newRoot = new Node(root->next->val);
            newRoot->next = newRootNext;
            root = root->next;
        }

        return newRoot;
    }

    bool IsSame(Node *root1, Node *root2) {
        while (root1 && root2) {
            if (root1->val != root2->val)
                return false;
            root1 = root1->next;
            root2 = root2->next;
        }

        return (!root1 && !root2);
    }

    bool IsPalindromicUsingStack(Node *root) {
        stack<Node *> st;
        Node *cur = root;
        while (cur) {
            st.push(cur);
            cur = cur->next;
        }

        while (root) {
            auto cur = st.top();
            st.pop();
            if (cur->val != root->val)
                return false;
            root = root->next;
        }

        return true;
    }

    bool IsPalindromicUsingRecursion(Node *&root1, Node *root2) {
        if (!root2)
            return true;

        bool res = IsPalindromicUsingRecursion(root1, root2->next);
        if (!res || root1->val != root2->val)
            return false;

        root1 = root1->next;

        return true;
    }

    friend std::ostream &operator<<(std::ostream &out, Node *root) {
        while (root) {
            out << root->val << " ";
            root = root->next;
        }

        return out;
    }
};