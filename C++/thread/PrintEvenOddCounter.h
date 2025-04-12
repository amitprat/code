#pragma once
#include "../header.h"

class PrintEvenOddCounter {
    int n;
    mutex m;
    condition_variable cv;
    int count = 1;

   public:
    PrintEvenOddCounter(int n) : n(n) {}

    static void test() {
        int n = 100;
        PrintEvenOddCounter obj(n);
        obj.print();
    }

    void print() {
        thread t1([this] { this->printOdd(); });
        thread t2(&PrintEvenOddCounter::printEven, this);

        t1.join();
        t2.join();
    }

    void printOdd() {
        while (count < 100) {
            unique_lock lock(m);
            cv.wait(lock, [this]() { return count & 1; });

            cout << "From Odd: " << count << endl;
            count++;

            cv.notify_all();
        }
    }

    void printEven() {
        while (count < 100) {
            unique_lock lock(m);
            cv.wait(lock, [this]() { return !(count & 1); });

            cout << "From Even: " << count << endl;
            count++;

            cv.notify_all();
        }
    }
};