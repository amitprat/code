#pragma once
#include "../header.h"

class AtomicFlagExample {
   public:
    static void test() {
        std::atomic_flag flag;
        cout << "Value: " << flag.test() << endl;
        flag.test_and_set(std::memory_order_acquire);
        cout << "Value: " << flag.test() << endl;
        flag.clear();
        cout << "Value: " << flag.test() << endl;

        thread t([&flag]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            flag.test_and_set(std::memory_order_acquire);
            flag.notify_one();
            cout << "Thread set the value to true" << endl;
        });

        cout << "Waiting for thread to set" << endl;
        flag.wait(false);

        cout << "Value set to true: " << flag.test() << endl;

        t.join();
    }
};