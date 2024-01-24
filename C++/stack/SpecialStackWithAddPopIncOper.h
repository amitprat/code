#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5656728816320512

Twitter
Create a simple stack which takes a list of elements.
Each element contains a stack operator (push, pop, inc) and a value to either push/pop or two values, n and m,
which increment the bottom n values by m.
Then print the topmost value of the stack after every operation. If the stack is empty, print "empty"

The push, pop and inc can all take place in O(1) time
if there is an additional array to maintain the m incremented at each position n.


class Stack:
    def __init__(self):
        self.nums = []
        self.add = []

    def push(self,num):
        self.nums.append(num)
        self.add.append(0)
        print num," "

    def pop(self):
        try:
            number_to_add = self.add.pop()
            print self.nums.pop() + number_to_add
            if self.add:
                self.add[-1] += number_to_add
        except:
            print "can't pop from an empty stack"

    def inc(self, n, m):
        if not self.nums:
            print "empty"
        if n > 0:
            n = min(n, len(self.nums))
            self.add[n - 1] += m
        print self.nums[-1] + self.add[-1], " "
*/

class SpecialStackWithAddPopIncOper {
    vector<int> stack;
    vector<int> valuesToAdd;

public:
    static void test() {
        SpecialStackWithAddPopIncOper st;

        st.push(1);
        st.push(2);
        st.push(3);
        cout << "Inc " << st.inc(2, 1) << endl;

        st.push(4);
        st.push(5);
        cout << "Inc " << st.inc(4, 2) << endl;

        while (!st.empty()) {
            cout << st.pop() << endl;
        }
    }

    void push(int val) {
        stack.push_back(val);
        valuesToAdd.push_back(0);
    }

    int pop() {
        if (stack.empty()) throw exception("empty stack");

        int numToAdd = valuesToAdd.back();  valuesToAdd.pop_back();
        int valueReturn = stack.back() + numToAdd; stack.pop_back();

        if (!valuesToAdd.empty()) valuesToAdd[valuesToAdd.size() - 1] += numToAdd;

        return valueReturn;
    }

    int inc(int n, int m) {
        if (valuesToAdd.empty()) throw exception("empty stack");

        int l = min((int)valuesToAdd.size(), n);
        valuesToAdd[l - 1] += m;

        return stack.back() + valuesToAdd.back();
    }

    bool empty() {
        return stack.empty();
    }
};