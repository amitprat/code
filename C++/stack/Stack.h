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

        downSizeIfNeeded();

        return res;
    }

    bool empty() {
        return end == 0;
    }

   private:
    void upSize() {
        int newSize = (size + 1) * 2;
        // cout << format("Upsizing stack size from {} to {}", size, newSize) << endl;

        auto* newArr = new T[newSize];
        for (int i = 0; i < end; i++) {
            newArr[i] = array[i];
        }

        swap(array, newArr);
        size = newSize;

        delete[] newArr;
    }

    void downSizeIfNeeded() {
        if (end > (size / 2)) return;

        int newSize = size / 2;
        // cout << format("Downsizing stack size from {} to {}", size, newSize) << endl;

        auto* newArr = new T[newSize];
        for (int i = 0; i < end; i++) {
            newArr[i] = array[i];
        }

        swap(array, newArr);
        size = newSize;

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