#pragma once
#include <atomic>

/*
Given four resources A1, A2, B1 , B2. Such that Thread T1 and Thread T2 operates on A1, A2 and B1, B2 respectively.
How will you ensure the order of execution is A1-B1-A2-B2 ?
*/

#include "../header.h"

class PrintA1B1A2B2 {
    mutex m;
    condition_variable cv1, cv2, cv3, cv4;
    int val = 1;

   public:
    static void test() {
        PrintA1B1A2B2 obj;
        obj.print();
    }

    void print() {
        thread t1([this]() {
            printA1();
            printA2();
        });

        thread t2([this]() {
            printB1();
            printB2();
        });

        t1.join();
        t2.join();
    }
    void printA1() {
        unique_lock lock(m);
        cv1.wait(lock, [this]() { return val == 1; });

        cout << "A1" << endl;
        val++;

        cv2.notify_all();
    }

    void printB1() {
        unique_lock lock(m);
        cv2.wait(lock, [this]() { return val == 2; });

        cout << "B1" << endl;
        val++;

        cv3.notify_all();
    }

    void printA2() {
        unique_lock lock(m);
        cv3.wait(lock, [this]() { return val == 3; });

        cout << "A2" << endl;
        val++;

        cv4.notify_all();
    }

    void printB2() {
        unique_lock lock(m);
        cv4.wait(lock, [this]() { return val == 4; });

        cout << "B2" << endl;
        val = 1;

        cv1.notify_all();
    }
};

class PrintA1B1A2B2InLoop {
   private:
    mutex m;
    condition_variable cv1, cv2, cv3, cv4;
    atomic<int> limit = 20;
    int val = 0;

   public:
    static void test() {
        PrintA1B1A2B2InLoop obj;
        obj.print();
    }

    void print() {
        thread t1([this]() { printA1A2(); });
        thread t2([this]() { printB1B2(); });

        t1.join();
        t2.join();
    }

    void printA1A2() {
        while (limit > 0) {
            printStr("A1", 0, cv1, cv2);
            printStr("A2", 2, cv3, cv4);
        }
    }

    void printB1B2() {
        while (limit > 0) {
            printStr("B1", 1, cv2, cv3);
            printStr("B2", 3, cv4, cv1);
        }
    }

    void printStr(string str, int expected, condition_variable& cur, condition_variable& next) {
        unique_lock lock(m);
        cur.wait(lock, [this, expected]() { return val == expected; });

        val = (val + 1) % 4;
        if (limit > 0) {
            cout << str;
            limit--;
        }

        next.notify_one();
    }
};

class PrintA1B1A2B2InLoopUsingAtomic2 {
   private:
    atomic_flag a1, b1, a2, b2;
    const int max = 10;
    atomic<int> index = 0;

   private:
    void print(atomic_flag& cur, atomic_flag& next, string str) {
        while (index < max) {
            // wait for cur to set to true. it compares against old state=false
            cur.wait(false);

            // this is exit afte exactly max iterations without partial printing.
            // If we exceed max at any point, then set all flags and notify them to exit.
            if (index >= max) {
                next.test_and_set();
                next.notify_one();
                break;
            }

            // print and if it is end of string 'B2', then increase the index count.
            cout << str;
            if (str == "B2") {
                cout << endl;
                index++;
            }

            // clear the current flag, set next flag and notify it to resume.
            cur.clear();
            next.test_and_set();
            next.notify_one();
        }
    }

   public:
    void printStr() {
        auto fut1 = async(&PrintA1B1A2B2InLoopUsingAtomic2::print, this, std::ref(a1), std::ref(b1), "A1");
        auto fut2 = async(&PrintA1B1A2B2InLoopUsingAtomic2::print, this, std::ref(b1), std::ref(a2), "B1");
        auto fut3 = async(&PrintA1B1A2B2InLoopUsingAtomic2::print, this, std::ref(a2), std::ref(b2), "A2");
        auto fut4 = async(&PrintA1B1A2B2InLoopUsingAtomic2::print, this, std::ref(b2), std::ref(a1), "B2");

        a1.test_and_set();

        fut1.get();
        fut2.get();
        fut3.get();
        fut4.get();
    }

   public:
    static void test() {
        PrintA1B1A2B2InLoopUsingAtomic2 obj;
        obj.printStr();
    }
};