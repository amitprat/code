#pragma once
#include "../header.h"

class ReverseQueue {
   public:
    static void test() {
        ReverseQueue obj;
        queue<int> q;
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        q.push(5);

        {
            auto tmp = q;
            obj.reverseQueueRecursiveUsingSystemStack(tmp);
            obj.print(tmp);
        }

        {
            auto tmp = q;
            obj.reverseQueueUsingStack(tmp);
            obj.print(tmp);
        }
    }

   public:
    void reverseQueueUsingStack(queue<int>& q) {
        stack<int> st;
        while (!q.empty()) {
            st.push(q.front());
            q.pop();
        }

        while (!st.empty()) {
            q.push(st.top());
            st.pop();
        }
    }

   public:
    void reverseQueueRecursiveUsingSystemStack(queue<int>& q) {
        if (q.empty()) return;

        auto front = q.front();
        q.pop();
        reverseQueueRecursiveUsingSystemStack(q);

        q.push(front);
    }

   private:
    void print(queue<int> q) {
        while (!q.empty()) {
            cout << q.front() << " ";
            q.pop();
        }
        cout << endl;
    }
};