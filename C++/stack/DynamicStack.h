#pragma once
#include "../header.h"

class DynamicStack {
public:
    class Node {
    public:
        Node* prev = nullptr;
        int index;
        Node(int index) :index(index) {}
    };

private:
    int* arr = nullptr;
    int capacity;
    int nums;
    int top;
    vector<int> freelist;
    Node** indices;

public:
    DynamicStack(int nums, int capacity) :nums(nums), capacity(capacity) {
        arr = new int[capacity];
        top = 0;
        indices = new Node * [nums];
        for (int i = 0; i < nums; i++) indices[i] = new Node(-1);
    }

    void push(int num, int item) {
        if (isFull()) throw exception("Stack is full");
        auto cur = indices[num];

        auto nextPos = next();
        arr[nextPos] = item;
        indices[num] = new Node(nextPos);
        indices[num]->prev = cur;
    }

    int pop(int num) {
        auto cur = indices[num];
        if (cur->index == -1) throw exception("Stack is empty");

        auto item = arr[cur->index];
        indices[num] = cur->prev;
        freelist.push_back(cur->index);

        return item;
    }

    bool empty(int num) {
        auto cur = indices[num];
        return cur->index == -1;
    }

    bool empty() {
        return top == 0;
    }

    bool isFull() {
        return top >= capacity && freelist.empty();
    }

    int next() {
        if (top < capacity) {
            auto n = top;
            top++;
            return n;
        }
        auto n = freelist.back();
        freelist.pop_back();
        return n;
    }

    static void test() {
        DynamicStack dst(3, 15);
        //for (int i = 0; i < 16; i++) {
        //    dst.push(i % 3, i);
        //}
        //while (!dst.empty()) cout << dst.pop(0) << " ";
        //cout << endl;

        //for (int i = 0; i < 16; i++) {
        //    dst.push(1, i);
        //}
        //while (!dst.empty()) cout << dst.pop(1) << " ";
        //cout << endl;
        try {
            dst.push(0, 1);
            dst.push(2, 15);
            for (int i = 2; i < 15; i++) dst.push(1, i);

            while (!dst.empty(0)) cout << dst.pop(0) << " ";
            //while (!dst.empty(1)) cout << dst.pop(1) << " ";
            //while (!dst.empty(2)) cout << dst.pop(2) << " ";

            dst.push(0, 16);
            //dst.push(0, 17);
            while (!dst.empty(0)) cout << dst.pop(0) << " ";
            while (!dst.empty(1)) cout << dst.pop(1) << " ";
            while (!dst.empty(2)) cout << dst.pop(2) << " ";
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
};