#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <string.h>
using namespace std;

class ThreadPrint3SubSeq
{
private:
    mutex m;
    std::condition_variable cv;
    int count = 0;

public:
    static void test()
    {
        ThreadPrint3SubSeq obj;
        int max = 100;
        obj.printSeq(max);
    }

    void printSeq(int max)
    {
        thread printOne([this, max]() {
            while (count <= max) {
                unique_lock<mutex> lock(m);
                cv.wait(lock, [this]() {return count % 3 == 0; });
                cout << "1" << " ";
                count++;
                cv.notify_one();
            }
            });

        thread printTwo([this, max]() {
            while (count <= max) {
                unique_lock<mutex> lock(m);
                cv.wait(lock, [this]() {return count % 3 == 1; });
                cout << "2" << " ";
                count++;
                cv.notify_one();
            }
            });

        thread printThree([this, max]() {
            while (count <= max) {
                unique_lock<mutex> lock(m);
                cv.wait(lock, [this]() {return count % 3 == 2; });
                cout << "3" << " ";
                count++;
                cv.notify_one();
            }
            });

        printOne.join();
        printTwo.join();
        printThree.join();
    }
};