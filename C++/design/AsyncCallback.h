/*
Start Execute
Rest Scheduled task to service
Waiting for task to be done!
Start Execute
Rest Scheduled task to service
Waiting for task to be done!
Start Execute
Rest Scheduled task to service
Waiting for task to be done!
Start Execute
Rest Scheduled task to service
Waiting for task to be done!
Sum of (1,2) = 3
Sum of (10,20) = 30
Sum of (100,200) = 300
Sum of (1000,2000) = 3000
*/

#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <functional>
#include <future>
#include "AsyncState.h"
using namespace std;

namespace AsyncCallbackImpl {
    using Result = int;
    class Service
    {
    private:
        AsyncState<Result> asynState;
        thread t;

    public:
        ~Service() { t.join(); }
        void Init(Caller caller, Callback callback, State state)
        {
            asynState.Init(caller, callback, state);
        }
        void execute(int a, int b)
        {
            cout << "Waiting for task to be done!" << endl;
            t = std::thread([=]() {
                std::this_thread::sleep_for(std::chrono::seconds(10));
                Result r = a + b;
                asynState.Complete(r);
                });
        }
    };

    class Rest
    {
    private:
        Service service;
        AsyncState<Result> asynState;

        void after_execute(IAsyncState* result)
        {
            asynState.Complete(((AsyncState<Result>*)result)->GetResult());
        }
        DEFINE_STATIC_CALLBACK(Rest, after_execute);

    public:
        void Init(Caller caller, Callback callback, State state)
        {
            asynState.Init(caller, callback, state);
        }
        void execute(int a, int b)
        {
            if (a < 0) asynState.Complete(-1);
            if (b < 0) asynState.Complete(-1);

            cout << "Rest Scheduled task to service" << endl;
            service.Init(this, STATIC_CALLBACK(after_execute), nullptr);
            service.execute(a, b);
        }
    };

    class Client
    {
    private:
        Rest rest;
        std::promise<Result> promise;

        void after_execute(IAsyncState* result)
        {
            promise.set_value(((AsyncState<Result>*)result)->GetResult());
        }
        DEFINE_STATIC_CALLBACK(Client, after_execute);

    public:
        future<Result> test(int a, int b)
        {
            cout << "Start Execute" << endl;
            rest.Init(this, STATIC_CALLBACK(after_execute), nullptr);
            rest.execute(a, b);
            return promise.get_future();
        }
    };

    class Test
    {
    public:
        static void test()
        {
            Client client1, client2, client3, client4;
            auto f1 = client1.test(1, 2);
            auto f2 = client2.test(10, 20);
            auto f3 = client3.test(100, 200);
            auto f4 = client4.test(1000, 2000);
            cout << "Sum of (1,2) = " << f1.get() << endl;
            cout << "Sum of (10,20) = " << f2.get() << endl;
            cout << "Sum of (100,200) = " << f3.get() << endl;
            cout << "Sum of (1000,2000) = " << f4.get() << endl;
        }
    };
}