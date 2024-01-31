#include <execution>

#include "../header.h"

class ParallelExecution {
   public:
    static void test() {
        array<string, 3> arr = {"amit", "pratap", "singh"};
        // for_each(execution::par, arr.begin(), arr.end(), [](const auto& str) {
        //     cout << str << " ";
        // });
        cout << endl;
    }
};