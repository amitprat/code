#pragma once
#include "../Header.h"

class InfixToPostfix {
public:
    static void test() {
        string exp = "a+b*(c^d-e)^(f+g*h)-i";
        auto res = infixToPostfix(exp);

        cout << "Postfix: " << res << endl;

        cout << evaluate("1^2+3^(4-5)*6") << endl;

        cout << evaluate("2^(2+3^(4-5)*6)") << endl;
    }

    static string infixToPostfix(string str) {
        stack<char> st;
        string res;

        for (auto ch : str) {
            if (isOperand(ch)) res += ch;
            else {
                if (ch == '(') st.push(ch);
                else if (ch == ')') {
                    while (!st.empty() && st.top() != '(') {
                        res += st.top();
                        st.pop();
                    }

                    if (st.top() != '(') throw exception("Invalid");
                    st.pop();
                }
                else {
                    while (!st.empty() && prec(st.top()) >= prec(ch)) {
                        res += st.top();
                        st.pop();
                    }
                    st.push(ch);
                }
            }
        }
        while (!st.empty()) {
            res += st.top(); st.pop();
        }

        return res;
    }

    static int prec(char ch) {
        switch (ch) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        }
    }

    static double evaluate(string str) {
        str = infixToPostfix(str);
        double res = 0;
        stack<double> st;
        for (auto ch : str) {
            if (isOperand(ch)) {
                st.push(ch - '0');
            }
            else {
                auto s = st.top(); st.pop();
                auto f = st.top(); st.pop();
                st.push(apply(f, s, ch));
            }
        }

        return st.top();
    }

    static double apply(double f, double s, char oper) {
        switch (oper) {
        case '^':
            return pow(f, s);
        case '+':
            return f + s;
        case '-':
            return f - s;
        case '*':
            return f * s;
        case '/':
            return f / s;

        }
    }

    static bool isOperand(char ch) {
        return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }
};