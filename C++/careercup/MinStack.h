#include "../header.h"

/*
https://careercup.com/question?id=5741637822054400

Implement a stack that in addition to push and pop has a function that returns the min value of the stack.

I came up with a O(logn) solution, but he wanted a O(1) for the whole algorithm.
*/

template <class T>
class MinStack
{
    stack<T> st;
    stack<T> mnSt;

public:
    void push(T val)
    {
        st.push(val);
        if (mnSt.empty() || val < mnSt.top())
        {
            mnSt.push(val);
        }
    }

    T pop()
    {
        if (this->empty())
            throw exception("Stack is empty.");

        T val = st.top();
        st.pop();
        if (val == mnSt.top())
            mnSt.pop();

        return val;
    }

    T top()
    {
        if (this->empty())
            throw exception("Stack is empty.");

        return st.top();
    }

    T min()
    {
        if (this->empty())
            throw exception("Stack is empty.");

        return mnSt.top();
    }

    bool empty()
    {
        return st.empty();
    }
};

class MinStackTest
{
public:
    static void test()
    {
        MinStack<int> mnStack;
        mnStack.push(10);
        mnStack.push(1);
        mnStack.push(5);
        mnStack.push(2);

        while (!mnStack.empty())
        {
            cout << "top: " << mnStack.top() << endl;
            cout << "min: " << mnStack.min() << endl;

            mnStack.pop();
        }
    }
};