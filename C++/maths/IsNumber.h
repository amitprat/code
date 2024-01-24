#pragma once
#include "../header.h"

class IsNumber {
public:
    enum class State {
        Invalid,
        Num,
        Dot,
        Exp,
        Sign
    };
    static void test() {
        IsNumber obj;
        vector<string> inputs = {
            "0",
            "0.0",
            "+1",
            "-1",
            "+1.0",
            "+132423.12414",
            "10e-10",
            "10e10",
            "+10e-10",
            "",
            "sdf",
            "1.1.1",
            "1.",
            "1,",
            ".12.12",
            "e-10",
                        "+-",
            "*2021341.23.2.34.`2..12",
            "+-1.1.1",
            "+-1.",
            "1,-1.",
            "...",
            ".."
        };

        for (auto input : inputs) {
            cout << "Is Valid (" + input + ") = " << obj.isNumberMap(input) << endl;
        }

        cout << "Random Testing..." << endl;

        string allowChars = "+-.e0123456789";
        int l = allowChars.length();
        srand(time(nullptr));
        for (int i = 0; i < 50; i++) {
            string cur;
            for (int i = 0; i < rand() % 10; i++) {
                int r = rand() % l;
                cur += allowChars[r];
            }
            cout << "Is Valid (" + cur + ") = " << obj.isNumberMap(cur) << endl;
        }
    }

    bool isNumber(string input) {
        int i = 0;
        bool end = false;
        bool allowSign = true;
        bool allowDot = true;
        bool allowExp = true;
        for (int i = 0; i < input.length(); i++) {
            switch (input[i]) {
                case '+':
                case '-':
                    if (!allowSign) return false;
                    allowSign = false;
                    end = false;
                    break;
                case '.':
                    if (!allowDot || !end) return false;
                    allowDot = false;
                    end = false;
                    break;
                case 'e':
                    if (!allowExp || !end) return false;
                    allowExp = false;
                    allowSign = true;
                    end = false;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    end = true;
                    break;
                default:
                    return false;
            }
        }
        return end;
    }

    bool isNumberIfLadder(string input) {
        int i = 0;
        bool end = false;
        bool allowSign = true;
        bool allowDot = false;
        bool allowExp = false;
        bool isDotSeen = false;
        bool isExpSeen = false;
        for (int i = 0; i < input.length(); i++) {
            char ch = input[i];
            if (allowSign && (ch == '+' || ch == '-')) {
                allowSign = false;
                allowDot = false;
                end = false;
            }
            else if (allowDot && ch == '.') {
                allowDot = false;
                end = false;
                isDotSeen = true;
            }
            else if (allowExp && ch == 'e') {
                allowExp = false;
                allowSign = true;
                allowDot = false;
                end = false;
                isExpSeen = false;
            }
            else if (ch >= '0' && ch <= '9') {
                if (!isExpSeen) allowExp = true;
                allowSign = false;
                if (!isDotSeen) allowDot = true;
                end = true;
            }
            else {
                return false;
            }
        }
        return end;
    }

    bool isNumberMap(string input) {
        vector<vector<State>> validStates = {
            {State::Num},
            {State::Num,State::Exp,State::Num},
            {State::Num,State::Exp,State::Sign,State::Num},

            {State::Sign, State::Num},
                        {State::Sign,State::Num,State::Exp,State::Num},
            {State::Sign,State::Num,State::Exp,State::Sign,State::Num},

            {State::Num, State::Dot, State::Num},
            {State::Num, State::Dot, State::Num,State::Exp,State::Num},
            {State::Num, State::Dot, State::Num,State::Exp,State::Sign,State::Num},

            {State::Sign, State::Num, State::Dot, State::Num},
            {State::Sign, State::Num, State::Dot, State::Num,State::Exp,State::Num},
            {State::Sign, State::Num, State::Dot, State::Num,State::Exp,State::Sign,State::Num}
        };

        vector<int> curAllowedStates;
        for (int i = 0; i < validStates.size(); i++) curAllowedStates.push_back(i);
        for (int i = 0; i < input.length(); i++) {
            char ch = input[i];
            State state = getState(ch);
            if (state == State::Invalid) return false;
            for (auto it = curAllowedStates.begin(); it != curAllowedStates.end();) {
                if (validStates.empty()) return false;
                if (i >= validStates[*it].size()) return false;
                if (validStates[*it][i] != state) it = curAllowedStates.erase(it);
                else it++;
            }
        }
        return true;
    }

    State getState(char ch) {
        if (ch >= '0' && ch <= '9')
            return State::Num;
        if (ch == '.')
            return State::Dot;
        if (ch == '+' || ch == '-')
            return State::Sign;
        if (ch == 'e')
            return State::Exp;
        return State::Invalid;
    }
};