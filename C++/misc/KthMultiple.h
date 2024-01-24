#pragma once
#include "../Header.h"

class KthElement {
public:
    static void test() {
        KthElement obj;
        int n = 20;
        {
            auto res = obj.getMultiples(n);
            cout << to_string(res) << endl;
        }
        {
            auto res = obj.getMultiples1(n);
            cout << to_string(res) << endl;
        }
    }

    vector<int> getMultiples(int n) {
        vector<int> res = { 1 };
        int c3 = 0, c5 = 0, c7 = 0;
        n--;
        while (n--) {
            auto mn = min(3 * res[c3], min(5 * res[c5], 7 * res[c7]));
            res.push_back(mn);
            if (mn == 3 * res[c3]) c3++;
            if (mn == 5 * res[c5]) c5++;
            if (mn == 7 * res[c7]) c7++;
        }

        return res;
    }

    vector<int> getMultiples1(int n) {
        queue<int> q3, q5, q7;
        vector<int> result;
        result.push_back(1);
        q3.push(3);
        q5.push(5);
        q7.push(7);
        n--;

        while (n--) {
            auto mn = min(q3.front(), min(q5.front(), q7.front()));
            result.push_back(mn);
            if (mn == q3.front()) {
                q3.pop();
                q3.push(mn * 3);
                q5.push(mn * 5);
            }
            else if (mn == q5.front()) {
                q5.pop();
                q5.push(mn * 5);
            }
            else if (mn == q7.front()) {
                q7.pop();
            }
            q7.push(mn * 7);
        }

        return result;
    }
};