#pragma once
#include "../Header.h"

class CheckGrammer {
private:
    enum class State {
        None,
        Upper,
        Lower,
        Space,
        Dot,
        End
    };
public:
    bool checkSentence(string str) {
        bool started, restSentence, isSpace, end;
        started = restSentence = isSpace = end = false;

        for (auto ch : str) {
            if (isupper(ch)) {
                if (!started) started = true;
                else if (isSpace) isSpace = false;
                else return false;
            }
            else if (islower(ch)) {
                if (!started) return false;
                if (isSpace) isSpace = false;
            }
            else if (isspace(ch)) {
                if (!started) return false;
                if (!isSpace) isSpace = true;
                else return false;
            }
            else if (ch == '.') {
                if (started) end = true;
                else return false;
                started = false;
            }
        }

        return end;
    }
    State getState(char ch) {
        if (isupper(ch)) return State::Upper;
        if (islower(ch)) return State::Lower;
        if (isspace(ch)) return State::Space;
        if (ch == '.') return State::Dot;
    }
    bool isValidState(State pre, vector<State> validNextStates) {
        for (auto v : validNextStates) {
            if (v == pre) {
                return true;
            }
        }
        return false;
    }
    bool checkSentence2(string str) {
        unordered_map<State, vector<State>> stateMachine;
        stateMachine.insert({ State::None, {State::Upper} });
        stateMachine.insert({ State::Upper, {State::Lower, State::Space,State::Dot} });
        stateMachine.insert({ State::Lower, {State::Lower, State::Space, State::Dot} });
        stateMachine.insert({ State::Space, {State::Upper, State::Lower} });
        stateMachine.insert({ State::Dot, {State::End} });

        State pre = State::None;
        for (auto ch : str) {
            State cur = getState(ch);
            if (!isValidState(cur, stateMachine[pre])) return false;
            pre = cur;
        }
        return pre == State::Dot;
    }
    static void test() {
        CheckGrammer obj;
        vector<string> strs = {
                    " ",
                    "",
                    "AA",
                    "Az .",
                    "Az.",
                    "I love cinema.", "The vertex is S.",
                    "I am single.", "My name is KG.",
                    "I lovE cinema.", "GeeksQuiz. is a quiz site.",
                    "I love Geeksquiz and Geeksforgeeks.",
                    "  You are my friend.", "I love cinema"
        };

        for (auto str : strs) {
            auto res = obj.checkSentence2(str);
            if (res) {
                cout << "'" << str << "'" << " is correct." << endl;
            }
            else {
                cout << "'" << str << "'" << " is incorrect." << endl;
            }
        }
    }
};