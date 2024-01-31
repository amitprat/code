#pragma once
#include "../header.h"

template <class T>
class StackNode {
public:
    int prevIndex;
    T val;
    StackNode() {}
    StackNode(int index, T val) : prevIndex(index), val(val) {}
};

template <class T>
class MultiStack
{
private:
    StackNode<T>* array = nullptr;
    int size = 0;
    int numStacks = 0;
    int end = 0;
    vector<int> stackTops;

public:
    MultiStack(int size, int k) {
        this->size = size;
        numStacks = k;
        array = new StackNode<T>[size];
        stackTops.resize(k);
        for (int i = 0; i < k; i++) stackTops[i] = -1;
    }

    void push(int stIndex, T val) {
        if (stIndex > numStacks) throw exception("Invalid Input!");
        if (!empty()) throw exception("No space left");
        array[end++] = StackNode<T>(stackTops[stIndex], val);
        stackTops[stIndex] = end - 1;
    }

    bool empty(int stIndex) {
        return stackTops[stIndex] == -1;
    }

    T top(int stIndex) {
        if (empty(stIndex)) throw exception("stack is empty");
        auto node = stackTops[stIndex];
        return node.val;
    }

    T pop(int stIndex) {
        if (empty(stIndex)) throw exception("stack is empty");
        auto index = stackTops[stIndex];
        auto val = array[index].val;
        stackTops[stIndex] = array[index].prevIndex;
        return val;
    }

private:
    bool empty() {
        return end != size;
    }
};

class MultiStackTest {
public:
    static void test() {
        MultiStack<string> st(100, 10);
        try {
            for (int i = 0; i < 50; i++) {
                st.push(1, to_string(i));
            }
            for (int i = 0; i < 20; i++) {
                st.push(5, to_string(i * 10));
            }
            for (int i = 0; i < 10; i++) {
                st.push(0, to_string(i * 100));
            }
            for (int i = 0; i < 20; i++) {
                st.push(1, to_string(i + 51));
            }
            for (int i = 0; i < 10; i++) {
                while (!st.empty(i)) cout << st.pop(i) << " ";
                cout << endl;
            }
        }
        catch (exception e) {
            cout << e.what() << endl;
        }
    }
};