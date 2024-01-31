#pragma once
#include "../header.h"

template <class T>
class CircularQueue {
    T* arr = nullptr;
    int start = 0;
    int end = 0;
    int capacity = 0;
    int sz = 0;

   public:
    CircularQueue(int capacity) : capacity(capacity) {
        arr = new T[capacity];
    }

    void push(T elem) {
        if (full()) {
            start = next(start);
            sz--;
        }

        sz++;
        end = next(end);

        arr[end] = elem;
    }

    T top() {
        if (empty()) {
            reset();
            throw runtime_error("buffer empty!");
        }

        return arr[start];
    }

    T pop() {
        if (empty()) {
            reset();
            throw runtime_error("buffer empty!");
        }

        sz--;
        auto res = arr[start];
        start = next(start);

        return res;
    }

    bool empty() {
        return start == end;
    }

    bool full() {
        return next(end) == start;
    }

    void reset() {
        start = -1;
        end = -1;
    }

    string to_string() {
        stringstream ss;
        for (int i = start;; i = next(i)) {
            ss << arr[i] << " ";
            if (i == end) break;
        }

        return ss.str();
    }

    int size() {
        return sz;
    }

    int next(int i) {
        return (i + 1) % capacity;
    }
};

class CircularQueueTest {
   public:
    static void test() {
        CircularQueue<string> cq(4);
        for (int i = 0; i < 20; i++) {
            cq.push(std::to_string(i));
            cout << cq.to_string() << endl;
        }

        while (!cq.empty()) cout << cq.pop() << " ";
    }
};