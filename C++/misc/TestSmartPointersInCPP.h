#pragma once
#include "../header.h"
using namespace std;

class TestSmartPointersInCPP {
    void bar(std::shared_ptr<int>& i,
        std::shared_ptr<string>& s,
        std::shared_ptr<double>& d)
    {
        cout << "Integer " << *i << endl;
        cout << "String " << *s << endl;
        cout << "Double " << *d << endl;
    }
    void test(std::function<void()> func) {
        func();
    }
    thread foo(std::shared_ptr<int>& i,
        std::shared_ptr<string>& s,
        std::shared_ptr<double>& d)
    {
        auto lambda = [this, i, s, d]() mutable {
            bar(i, s, d);
        };

        return std::thread([this, lambda]() {
            std::this_thread::sleep_for(10s);
            test(lambda);
            });
    }

public:
    static void test()
    {
        TestSmartPointersInCPP obj;
        thread t;
        {
            std::shared_ptr<int> i = std::make_shared<int>(10);
            std::shared_ptr<string> s = std::make_shared<string>("10");
            std::shared_ptr<double> d = std::make_shared<double>(10.0);

            t = obj.foo(i, s, d);
            std::this_thread::sleep_for(10s);
        }

        t.join();
    }
};