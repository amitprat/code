#include "../header.h"

class PartitionLinkedList
{
    template <class T>
    struct Node
    {
        T val;
        Node *next;
        Node(T val) : val(val), next(nullptr) {}
    };

public:
    static void test()
    {
        PartitionLinkedList obj;
        {
            Node<int> *root = new Node<int>(1);
            root->next = new Node<int>(2);
            root->next->next = new Node<int>(3);
            root->next->next->next = new Node<int>(4);
            root->next->next->next->next = new Node<int>(5);
            root->next->next->next->next->next = new Node<int>(6);
            root->next->next->next->next->next->next = new Node<int>(7);
            root->next->next->next->next->next->next->next = new Node<int>(8);

            cout << "Original list: ";
            obj.print<int>(root);

            auto res = obj.partitionList<int>(root, 4, [](const auto &x, const auto &y)
                                              { return x < y ? -1 : (x == y ? 0 : 1); });

            cout << "Rearranged list: ";
            obj.print<int>(res);

            cout << endl;
        }

        {
            Node<int> *root = new Node<int>(2);
            root->next = new Node<int>(1);

            cout << "Original list: ";
            obj.print<int>(root);

            auto res = obj.partitionList<int>(root, 1, [](const auto &x, const auto &y)
                                              { return x < y ? -1 : (x == y ? 0 : 1); });

            cout << "Rearranged list: ";
            obj.print<int>(res);

            cout << endl;
        }

        {
            Node<int> *root = new Node<int>(20);
            root->next = new Node<int>(10);
            root->next->next = new Node<int>(2);
            root->next->next->next = new Node<int>(30);

            cout << "Original list: ";
            obj.print<int>(root);

            auto res = obj.partitionList<int>(root, 9, [](const auto &x, const auto &y)
                                              { return x < y ? -1 : (x == y ? 0 : 1); });

            cout << "Rearranged list: ";
            obj.print<int>(res);

            cout << endl;
        }

        {
            Node<int> *root = new Node<int>(1);

            cout << "Original list: ";
            obj.print<int>(root);

            auto res = obj.partitionList<int>(root, 1, [](const auto &x, const auto &y)
                                              { return x < y ? -1 : (x == y ? 0 : 1); });

            cout << "Rearranged list: ";
            obj.print<int>(res);

            cout << endl;
        }

        {
            Node<int> *root = new Node<int>(2);

            cout << "Original list: ";
            obj.print<int>(root);

            auto res = obj.partitionList<int>(root, 1, [](const auto &x, const auto &y)
                                              { return x < y ? -1 : (x == y ? 0 : 1); });

            cout << "Rearranged list: ";
            obj.print<int>(res);

            cout << endl;
        }
    }

private:
    template <class T>
    Node<T> *partitionList(Node<T> *head, T val, std::function<int(const T &, const T &)> compare)
    {
        Node<T> *firstRoot = nullptr;
        Node<T> *secondRoot = nullptr;

        Node<T> *x = nullptr;
        Node<T> *y = nullptr;

        while (head)
        {
            if (compare(head->val, val) <= 0)
            {
                if (!firstRoot)
                {
                    firstRoot = x = head;
                }
                else
                {
                    x->next = head;
                    x = x->next;
                }
            }
            else
            {
                if (!secondRoot)
                {
                    secondRoot = y = head;
                }
                else
                {
                    y->next = head;
                    y = y->next;
                }
            }

            head = head->next;
        }

        if (x == nullptr)
            return secondRoot;

        x->next = secondRoot;
        if (y)
            y->next = nullptr;

        return firstRoot;
    }

    template <class T>
    void print(Node<T> *root)
    {
        while (root)
        {
            cout << root->val << " ";
            root = root->next;
        }
        cout << endl;
    }
};