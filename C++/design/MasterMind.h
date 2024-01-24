#pragma once
#include "../header.h"

class MasterMind {
public:
    static void test() {
        MasterMind obj;
        int hits = 0;
        int phits = 0;
        string solution = "RGBY";
        string guess = "GRYB";
        obj.calculate(solution, guess, hits, phits);
        cout << "Hits:" << hits << ", PHits:" << phits << endl;
    }

    void calculate(string sol, string guess, int& hits, int& phits) {
        vector<int> map(4, 0);
        for (int i = 0; i < sol.length(); i++) {
            if (sol[i] == guess[i]) hits++;
            else map[code(sol[i])]++;
        }
        for (auto& ch : guess) {
            if (map[code(ch)] > 0) {
                phits += map[code(ch)];
                map[code(ch)]--;
            }
        }
    }
    int code(char ch) {
        switch (ch) {
            case 'R':
                return 0;
            case 'Y':
                return 1;
            case 'G':
                return 2;
            case 'B':
                return 3;
        }
        return -1;
    }
};