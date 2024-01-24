#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

class EvaluateExpr
{
public:
    static void test(vector<string> expressions)
    {
        EvaluateExpr obj;
        for (auto expr : expressions) {
            cout << "Expression: " << expr << ", ";
            cout << "Result: " << obj.evaluate(expr) << endl;
        }
    }

    int evaluate(string expr)
    {
        vector<string> p = postfix(expr);
        cout << "Postfix = ";
        for (auto i : p) cout << i << " ";
        cout << endl;
        return evaluatePostfix(p);
    }

private:
    int evaluatePostfix(vector<string> p)
    {
        stack<int> st;
        for (auto str : p) {
            if (isOperand(str)) {
                st.push(toInt(str));
            }
            else if (isOperator(str)) {
                int f = st.top(); st.pop();
                int s = st.top(); st.pop();
                int r = eval(f, s, str[0]);
                st.push(r);
            }
        }

        return st.top();
    }

    int eval(int f, int s, char op)
    {
        switch (op) {
            case '*':
                return f * s;
            case '/':
                return f / s;
            case '+':
                return f + s;
            case '-':
                return f - s;
        }
    }
    vector<string> postfix(string expr)
    {
        vector<string> res;
        stack<char> st;
        string operand;
        for (auto ch : expr) {
            if (isOperand(ch)) {
                operand += ch;
            }
            else if (isOperator(ch)) {
                res.push_back(operand);
                operand = string();
                if (ch == '(') st.push(ch);
                else if (ch == ')') {
                    char oper = st.top(); st.pop();
                    while (!st.empty() && oper != '(') {
                        res.push_back(string(1, oper));
                        oper = st.top(); st.pop();
                    }
                }
                else {
                    while (!st.empty() && prec(ch) >= prec(st.top())) {
                        res.push_back(string(1, st.top())); st.pop();
                    }
                    st.push(ch);
                }
            }
            else
                throw new exception("Invalid Expression");
        }
        res.push_back(operand);

        while (!st.empty()) {
            res.push_back(string(1, st.top())); st.pop();
        }

        return res;
    }

    bool isOperand(char ch) {
        return ch >= '0' && ch <= '9';
    }

    bool isOperand(string str) {
        for (auto ch : str) if (!isOperand(ch)) return false;
        return true;
    }

    bool isOperator(char ch) {
        return ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-';
    }

    bool isOperator(string str) {
        if (str.size() != 1) return false;
        char ch = str[0];
        return ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-';
    }

    int toInt(string str) {
        int res = 0;
        for (auto ch : str) {
            int i = ch - '0';
            res = res * 10 + i;
        }

        return res;
    }

    int prec(char op) {
        switch (op) {
            case '^':
                return 0; break;
            case '*':
            case '/':
                return 1; break;
            case '+':
            case '-':
                return 2; break;
            default:
                return 3;
        }
    }
};