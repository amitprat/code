#include "../header.h"

class PrintEvenOdds {
    int n = 100;
    condition_variable cv;
    mutex mtx;
    bool isEven = true;

   public:
    static void test() {
        PrintEvenOdds obj;
        obj.print();
    }

    void print() {
        thread t1([this]() { this->printEven(); });
        thread t2([this]() { this->printOdd(); });

        t1.join();
        t2.join();
    }

    void printEven() {
        for (int i = 0; i < n; i += 2) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() { return isEven; });
            cout << "Even: " << i << endl;
            isEven = false;
            cv.notify_one();
        }
    }

    void printOdd() {
        for (int i = 1; i < n; i += 2) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() { return !isEven; });
            cout << "Odd: " << i << endl;
            isEven = true;
            cv.notify_one();
        }
    }
};