#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template <class T>
class RingBuffer
{
public:
    static void test()
    {
        RingBuffer<int> rb(5);
        try {
            rb.push(1);
            rb.push(2);
            rb.push(3);
            cout << rb.pop() << endl;
            rb.push(4);
            rb.push(5);
            cout << rb.pop() << endl;
            rb.push(6);
            //rb.push(7);
            //rb.push(8);
            cout << rb.pop() << endl;
            cout << rb.pop() << endl;
            rb.push(9);
            rb.push(10);
            while (!rb.isEmpty()) cout << rb.pop() << endl;
            rb.push(1);
            //rb.pop();
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    RingBuffer(int capacity)
    {
        buffer = new T[capacity];
        this->capacity = capacity;
        head = tail = 0;
    }

    void push(T item)
    {
        if (isFull()) throw new exception("Ring buffer is full!!");
        buffer[tail] = item;
        tail = (tail + 1) % capacity;
        sz++;
    }

    T pop()
    {
        if (isEmpty()) {
            head = tail = 0;
            throw new exception("Ring buffer is empty!!");
        }
        T item = buffer[head];
        head = (head + 1) % capacity;
        sz--;

        return item;
    }

    bool isFull()
    {
        return head == ((tail + 1) % capacity);
    }

    bool isEmpty()
    {
        return head == tail;
    }
private:
    T* buffer = nullptr;
    int sz = 0;
    int capacity = 0;
    int head = -1, tail = -1;
};