#include "../header.h"

/*
https://www.careercup.com/question?id=14622668

Implement a thread-safe Blocking queue in C/C++(POSIX) or Java
*/
template <class T>
class BlockingQueue {
    queue<T> q;
    const int limit = 10;
    atomic<bool> flag;

    // https://stackoverflow.com/questions/244316/reader-writer-locks-in-c
    using Lock = shared_mutex;
    using WriteLock = unique_lock<Lock>;
    using ReadLock = shared_lock<Lock>;
    Lock lock;

   public:
    void push(T item) {
        flag.wait(q.size() != limit);

        WriteLock writeLock(lock);

        cout << "Pushed element: " << item << endl;
        q.push(item);

        flag.notify_all();
    }

    T top() {
        flag.wait(!q.empty());

        ReadLock readLock(lock);

        auto item = q.front();

        return item;
    }

    T pop() {
        flag.wait(!q.empty());

        WriteLock writeLock(lock);

        auto item = q.front();
        q.pop();
        cout << "Popped element: " << item << endl;

        return item;
    }
};

class BlockingQueueTester {
   public:
    static void test() {
        BlockingQueue<int> queue;
        thread publisher([&]() {
            for (int i = 0; i < 100; i++) {
                queue.push(i);
                this_thread::sleep_for(chrono::seconds(1));
            }
        });

        cout << "Waiting for subscribers to consume" << endl;
        this_thread::sleep_for(chrono::seconds(10));

        cout << "Subscriber started" << endl;
        thread subscriber([&]() {
            for (int i = 0; i < 100; i++) {
                cout << queue.pop() << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        });

        publisher.join();
        subscriber.join();
    }
};