#pragma once
#include "../Header.h"

class GenerateCombinations {
public:
    static void test() {
        int n = 4;
        vector<int> res;
        generate(1, n, res);
        cout << endl;

        res.clear();
        generate1(1, n, res);
        cout << endl;

        res.clear();
        generate2(n, n - 1, res);
        cout << endl;
    }

    static void generate1(int s, int n, vector<int> res) {
        if (n == 0) {
            cout << to_string(res) << ", ";
            return;
        }
        if (s > n || n < 0) return;

        generate(s + 1, n, res);
        res.push_back(s);
        generate(s, n - s, res);
    }

    static void generate(int s, int n, vector<int> res) {
        if (n == 0) {
            cout << to_string(res) << ", ";
            return;
        }
        for (int e = s; e <= n; e++) {
            res.push_back(e);
            generate(e, n - e, res);
            res.pop_back();
        }
    }

    static void generate2(int n, int upper, vector<int> res) {
        if (n < 0) return;
        if (n == 0) {
            cout << to_string(res) << ", ";
            return;
        }

        for (int e = 1; e <= upper; e++) {
            res.push_back(e);
            generate2(n - e, e, res);
            res.pop_back();
        }
    }
};