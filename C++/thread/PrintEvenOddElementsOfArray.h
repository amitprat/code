#pragma once
#include "../header.h"

/*
Given an array of elements print even and odd numbers out of it using 2 threads . even_thread and odd_thread.
int arr[] = {3,1 ,2, 5, 6, 7, 8, 10, 9};
*/
class PrintEvenOdd1 {
    std::mutex mut;
    std::condition_variable cv;
    int index = 0;

   public:
    // Even and odd threads might them in any order
    void printOutOfOrder(const vector<int>& arr, string thread, bool isEven) {
        for (auto& num : arr) {
            if (isEven && (num & 1) != 0) continue;
            if (!isEven && (num & 1) == 0) continue;

            unique_lock<mutex> lock(mut);
            cv.wait(lock, [&]() { return isEven && (num & 1) == 0 || !isEven && (num & 1); });

            cout << thread << ": " << num << endl;
            cv.notify_all();
        }
    }

   public:
    // Array elements are printed in order by odd and even threads.
    void printInOrder(const vector<int>& arr, string thread, function<bool(int)> comp) {
        while (true) {
            unique_lock<mutex> lock(mut);
            cv.wait(lock, [&]() { return index >= arr.size() || comp(index); });
            if (index >= arr.size()) {
                cv.notify_all();
                break;
            }

            cout << thread << ": " << arr[index++] << endl;
            cv.notify_all();
        }
    }

   public:
    static void testPrintInOrder() {
        PrintEvenOdd1 obj;
        vector<int> arr = {3, 1, 2, 5, 6, 7, 8, 10, 9};
        auto fut1 = std::async(&PrintEvenOdd1::printInOrder, &obj, arr, "EvenThread", [](auto elem) { return (elem & 1) == 0; });
        auto fut2 = std::async(&PrintEvenOdd1::printInOrder, &obj, arr, "OddThread", [](auto elem) { return (elem & 1) != 0; });

        fut1.get();
        fut2.get();
    }

    static void testPrintOutOfOrder() {
        PrintEvenOdd1 obj;
        vector<int> arr = {3, 1, 2, 5, 6, 7, 8, 10, 9};
        auto fut1 = std::async(&PrintEvenOdd1::printOutOfOrder, &obj, arr, "EvenThread", true);
        auto fut2 = std::async(&PrintEvenOdd1::printOutOfOrder, &obj, arr, "OddThread", false);

        fut1.get();
        fut2.get();
    }
};

class PrintEvenOdd2 {
    mutex m;
    condition_variable cv;

   public:
    static void test() {
        vector<int> arr = {3, 1, 2, 5, 6, 7, 8, 10, 9};
        atomic<int> index = 0;
        PrintEvenOdd2 obj;

        thread t1([&] {
            obj.printEven(arr, index);
        });
        thread t2([&] {
            obj.printOdd(arr, index);
        });

        t1.join();
        t2.join();
    }

    void printEven(vector<int> arr, atomic<int>& index) {
        while (true) {
            unique_lock lock(m);
            cv.wait(lock, [&] { return index >= arr.size() || !(arr[index] & 1); });

            if (index >= arr.size()) {
                cv.notify_all();
                break;
            }

            cout << "Print by even thread " << arr[index++] << endl;
            cv.notify_all();
        }
    }

    void printOdd(vector<int> arr, atomic<int>& index) {
        while (true) {
            unique_lock lock(m);
            cv.wait(lock, [&] { return index >= arr.size() || (arr[index] & 1); });

            if (index >= arr.size()) {
                cv.notify_all();
                break;
            }

            cout << "Print by odd thread " << arr[index++] << endl;
            cv.notify_all();
        }
    }
};