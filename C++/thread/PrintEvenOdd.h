#pragma once
#include "../header.h"

class PrintEvenOdd {
    int n;
    mutex m;
    condition_variable cv;
    int count = 1;

   public:
    PrintEvenOdd(int n) : n(n) {}

    static void test() {
        int n = 100;
        PrintEvenOdd obj(n);
        obj.print();
    }

    void print() {
        thread t1([this] { this->printOdd(); });
        thread t2(&PrintEvenOdd::printEven, this);

        t1.join();
        t2.join();
    }

    void printOdd() {
        while (count < 100) {
            unique_lock lock(m);
            cv.wait(lock, [this]() { return count & 1; });

            cout << "Fromt Odd: " << count << endl;
            count++;

            lock.unlock();
            cv.notify_all();
        }
    }

    void printEven() {
        while (count < 100) {
            unique_lock lock(m);
            cv.wait(lock, [this]() { return !(count & 1); });

            cout << "Fromt Even: " << count << endl;
            count++;

            lock.unlock();
            cv.notify_all();
        }
    }
};