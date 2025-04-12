#pragma once
#include "../header.h"

class ThreadPrint3SubSeq {
   private:
    mutex m;
    std::condition_variable cv;
    int count = 0;

   public:
    static void test() {
        ThreadPrint3SubSeq obj;
        int max = 100;
        obj.printSeq(max);
    }

    void printSeq(int max) {
        thread printOne([this, max]() {
            while (count <= max) {
                unique_lock<mutex> lock(m);
                cv.wait(lock, [this]() { return count % 3 == 0; });
                cout << "1" << " ";
                count++;
                cv.notify_all();
            }
        });

        thread printTwo([this, max]() {
            while (count <= max) {
                unique_lock<mutex> lock(m);
                cv.wait(lock, [this]() { return count % 3 == 1; });
                cout << "2" << " ";
                count++;
                cv.notify_all();
            }
        });

        thread printThree([this, max]() {
            while (count <= max) {
                unique_lock<mutex> lock(m);
                cv.wait(lock, [this]() { return count % 3 == 2; });
                cout << "3" << " ";
                count++;
                cv.notify_all();
            }
        });

        printOne.join();
        printTwo.join();
        printThree.join();
    }
};

class ThreadPrint3SubSeqOptimized {
   private:
    mutex m;
    std::condition_variable cv;
    int count = 1;

   public:
    static void test() {
        ThreadPrint3SubSeqOptimized obj;
        int max = 100;
        vector<int> output;
        obj.printSeq(max, output);
        assert(isValid(output));
        println("Output: {0}", output);
    }

    static bool isValid(const vector<int>& out) {
        int next = 1;
        for (auto& e : out) {
            if (e != next) return false;
            next = (next + 1) % 3 == 0 ? 3 : (next + 1) % 3;
        }

        return true;
    }

    void printSeq(int max, vector<int>& output) {
        thread t1([this, max, &output]() { printNumbers(max, output, 1); });
        thread t2([this, max, &output]() { printNumbers(max, output, 2); });
        thread t3([this, max, &output]() { printNumbers(max, output, 3); });

        t1.join();
        t2.join();
        t3.join();
    }

    void printNumbers(int max, vector<int>& output, int expected) {
        while (count <= max) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this, expected]() { return count % 3 == expected % 3; });
            output.push_back(expected);
            count++;
            cv.notify_all();
        }
    }
};

class ThreadPrint3SubSeqUsingAtomicFlag {
   private:
    atomic_flag flag1, flag2, flag3;
    atomic<int> count = 1;
    const int maxCount = 100;

   public:
    void print(int thread_id, atomic_flag& cur_flag, atomic_flag& next_flag, vector<int>& out) {
        while (count < maxCount) {
            cur_flag.wait(false);

            out.push_back(count % 3 == 0 ? 3 : count % 3);
            count++;
            cur_flag.clear();

            next_flag.test_and_set(std::memory_order_acquire);
        }
    }

    void printSeq(vector<int>& output) {
        flag1.test_and_set(std::memory_order_acquire);

        thread t1([this, &output]() { print(1, std::ref(flag1), std::ref(flag2), output); });
        thread t2([this, &output]() { print(2, std::ref(flag2), std::ref(flag3), output); });
        thread t3([this, &output]() { print(3, std::ref(flag3), std::ref(flag1), output); });

        t1.join();
        t2.join();
        t3.join();
    }

   public:
    static void test() {
        ThreadPrint3SubSeqUsingAtomicFlag obj;
        vector<int> output;
        obj.printSeq(output);
        assert(isValid(output));
        println("Output: {0}", output);
    }

    static bool isValid(const vector<int>& out) {
        int next = 1;
        for (auto& e : out) {
            if (e != next) return false;
            next = (next + 1) % 3 == 0 ? 3 : (next + 1) % 3;
        }

        return true;
    }
};

class ThreadPrint3SubSeqUsingBinarySemaphore {
   private:
    binary_semaphore sem1{1} /*unlocked*/, sem2{0}, sem3{0} /*locked*/;
    atomic<int> count = 1;
    const int maxCount = 100;

   public:
    void printSeq(vector<int>& result) {
        auto run1 = std::async(std::launch::async, [this, &result]() { print(result, sem1, sem2); });
        auto run2 = std::async(std::launch::async, [this, &result]() { print(result, sem2, sem3); });
        auto run3 = std::async(std::launch::async, [this, &result]() { print(result, sem3, sem1); });

        run1.get();
        run2.get();
        run3.get();
    }

    void print(vector<int>& result, binary_semaphore& cur_sem, binary_semaphore& next_sem) {
        while (count < maxCount) {
            cur_sem.acquire();

            result.push_back(count % 3 == 0 ? 3 : count % 3);
            count++;

            next_sem.release();
        }
    }

   public:
    static void test() {
        ThreadPrint3SubSeqUsingBinarySemaphore obj;
        vector<int> output;
        obj.printSeq(output);
        assert(isValid(output));
        println("Output: {0}", output);
    }

    static bool isValid(const vector<int>& out) {
        int next = 1;
        for (auto& e : out) {
            if (e != next) return false;
            next = (next + 1) % 3 == 0 ? 3 : (next + 1) % 3;
        }

        return true;
    }
};