#include "../header.h"
#include <chrono>
#include <stop_token>
using namespace std;

class Cancellation {
   public:
    static void test() {
        std::jthread t(worker);  // Automatically passes stop_token to worker

        std::this_thread::sleep_for(std::chrono::seconds(3));
        t.request_stop();  // Signal cancellation
    }

   public:
    void worker(std::stop_token st) {
        int i = 0;
        while (!st.stop_requested()) {
            std::cout << "Working... " << i++ << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "Cancellation requested, exiting thread.\n";
    }
};