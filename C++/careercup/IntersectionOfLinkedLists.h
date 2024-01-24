#include "../header.h"

class IntersectionOfLinkedLists
{
    struct Node
    {
        int val;
        Node *next = nullptr;
        Node(int val) : val(val) {}
    };

public:
    static void test()
    {
        // 1->3->5->7->9->11
        Node *root1 = new Node(1);
        root1->next = new Node(3);
        root1->next->next = new Node(5);
        root1->next->next->next = new Node(7);
        root1->next->next->next->next = new Node(9);
        root1->next->next->next->next->next = new Node(11);

        // 0->2->4->6->7->9->11
        Node *root2 = new Node(0);
        root2->next = new Node(2);
        root2->next->next = new Node(4);
        root2->next->next->next = new Node(6);
        root2->next->next->next->next = root1->next->next->next;

        cout << "List list: " << root1 << endl;
        cout << "List list: " << root2 << endl;

        IntersectionOfLinkedLists obj;
        Node *node = obj.findIntersection(root1, root2);
        cout << "Intsection point: " << node->val << endl;
    }

private:
    Node *moveNode(Node *root, int l)
    {
        while (l)
        {
            root = root->next;
            l--;
        }

        return root;
    }

    int length(Node *root)
    {
        int l = 0;
        while (root)
        {
            l++;
            root = root->next;
        }

        return l;
    }

    Node *findIntersection(Node *root1, Node *root2)
    {
        int l1 = length(root1);
        int l2 = length(root2);

        if (l1 < l2)
            root2 = moveNode(root2, l2 - l1);
        else if (l1 > l2)
            root1 = moveNode(root1, l1 - l2);

        while (root1 && root2)
        {
            if (root1 == root2)
                return root1;

            root1 = root1->next;
            root2 = root2->next;
        }

        return nullptr;
    }

    friend std::ostream &operator<<(std::ostream &out, Node *root)
    {
        while (root)
        {
            out << root->val << " ";
            root = root->next;
        }

        return out;
    }
};