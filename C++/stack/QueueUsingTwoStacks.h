#include "../header.h"

class QueueUsingTwoStacks
{
public:
    static void test()
    {
        QueueUsingTwoStacks q;
        q.push(2);
        q.push(1);
        q.push(3);

        cout << "Queue: ";
        while (!q.empty())
        {
            cout << q.front() << " ";
            q.pop();
        }
        cout << endl;
    }

private:
    stack<int> s1, s2;

public:
    void push(int val)
    {
        s2.push(val);
    }

    int pop()
    {
        if (s1.empty())
        {
            while (!s2.empty())
            {
                s1.push(s2.top());
                s2.pop();
            }
        }

        auto val = s1.top();
        s1.pop();
        return val;
    }

    int front()
    {
        if (s1.empty())
        {
            while (!s2.empty())
            {
                s1.push(s2.top());
                s2.pop();
            }
        }

        return s1.top();
    }

    bool empty()
    {
        return s1.empty() && s2.empty();
    }
};