#pragma once
#include "../Header.h"

template <class T>
class TwoDArray {
    T* arr = nullptr;
    int rows, cols;

    TwoDArray(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;

        arr = (T**)malloc(rows * sizeof(T*));
        for (int i = 0; i < rows; i++) {
            arr[i] = malloc(cols * sizeof(T));
        }
    }

    ~TwoDArray() {
        for (int i = 0; i < rows; i++) {
            free(arr[i]);
        }
        free(arr);
    }

    T operator[][](int i, int j) {

    }

public:
    static void test() {
        TwoDArray* obj = new TwoDArray(5, 3);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                obj[i][j] = i * j;
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                cout << obj[i][j] << " ";
            }
            cout << endl;
        }
    }
};