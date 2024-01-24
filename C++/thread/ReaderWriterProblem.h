#pragma once
#include "../header.h"

class ReaderWriter {
    unordered_map<string, int> teleBook;
    shared_timed_mutex m;
public:
    void printNumber(string name) {
        shared_lock lock(m);
        cout << "Reading Book: " << name << "=" << teleBook[name] << endl;
        lock.unlock();
    }

    void addToTeleBook(string name, int year) {
        unique_lock lock(m);
        cout << "Upserting record : " << name << ", " << year << endl;
        teleBook[name] = year;
        lock.unlock();
    }

    static void test() {
        ReaderWriter obj;
        obj.readWrite();
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
};