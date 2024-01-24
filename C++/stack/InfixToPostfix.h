#pragma once
#include "../Header.h"

class InfixToPostfix {
public:
    static void test() {
        InfixToPostfix obj;
        string exp = "a+b*(c*d-e)-i";
        auto res = obj.infixToPostfix(exp);
        cout << res << endl;
    }

    string infixToPostfix(string str) {
        stack<char> st;
        string result;

        for (auto ch : str) {
            if (isOperand(ch)) {
                while (!st.empty() && prec(st.top()) >= prec(ch)) {
                    if (st.top() != '(') result += st.top();
                    st.pop();
                }
                if (st.empty() || st.top() != ')') st.push(ch);
            }
            else {
                result += ch;
            }
        }

        return result;
    }

    bool isOperand(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
    }

    int prec(char ch) {
        switch (ch) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case ')':
                return 0;
            case '(':
                return 4;
        }
    }
};