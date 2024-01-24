#include "../header.h"

class Find2OddElements {
   public:
    static void test() {
        vector<int> arr = {4, 2, 4, 5, 2, 3, 3, 1};
        Find2OddElements obj;
        auto res = obj.find2OffElements(arr);
        cout << "Two odd elements: " << res << endl;
    }

    pair<int, int> find2OffElements(vector<int> arr) {
        int val = 0;
        for (auto &i : arr)
            val ^= i;

        int lastSetBit = val & ~(val - 1);

        int first = 0;
        int second = 0;
        for (auto &i : arr) {
            if (lastSetBit & i) {
                first ^= i;
            } else {
                second ^= i;
            }
        }

        return {first, second};
    }
};