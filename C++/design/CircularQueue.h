#pragma once
#include "../header.h"

template <class T>
class CircularQueue {
    T* arr = nullptr;
    int start = 0;
    int end = -1;
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
            throw exception("buffer empty!");
        }
        return arr[start];
    }

    T pop() {
        if (empty()) {
            reset();
            throw exception("buffer empty!");
        }
        sz--;
        auto res = arr[start];
        start = next(start);
        return res;
    }

    bool empty() {
        return end == -1;
    }

    bool full() {
        return (end != -1) && next(end) == start;
    }

    void reset() {
        start = 0;
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

template <class T>
class CircularQueue2 {
    T* arr = nullptr;
    int start = 0;
    int end = -1;
    int capacity = 0;
    int sz = 0;

public:
    CircularQueue2(int capacity) : capacity(capacity) {
        arr = new T[capacity];
    }

    void push(T elem) {
        if (full()) {
            start++;
            sz--;
        }
        sz++;
        arr[++end % capacity] = elem;
    }

    T top() {
        if (empty()) {
            reset();
            throw exception("buffer empty!");
        }
        return arr[start];
    }

    T pop() {
        if (empty()) {
            reset();
            throw exception("buffer empty!");
        }
        sz--;
        auto res = arr[start % capacity];
        start++;
        return res;
    }

    bool empty() {
        return end == -1;
    }

    bool full() {
        return (end != -1) && (end + 1) % capacity == start;
    }

    void reset() {
        start = 0;
        end = -1;
    }

    string to_string() {
        stringstream ss;
        for (int i = start; i <= end; i++) {
            ss << arr[i % capacity] << " ";
        }

        return ss.str();
    }

    int size() {
        return sz;
    }
};

class CircularQueueTest {
public:
    static void test() {
        CircularQueue2<string> cq(4);
        for (int i = 0; i < 20; i++) {
            cq.push(std::to_string(i));
            cout << cq.to_string() << endl;
        }

        while (!cq.empty()) cout << cq.pop() << " ";
    }
};