#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define BUFFER_SIZE 4 

int buffer[BUFFER_SIZE];
int count = 0;
mtx_t mutex;
cnd_t cv;

int producer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        mtx_lock(&mutex);
        while (count == BUFFER_SIZE) {
            cnd_wait(&cv, &mutex);
        }
        buffer[count] = i;
        count++;
        cnd_signal(&cv);
        mtx_unlock(&mutex);
    }
    return 0;
}

int consumer(void *arg) {
    while (1) {
        mtx_lock(&mutex);
        while (count == 0) {
            cnd_wait(&cv, &mutex);
        }
        int message = buffer[count - 1];
        count--;
        cnd_signal(&cv);
        mtx_unlock(&mutex);

        printf("Received message: %d\n", message);
    }
}

int main() {
    mtx_init(&mutex, mtx_plain);
    cnd_init(&cv);

    thrd_t producer_thread, consumer_thread;

    thrd_create(&producer_thread, producer, NULL);
    thrd_create(&consumer_thread, consumer, NULL);

    thrd_join(producer_thread, NULL);
    thrd_join(consumer_thread, NULL);

    mtx_destroy(&mutex);
    cnd_destroy(&cv);

    return 0;
}

//--------------
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::queue<int> message_queue;
std::condition_variable cv;

void producer() {
    for (int i = 0; i < 4; i++) {
        std::lock_guard<std::mutex> lock(mutex);
        message_queue.push(i);
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, []{ return !message_queue.empty(); });
        int message = message_queue.front();
        message_queue.pop();
        lock.unlock();

        std::cout << "Received message: " << message << std::endl;
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}