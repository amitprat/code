#include "../header.h"

/*
https://careercup.com/question?id=5179916190482432

input [2,3,1,4]
output [12,8,24,6]

Multiply all fields except it's own position.

Restrictions:
1. no use of division
2. complexity in O(n)
*/

class MultiplyAllNumbersExceptItself {
   public:
    static void test() {
        vector<int> input = {2, 3, 1, 4};

        MultiplyAllNumbersExceptItself obj;
        auto res1 = obj.multiply(input);
        cout << res1 << endl;
        auto res2 = obj.multiply1(input);
        cout << res2 << endl;
    }

    vector<int> multiply(vector<int> &input) {
        int l = 1, r = 1;
        vector<int> result(input.size());
        for (int i = 0; i < input.size(); i++) {
            result[i] = l;
            l *= input[i];
        }

        for (int i = input.size() - 1; i >= 0; i--) {
            result[i] *= r;
            r *= input[i];
        }

        return result;
    }

    vector<int> multiply1(vector<int> &input) {
        int n = input.size();
        vector<int> front(n);
        vector<int> rear(n);
        vector<int> result(n);

        front[0] = rear[n - 1] = 1;

        for (int i = 1; i < input.size(); i++) {
            front[i] = front[i - 1] * input[i - 1];
        }

        for (int i = input.size() - 2; i >= 0; i--) {
            rear[i] = rear[i + 1] * input[i + 1];
        }

        for (int i = 0; i < n; i++) {
            result[i] = front[i] * rear[i];
        }

        return result;
    }
};