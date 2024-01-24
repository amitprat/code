#pragma once
#include "../header.h"

class PrintOneTwoThree {
    int limit;
    mutex m;
    condition_variable cv1, cv2, cv3;
    int count = 1;
public:
    PrintOneTwoThree(int limit) : limit(limit) {}
    static void test() {
        PrintOneTwoThree obj(100);
        obj.print();
    }

    void print() {
        thread t1([this]() {this->printOne(); });
        thread t2([this]() {this->printTwo(); });
        thread t3([this]() {this->printThree(); });

        t1.join();
        t2.join();
        t3.join();
    }

    void printOne() {
        while (count < limit) {
            unique_lock lock(m);
            cv1.wait(lock);
            cout << "PrintOne: " << count << endl;
            count++;
            lock.unlock();
            cv2.notify_one();
        }
    }

    void printTwo() {
        while (count < limit) {
            unique_lock lock(m);
            cv2.wait(lock);
            cout << "printTwo: " << count << endl;
            count++;
            lock.unlock();
            cv3.notify_one();
        }
    }

    void printThree() {
        while (count < limit) {
            unique_lock lock(m);
            cv3.wait(lock);
            cout << "printThree: " << count << endl;
            count++;
            lock.unlock();
            cv1.notify_one();
        }
    }
};