#pragma once
#include "../Header.h"

class Facebook_XsOs {
public:
    static void test() {
        int tests = 0;
        cin >> tests;

        for (int i = 0; i < tests; i++) {
            int n;
            cin >> n;
            unordered_map<int, int> rows;
            unordered_map<int, int> cols;
            for (int j = 0; j < n; j++) {
                string str;
                cin >> str;
                int xs = 0;
                bool hasO = false;
                int n = str.length();
                for (int k = 0; k < n; k++) {
                    if (str[k] == 'O') {
                        hasO = true;
                        cols[k] = -1;
                    }
                    else if (str[k] == 'X') {
                        if (cols[k] != -1) cols[k]++;
                        xs++;
                    }
                }
                if (hasO) rows.erase(j);
                else rows[j] = n - xs;
            }

            int mnX = INT_MAX;
            int ways = 0;

            for (auto e : rows) {
                if (e.second < mnX) {
                    mnX = e.second;
                    ways = 1;
                }
                else if (e.second == mnX) {
                    ways++;
                }
            }

            for (auto e : cols) {
                if (e.second == -1) continue;
                if (n - e.second < mnX) {
                    mnX = n - e.second;
                    ways = 1;
                }
                else if (n - e.second == mnX) {
                    ways++;
                }
            }

            cout << mnX << " " << ways << endl;
        }
    }
};