#include "../header.h"

class Ranges {
   public:
    static void test() {
        vector<int> arr = {1, 2, 3, 4, 5};
        auto evenNumbers = arr | views::filter([](int i) { return i % 2 == 0; }) | views::transform([](int i) { return to_string(i); });
        cout << evenNumbers << endl;
    }
};