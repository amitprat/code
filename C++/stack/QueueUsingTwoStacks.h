#pragma once
#include "../header.h"

class QueueUsingTwoStacks {
   public:
    static void test() {
        QueueUsingTwoStacks q;
        q.push(2);
        q.push(1);
        q.push(3);

        std::cout << "Queue: ";
        while (!q.empty()) {
            std::cout << q.front() << " ";
            q.pop();
        }
        std::cout << std::endl;
    }

    void push(int val) {
        input.push(val);
    }

    void pop() {
        shiftStacks();
        output.pop();
    }

    int front() {
        shiftStacks();
        return output.top();
    }

    bool empty() const {
        return input.empty() && output.empty();
    }

   private:
    std::stack<int> input;
    std::stack<int> output;

    void shiftStacks() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }
};
