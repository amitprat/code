#pragma once
#include "../header.h"

class Semaphore {
    mutex m;
    unordered_map<int, pair<condition_variable*, bool>> cvs;

   public:
    Semaphore(int n) {
        for (int i = 0; i < n; i++) {
            cvs[i] = {new condition_variable(), false};
        }
    }
    Semaphore() {
    }
    void init(int id, bool val) {
        cvs[id] = {new condition_variable(), val};
    }
    void wait(int id) {
        unique_lock lock(m);
        cvs[id].first->wait(lock, [&]() { return cvs[id].second; });
        cvs[id].second = false;
    }
    void post(int id) {
        {
            unique_lock lock(m);
            cvs[id].second = true;
        }
        cvs[id].first->notify_all();
    }

   public:
    static void test() {
        Semaphore s;
        s.init(1, true);
        s.init(2, false);
        s.init(3, false);
        int count = 0, limit = 30;

        thread t1([&s, count, limit]() mutable {
            while (count < limit) {
                s.wait(1);
                cout << "1" << " ";
                count++;
                s.post(2);
            }
        });

        thread t2([&s, count, limit]() mutable {
            while (count < limit) {
                s.wait(2);
                cout << "2" << " ";
                s.post(3);
            }
        });

        thread t3([&s, count, limit]() mutable {
            while (count < limit) {
                s.wait(3);
                cout << "3" << " ";
                s.post(1);
            }
        });

        t1.join();
        t2.join();
        t3.join();
    }
};