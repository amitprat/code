#pragma once
#include "../header.h"
using namespace std;

class IDeque
{
public:
    virtual bool isFull() = 0;

    virtual bool isEmpty() = 0;

    virtual void pushFront(int item) = 0;

    virtual void pushBack(int item) = 0;

    virtual int front() = 0;

    virtual int back() = 0;

    virtual int popFront() = 0;

    virtual int popBack() = 0;
};

class ArrayDeque : public IDeque
{
private:
    int* arr = nullptr;
    int capacity;
    int start, end;

public:
    ArrayDeque(int capacity) : capacity(capacity)
    {
        arr = new int[capacity];
        start = end = 0;
    }

    bool isFull() override
    {
        return start == end + 1;
    }

    bool isEmpty() override
    {
        return start == end;
    }

    void pushFront(int item) override
    {
        if (isFull()) throw exception("Already Full!");
        start = index(start - 1);
        arr[start] = item;
    }

    void pushBack(int item) override
    {
        if (isFull()) throw exception("Already Full!");
        arr[end] = item;
        end = index(end + 1);
    }

    int front() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        return arr[start];
    }

    int back() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        return arr[end - 1];
    }

    int popFront() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        auto item = arr[start];
        start = index(start + 1);
        return item;
    }

    int popBack() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        end = index(end - 1);
        return arr[end];
    }

    void print()
    {
        if (isEmpty()) throw exception("Empty queue!");
        for (int i = start; i != end; i = index(i + 1)) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int index(int idx) {
        return (capacity + idx) % capacity;
    }
};

class LinkedDeque : public IDeque
{
private:
    struct Node
    {
        int val;
        Node* next;
        Node* prev;
        Node(int val) : val(val), next(nullptr), prev(nullptr) {}
    };

    Node* start = nullptr;
    Node* end = nullptr;

public:
    bool isFull() override
    {
        return false;
    }
    bool isEmpty() override
    {
        return start == nullptr;
    }

    void pushFront(int item) override
    {
        if (!start) {
            start = end = new Node(item);
            return;
        }

        auto node = new Node(item);
        node->next = start;
        start->prev = node;
        start = node;
    }

    void pushBack(int item) override
    {
        if (!start) {
            start = end = new Node(item);
            return;
        }

        end->next = new Node(item);
        end->next->prev = end;
        end = end->next;
    }

    int front() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        return start->val;
    }

    int back() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        return end->val;
    }

    int popFront() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        auto cur = start;
        start = start->next;
        if (start == nullptr) start = end = nullptr;
        else start->prev = nullptr;

        return cur->val;
    }

    int popBack() override
    {
        if (isEmpty()) throw exception("Empty queue!");
        auto cur = end;
        end = end->prev;
        if (end == nullptr) start = end = nullptr;
        else end->next = nullptr;

        return cur->val;
    }

    void print()
    {
        if (isEmpty()) throw exception("Empty queue!");
        for (auto tmp = start; tmp != nullptr; tmp = tmp->next) {
            cout << tmp->val << " ";
        }
        cout << endl;
    }
};

class DequeTest
{
public:
    static void test()
    {
        IDeque* deque = new LinkedDeque();
        try {
            deque->pushBack(1);

            deque->pushFront(2);
            cout << "Back :" << deque->back() << endl;

            deque->pushBack(3);
            cout << "Front :" << deque->front() << endl;

            cout << "Pop back : " << deque->popBack() << endl;
            cout << "Pop back : " << deque->popBack() << endl;
            cout << "Pop back : " << deque->popBack() << endl;

            deque->pushBack(1);
            deque->pushFront(10);

            deque->pushBack(2);
            deque->pushFront(9);

            cout << "Pop back : " << deque->popFront() << endl;
            cout << "Pop back : " << deque->popFront() << endl;
            cout << "Pop back : " << deque->popFront() << endl;
            cout << "Pop back : " << deque->popFront() << endl;

            for (int i = 0; i < 11; i++) {
                try {
                    deque->pushBack(i);
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
};