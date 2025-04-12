#pragma once
#include "../header.h"

class ReaderWriter1 {
    using SharedLock = std::shared_mutex;
    using WriterLock = std::unique_lock<SharedLock>;
    using WriterLock2 = std::lock_guard<SharedLock>;
    using ReaderLock = std::shared_lock<SharedLock>;

    using Key = string;
    using Value = string;
    using SharedUnSafeContainer = unordered_map<string, string>;

    SharedLock myLock;
    SharedUnSafeContainer container;

    string ReadFunction(string key) {
        ReaderLock r_lock(myLock);
        if (!container.count(key)) return string();

        return container[key];
    }

    void WriteFunction(string key, string value) {
        WriterLock w_lock(myLock);

        container[key] = value;
    }

   public:
    static void test() {
        ReaderWriter1 obj;
        vector<future<void>> futures;

        // writers
        for (int workerCount = 0; workerCount <= 10; workerCount++) {
            futures.push_back(std::async(std::launch::async, [&obj, workerCount]() {
                for (int i = workerCount * 100; i < workerCount * 100 + 100; i++) {
                    string key = format("{0}{1}", "key", i);
                    string val = format("{0}{1}", "val", i);

                    obj.WriteFunction(key, val);
                    cout << "Write value: " << key << ", " << val << endl;
                }
            }));
        }

        // readers
        for (int workerCount = 0; workerCount <= 10; workerCount++) {
            futures.push_back(std::async(std::launch::async, [&obj, workerCount]() {
                for (int i = workerCount * 100; i < workerCount * 100 + 100; i++) {
                    string key = format("{0}{1}", "key", i);

                    string val = obj.ReadFunction(key);
                    cout << "Read value: " << key << ", " << val << endl;
                }
            }));
        }

        for (auto& fut : futures) {
            fut.get();
        }
    }
};

class ReaderWriter2 {
    unordered_map<string, int> teleBook;
    shared_timed_mutex m;

   public:
    void printNumber(string name) {
        shared_lock lock(m);
        cout << "Reading Book: " << name << "=" << teleBook[name] << endl;
    }

    void addToTeleBook(string name, int year) {
        unique_lock lock(m);
        cout << "Upserting record : " << name << ", " << year << endl;
        teleBook[name] = year;
    }

    void readWrite() {
        std::cout << std::endl;

        std::thread reader1([this] { printNumber("Scott"); });
        std::thread reader2([this] { printNumber("Ritchie"); });
        std::thread w1([this] { addToTeleBook("Scott", 1968); });
        std::thread reader3([this] { printNumber("Dijkstra"); });
        std::thread reader4([this] { printNumber("Scott"); });
        std::thread w2([this] { addToTeleBook("Bjarne", 1965); });
        std::thread reader5([this] { printNumber("Scott"); });
        std::thread reader6([this] { printNumber("Ritchie"); });
        std::thread reader7([this] { printNumber("Scott"); });
        std::thread reader8([this] { printNumber("Bjarne"); });

        reader1.join();
        reader2.join();
        reader3.join();
        reader4.join();
        reader5.join();
        reader6.join();
        reader7.join();
        reader8.join();
        w1.join();
        w2.join();

        std::cout << std::endl;

        std::cout << "\nThe new telephone book" << std::endl;
        for (auto teleIt : teleBook) {
            std::cout << teleIt.first << ": " << teleIt.second << std::endl;
        }

        std::cout << std::endl;
    }

   public:
    static void test() {
        ReaderWriter2 obj;
        obj.readWrite();
    }
};