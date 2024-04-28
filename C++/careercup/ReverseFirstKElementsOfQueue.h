#pragma once
#include "../header.h"

class ReverseFirstKElementsOfQueue {
   public:
    static void test() {
        queue<int> q;
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        q.push(5);

        ReverseFirstKElementsOfQueue obj;
        obj.reverseFirstKElements(q, 3);

        obj.print(q);
    }

   public:
    void reverseFirstKElements(queue<int>& q, int k) {
        reverseFirstKElementsInternal(q, k);

        print(q);

        int s = q.size() - k;
        while (s--) {
            auto cur = q.front();
            q.pop();
            q.push(cur);
        }
    }

    void reverseFirstKElementsInternal(queue<int>& q, int k) {
        if (k == 0) return;

        auto front = q.front();
        q.pop();
        reverseFirstKElementsInternal(q, k - 1);

        q.push(front);
    }

   private:
    void print(queue<int>& q) {
        queue<int> tmp = q;
        while (!tmp.empty()) {
            cout << tmp.front() << " ";
            tmp.pop();
        }
        cout << endl;
    }
};