#pragma once
#include "../Header.h"

class GenerateBinary {
public:
    static void test() {
        int n = 7;
        vector<string> res = generate(n);
        cout << to_string(res) << endl;
    }

    static vector<string> generate(int n) {
        vector<string> res;

        queue<string> q;
        q.push("1");

        while (n--) {
            auto f = q.front(); q.pop();
            res.push_back(f);

            q.push(f + "0");
            q.push(f + "1");
        }

        return res;
    }
};