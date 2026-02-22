#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

class Snowflake {
   public:
    Snowflake(uint32_t workerId)
        : workerId(workerId),
          lastTimestamp(0),
          sequence(0) {}

    uint64_t nextId() {
        lock_guard<mutex> lock(mtx);

        uint64_t timestamp = currentTimeMillis();

        if (timestamp < lastTimestamp) {
            throw runtime_error("Clock moved backwards!");
        }

        if (timestamp == lastTimestamp) {
            sequence = (sequence + 1) & SEQUENCE_MASK;
            if (sequence == 0) {
                timestamp = waitNextMillis(lastTimestamp);
            }
        } else {
            sequence = 0;
        }

        lastTimestamp = timestamp;

        return ((timestamp - EPOCH) << TIMESTAMP_SHIFT) | (static_cast<uint64_t>(workerId) << WORKER_ID_SHIFT) | sequence;
    }

   private:
    static constexpr uint64_t EPOCH = 1704067200000ULL;  // Jan 1, 2024
    static constexpr uint32_t WORKER_ID_BITS = 10;
    static constexpr uint32_t SEQUENCE_BITS = 12;

    static constexpr uint32_t WORKER_ID_SHIFT = SEQUENCE_BITS;
    static constexpr uint32_t TIMESTAMP_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS;

    static constexpr uint32_t SEQUENCE_MASK = (1 << SEQUENCE_BITS) - 1;

    uint32_t workerId;
    uint64_t lastTimestamp;
    uint32_t sequence;

    mutex mtx;

    static uint64_t currentTimeMillis() {
        return duration_cast<milliseconds>(
                   system_clock::now().time_since_epoch())
            .count();
    }

    static uint64_t waitNextMillis(uint64_t lastTs) {
        uint64_t ts;
        do {
            ts = currentTimeMillis();
        } while (ts <= lastTs);
        return ts;
    }
};

// =========================
// Worker Thread (Server)
// =========================
void workerTask(uint32_t workerId, int count) {
    Snowflake generator(workerId);

    for (int i = 0; i < count; i++) {
        uint64_t id = generator.nextId();

        stringstream ss;
        ss << "Thread[" << this_thread::get_id()
           << "] WorkerId=" << workerId
           << " ID=" << id;

        cout << ss.str() << endl;

        this_thread::sleep_for(milliseconds(10));
    }
}

// =========================
// Main (Worker ID Assignment)
// =========================
int main() {
    const int NUM_WORKERS = 4;
    const int IDS_PER_WORKER = 5;

    vector<thread> threads;

    // Main thread assigns worker IDs
    for (uint32_t workerId = 0; workerId < NUM_WORKERS; workerId++) {
        threads.emplace_back(workerTask, workerId, IDS_PER_WORKER);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
