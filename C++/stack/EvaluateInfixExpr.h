#pragma once
#include "../Header.h"
using namespace std;

class EvaluateInfixExpr
{
public:
    static void test()
    {
        vector<string> expressions = { "10 + 2 * 6","100 * 2 + 12","100 * ( 2 + 12 )","100 * ( 2 + 12 ) / 14" };

        EvaluateInfixExpr obj;
        for (auto& expr : expressions) {
            int result = obj.evaluate(expr);
            cout << format("Infix expression={}, Result={}", expr, result) << endl;
        }
    }

    int evaluate(string expr)
    {
        vector<string> p = postfix(expr);
        cout << format("Postfix expression: {}", to_string(p)) << endl;
        return evaluatePostfix(p);
    }

private:
    int evaluatePostfix(vector<string> p)
    {
        stack<int> st;
        for (auto& str : p) {
            if (isOperand(str)) {
                st.push(stoi(str));
            }
            else if (isOperator(str)) {
                int s = st.top(); st.pop();
                int f = st.top(); st.pop();
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
        vector<string> result;
        stack<char> operStack;

        string operand;
        for (auto ch : expr) {
            if (isOperand(ch)) {
                operand += ch;
            }
            else if (isOperator(ch)) {
                if (!operand.empty()) {
                    result.push_back(operand);
                    operand = string();
                }

                if (ch == '(') operStack.push(ch);
                else if (ch == ')') {
                    char oper = operStack.top(); operStack.pop();
                    while (!operStack.empty() && oper != '(') {
                        result.push_back(string(1, oper));
                        oper = operStack.top(); operStack.pop();
                    }
                }
                else {
                    while (!operStack.empty() && prec(operStack.top()) >= prec(ch)) {
                        result.push_back(string(1, operStack.top())); operStack.pop();
                    }
                    operStack.push(ch);
                }
            }
            else if (ch == ' ' || ch == '\t') continue;
            else throw exception("Invalid Expression");
        }
        if (!operand.empty()) result.push_back(operand);

        while (!operStack.empty()) {
            result.push_back(string(1, operStack.top())); operStack.pop();
        }

        return result;
    }

    bool isOperand(char ch) {
        return ch >= '0' && ch <= '9';
    }

    bool isOperand(string str) {
        for (auto ch : str) if (!isOperand(ch)) return false;
        return true;
    }

    bool isOperator(char ch) {
        return ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '(' || ch == ')';
    }

    bool isOperator(string str) {
        if (str.size() != 1) return false;
        char ch = str[0];
        return ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-';
    }

    int prec(char op) {
        switch (op) {
        case '^':
            return 3; break;
        case '*':
        case '/':
            return 2; break;
        case '+':
        case '-':
            return 1; break;
        default:
            return 0;
        }
    }
};