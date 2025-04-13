#include "../header.h"
using namespace std;

class PartitionLinkedList {
    template <class T>
    struct Node {
        T val;
        Node *next;
        Node(T val) : val(val), next(nullptr) {}
    };

   public:
    static void test() {
        PartitionLinkedList obj;

        auto run_case = [&](auto vals, int pivot) {
            Node<int> *root = createList(vals);
            std::cout << "Original list: ";
            obj.print(root);

            auto cmp = [](const auto &x, const auto &y) { return (x < y ? -1 : (x == y ? 0 : 1)); };
            Node<int> *result = obj.partitionList(root, pivot, cmp);

            std::cout << "Rearranged list: ";
            obj.print(result);
            std::cout << std::endl;
        };

        run_case({1, 2, 3, 4, 5, 6, 7, 8}, 4);
        run_case({2, 1}, 1);
        run_case({20, 10, 2, 30}, 9);
        run_case({1}, 1);
        run_case({2}, 1);
    }

   private:
    template <class T>
    Node<T> *partitionList(Node<T> *head, T val, const std::function<int(const T &, const T &)> compare) {
        Node<T> *firstRoot = nullptr;
        Node<T> *secondRoot = nullptr;

        Node<T> *x = nullptr;
        Node<T> *y = nullptr;

        while (head) {
            if (compare(head->val, val) <= 0) {
                if (!firstRoot) {
                    firstRoot = x = head;
                } else {
                    x->next = head;
                    x = x->next;
                }
            } else {
                if (!secondRoot) {
                    secondRoot = y = head;
                } else {
                    y->next = head;
                    y = y->next;
                }
            }

            head = head->next;
        }

        if (x == nullptr) return secondRoot;

        x->next = secondRoot;
        if (y) y->next = nullptr;

        return firstRoot;
    }

   public:
    template <class T>
    Node<T> *partitionList2(Node<T> *head, int x) {
        Node<T> *start = head;
        Node<T> *end = head;

        while (head) {
            if (head->val < x) {
                auto *newHead = head;
                newHead->next = start;
                start = newHead;
            } else {
                end->next = head;
                end = end->enxt;
            }
            head = head->next;
        }

        return start;
    }

   public:
    void partition(Node<int> *&first, Node<int> *&second, int val) {
        Node<int> *node = first;
        first = second = nullptr;

        while (node) {
            Node<int> *next = node->next;

            if (node->val <= val) {
                node->next = first;
                first = node;
            } else {
                node->next = second;
                second = node;
            }

            node = next;
        }
    }

    void partitionCareerCup(Node<int> *&node, int val) {
        Node<int> *head = node;
        Node<int> *tail = node;
        head->next = nullptr;

        while (node) {
            Node<int> *next = node->next;

            if (node->val < val) {
                node->next = head;
                head = node;
            } else {
                tail->next = node;
                tail = node;
            }

            node = next;
        }

        tail->next = nullptr;
        node = head;
    }

   private:
    template <typename T>
    static Node<T> *createList(const std::initializer_list<T> &vals) {
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        for (const T &val : vals) {
            Node<T> *newNode = new Node<T>(val);
            if (!head) head = tail = newNode;
            else tail = tail->next = newNode;
        }
        return head;
    }

    template <class T>
    void print(Node<T> *root) {
        while (root) {
            cout << root->val << " ";
            root = root->next;
        }
        cout << endl;
    }
};