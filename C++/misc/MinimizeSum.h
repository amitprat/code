#include "../Header.h"

class MinimizeSum {
public:
    static void test() {
        MinimizeSum obj;
        vector<int> arr = { 1, 3, 5, 7, 8, 9,0,0,0 };
        string num = obj.minimize(arr);
        cout << num << endl;
    }

    string minimize(vector<int> arr) {
        sort(arr.begin(), arr.end());
        vector<int> first, second;
        for (int i = 0; i < arr.size(); i++) {
            if (i & 1) {
                first.push_back(arr[i]);
            }
            else {
                second.push_back(arr[i]);
            }
        }
        if (!first.empty() && first[0] == 0) {
            for (int i = 1; i < first.size(); i++) {
                if (first[i] != 0) {
                    swap(first[i], first[0]);
                    break;
                }
            }
        }

        if (!second.empty() && second[0] == 0) {
            for (int i = 1; i < second.size(); i++) {
                if (second[i] != 0) {
                    swap(second[i], second[0]);
                    break;
                }
            }
        }

        cout << to_string(first) << endl;
        cout << to_string(second) << endl;

        return sum(first, second);
    }

    string sum(vector<int>& first, vector<int>& second) {
        string res;
        int carry = 0;
        int i = first.size() - 1, j = second.size() - 1;
        for (; i >= 0 && j >= 0; i--, j--) {
            int num = first[i] + second[j] + carry;
            res += num % 10 + '0';
            carry = num / 10;
        }
        for (; i >= 0; i--) {
            int num = first[i] + carry;
            res += num % 10 + '0';
            carry = num / 10;
        }
        for (; j >= 0; j--) {
            int num = second[j] + carry;
            res += num % 10 + '0';
            carry = num / 10;
        }

        if (carry) res += carry + '0';

        reverse(res.begin(), res.end());

        return res;
    }
};