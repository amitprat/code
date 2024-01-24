#pragma once
#include "../header.h"

template <class T>
class Stack {
private:
    T* array = nullptr;
    int size = 0;
    int end = 0;

public:
    Stack() {}
    void push(T val) {
        if (array == nullptr || end == size) upSize();
        array[end++] = val;
    }
    T top() {
        if (empty()) throw exception("Stack already empty!");
        return array[end - 1];
    }
    T pop() {
        if (empty()) throw exception("Stack already empty!");
        auto res = array[end - 1];
        end--;
        downSize();
        return res;
    }
    bool empty() {
        return end == 0;
    }

private:
    void upSize() {
        size = (size + 1) * 2;
        auto* newArr = new T[size];
        for (int i = 0; i < end; i++) {
            newArr[i] = array[i];
        }
        swap(array, newArr);
        delete[] newArr;
    }

    void downSize() {
        if (end > size / 2) return;
        size = end;
        auto* newArr = new T[size];
        for (int i = 0; i < size; i++) {
            newArr[i] = array[i];
        }
        swap(array, newArr);
        delete[] newArr;
    }
};

class StackTest {
public:
    static void test() {
        Stack<int> st;
        for (int i = 0; i < 10; i++) st.push(i);
        while (!st.empty()) cout << st.pop() << " ";
    }
};