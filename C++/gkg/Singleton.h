#pragma once
#include "../Header.h"

class Singleton {
public:
    static void test() {
        {
            Singleton& obj = Singleton::getInstance();
            obj.doSomething("Say Hello");
        }

        {
            Singleton& obj = Singleton::getInstance();
            obj.doSomething("Say Hi");
        }
    }
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void doSomething(string msg) {
        cout << "Object " << this << " Message = " << msg << endl;
    }

private:
    Singleton() = default;
    ~Singleton() { cout << "Object being destructed"; }
    Singleton(const Singleton&) = delete;
    Singleton operator = (const Singleton&) = delete;
};

class BaseSingleton {
public:
    static void test() {
        {
            Singleton& obj = Singleton::getInstance();
            obj.doSomething("Say Hello");
        }

        {
            Singleton& obj = Singleton::getInstance();
            obj.doSomething("Say Hi");
        }
    }

    BaseSingleton* getInstance() {
        lock_guard<mutex> lock(m);
        return instance;
    }

    void doSomething(string msg) {
        cout << "Object " << this << " Message = " << msg << endl;
    }

private:
    mutex m;
    static BaseSingleton* instance;
    BaseSingleton() = default;
    ~BaseSingleton() = default;
    BaseSingleton(const BaseSingleton&) = delete;
    BaseSingleton operator=(const BaseSingleton&) = delete;
};

BaseSingleton* BaseSingleton::instance = nullptr;