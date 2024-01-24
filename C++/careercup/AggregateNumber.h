#include "../header.h"

/*
A number is aggreate number if it is formed by adding previous 2 digits.
For example: 112358
1+1 = 2
1+2 = 3
2+3 = 5
3+5 = 8
*/
class AggregateNumber {
   public:
    static void test() {
        vector<int> numbers = {112358, 122436, 1299111210, 112112224, 222442, 1, 12, 123, 1234};

        AggregateNumber obj;
        for (auto num : numbers) {
            auto res = obj.isAggregate(num);
            cout << format("num:{} is aggregate {}", num, res) << endl;
        }
    }

    bool isAggregate(int num) {
        string numStr = std::to_string(num);
        int n = numStr.length();

        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= n / 2; j++) {
                if (isAggregate(numStr, i, j, n)) return true;
            }
        }

        return false;
    }

    bool isAggregate(string num, int i, int j, int n) {
        string first = num.substr(0, i);
        string second = num.substr(i, j);

        string combined = first + second;
        while (combined.length() < num.length()) {
            string third = std::to_string(stoi(first) + stoi(second));
            combined += third;

            first = second;
            second = third;
        }

        return combined.length() == num.length() && combined == num;
    }
};