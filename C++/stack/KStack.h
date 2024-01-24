#pragma once
#include "../Header.h"

class KStack {
    class Node {
    public:
        int val;
        int prevIndex;
    };
    Node** nodes = nullptr;
    vector<int> prevIndices;
    int curIndex;
    int cap;
public:
    static void test() {
        srand(time(nullptr));
        KStack kstack(3, 10);

        try {
            for (int i = 0; i < 20; i++) {
                kstack.push(rand() % 3, i);
            }
        }
        catch (exception e) {
            cout << e.what() << endl;
        }

        cout << kstack.to_string() << endl;
    }
    KStack(int k, int cap) {
        prevIndices = vector<int>(k, -1);
        nodes = new Node * [cap];
        this->cap = cap;
    }

    void push(int stNum, int val) {
        cout << "Push {stNum=" << stNum << ", val=" << val << "}" << endl;
        if (isFull()) throw exception("Stack is full");
        nodes[curIndex] = new Node{ val, prevIndices[stNum] };
        prevIndices[stNum] = curIndex;
        curIndex++;
    }

    int pop(int stNum) {
        cout << "Pop {stNum=" << stNum << "}" << endl;
        if (isEmpty(stNum)) throw exception("Empty stack");
        Node* res = nodes[prevIndices[stNum]];
        prevIndices[stNum] = res->prevIndex;

        return res->val;
    }

    bool isEmpty() {
        return curIndex == 0;
    }

    bool isFull() {
        return curIndex == cap;
    }

    bool isEmpty(int stNum) {
        return isEmpty() || prevIndices[stNum] == -1;
    }

    string to_string() {
        stringstream ss;
        ss << "[" << endl;
        for (int i = 0; i < prevIndices.size(); i++) {
            ss << setw(4) << "{";
            int start = prevIndices[i];
            while (start != -1) {
                ss << nodes[start]->val << ", ";
                start = nodes[start]->prevIndex;
            }
            //ss.seekp(-2, std::ios_base::end);
            ss << "}" << endl;
        }
        ss << "]" << endl;

        return ss.str();
    }
};