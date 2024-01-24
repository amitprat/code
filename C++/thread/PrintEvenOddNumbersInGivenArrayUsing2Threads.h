#pragma once
#include "../Header.h"

class PrintEvenOddNumbersInGivenArrayUsing2Threads {
    mutex m;
    condition_variable cv;

public:
    static void test() {
        vector<int> arr = { 3,1,2,5,6,7,8,10,9 };
        atomic<int> index = 0;
        PrintEvenOddNumbersInGivenArrayUsing2Threads obj;

        thread t1([&] { obj.printEven(arr, index); });
        thread t2([&] { obj.printOdd(arr, index); });

        t1.join();
        t2.join();
    }

    void printEven(vector<int> arr, atomic<int>& index) {
        while (true) {
            unique_lock lock(m);
            cv.wait(lock, [&] {return index >= arr.size() || !(arr[index] & 1); });

            if (index < arr.size()) {
                cout << "Print by even thread " << arr[index++] << endl;
            }
            else { break; }

            cv.notify_all();
        }
    }

    void printOdd(vector<int> arr, atomic<int>& index) {
        while (true) {
            unique_lock lock(m);
            cv.wait(lock, [&] { return index >= arr.size() || (arr[index] & 1); });

            if (index < arr.size()) {
                cout << "Print by odd thread " << arr[index++] << endl;
            }
            else { break; }

            cv.notify_all();
        }
    }
};