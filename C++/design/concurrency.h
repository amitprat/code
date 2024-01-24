#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>
using namespace std;

namespace concurrency {
    class Storage
    {
    private:
        vector<int> v;
        mutex mut;

    public:
        void generate(int count)
        {
            lock_guard<mutex> lock(mut);
            for (int i = 0; i < count; i++)
            {
                v.push_back(i);
            }
        }

        vector<int> fetch(int count)
        {
            lock_guard<mutex> lock(mut);
            vector<int> res = vector<int>(v.begin(), v.begin() + count);
            v.assign(v.begin() + count, v.end());

            return res;
        }

        bool empty() const { return v.empty(); }
    };

    void print(vector<int> v)
    {
        for (auto i : v)
            cout << i << " ";
        cout << endl;
    }

    void testStore(Storage& store, bool test)
    {
        if (test)
        {
            while (!store.empty())
            {
                auto res = store.fetch(100);
                print(res);
            }
        }
    }

    class Executor
    {
    private:
        thread* realWorker = nullptr;

        void listAsync(function<void()> orgCallback)
        {
            realWorker = new thread([this, orgCallback]() {
                this_thread::sleep_for(chrono::seconds(1));
                listAsyncCallback(orgCallback);
                });
        }
        void listAsyncCallback(function<void()> orgCallback)
        {
            doRealWorkAsync(orgCallback);
        }
        void doRealWorkAsync(function<void()> orgCallback)
        {
            realWorker = new thread([this, orgCallback]() {
                this_thread::sleep_for(chrono::seconds(1));
                workDone(orgCallback);
                });
        }
        void workDone(function<void()> orgCallback)
        {
            executeDone(orgCallback);
        }

    public:
        Executor(thread* t) :realWorker(t) {}
        void executeAsync(function<void()> callback)
        {
            listAsync(callback);
        }
        void executeDone(function<void()> orgCallback)
        {
            orgCallback();
        }
    };

    class Processor
    {
    private:
        vector<thread>& workers;
        Executor executor;

        void workAsync()
        {
            cout << "Work Async started" << endl;
            executor.executeAsync(bind(&Processor::workDone, this));
        }

        void workDone()
        {
            cout << "Work async done" << endl;
        }

    public:
        Processor(thread& realWorker, vector<thread>& workers) : executor(realWorker), workers(workers)
        {
        }
        void process(Storage& store)
        {
            cout << "Starting process" << endl;
            workers.push_back(thread(&Processor::workAsync, this));
        }
    };

    int test()
    {
        Storage store;
        store.generate(1000);
        testStore(store, false);

        thread realWorker;
        vector<thread> workers;
        Processor processor(realWorker, workers);
        processor.process(store);

        realWorker.join();
        for (auto& w : workers) w.join();

        return 0;
    }
}