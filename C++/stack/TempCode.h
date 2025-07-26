#include "../header.h"

class Solution {
   public:
    static void test() {
        Solution obj;
        auto res = obj.calculate("(1+(4+5+2)-3)+(6+8)");
        cout << res << endl;
    }

   public:
    int calculate(string s) {
        stack<int> values;
        stack<char> ops;

        string curVal;
        for (auto& ch : s) {
            if (ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                if (!curVal.empty()) values.push(stoi(curVal));
                curVal = "";

                if (ch == '(') ops.push(ch);
                else if (ch == ')') {
                    while (!ops.empty() && ops.top() != '(') {
                        auto second = values.top();
                        values.pop();
                        auto first = values.top();
                        values.pop();
                        auto op = ops.top();
                        ops.pop();

                        values.push(eval(first, second, op));
                    }
                    ops.pop();
                } else {
                    while (!ops.empty() && prec(ops.top()) >= prec(ch)) {
                        auto second = values.top();
                        values.pop();
                        auto first = values.top();
                        values.pop();
                        auto op = ops.top();
                        ops.pop();

                        values.push(eval(first, second, op));
                    }
                    ops.push(ch);
                }
            } else if (iswspace(ch)) {
                if (!curVal.empty()) values.push(stoi(curVal));
                curVal = "";
            } else {
                curVal += ch;
            }
        }
        if (!curVal.empty()) values.push(stoi(curVal));

        while (!ops.empty()) {
            auto second = values.top();
            values.pop();
            auto first = values.top();
            values.pop();
            auto op = ops.top();
            ops.pop();

            values.push(eval(first, second, op));
        }

        return values.top();
    }

    int eval(int f, int s, char op) {
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
        return -1;
    }

    int prec(char op) {
        switch (op) {
            case '^':
                return 3;
                break;
            case '*':
            case '/':
                return 2;
                break;
            case '+':
            case '-':
                return 1;
                break;
            default:
                return 0;
        }
    }
};