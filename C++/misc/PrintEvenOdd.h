#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class PrintEvenOdd
{
private:
    mutex m;
    std::condition_variable cv;
    int count = 0;

    void printEven(int mx)
    {
        while (count < mx) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]() {return !(count & 1); });
            cout << count++ << " ";
            cv.notify_one();
        }
    }

    void printOdd(int mx)
    {
        while (count < mx) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]() {return count & 1; });
            cout << count++ << " ";
            cv.notify_one();
        }
    }

public:
    static void test(vector<int> v)
    {
        PrintEvenOdd obj;

        for (auto i : v) {
            cout << "Output = ";
            obj.print(i);
            cout << endl;
        }
    }

    void print(int mx)
    {
        thread oddPrintingThread(&PrintEvenOdd::printOdd, this, mx);
        thread evenPrintingThread(&PrintEvenOdd::printEven, this, mx);

        oddPrintingThread.join();
        evenPrintingThread.join();
    }
};