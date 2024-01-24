#pragma once
#include "../header.h"

class Calculator {
private:
    unordered_map<string, int> precMap = {
        {"*",4},
        {"/",4},
        {"+",2},
        {"-",2}
    };
public:
    static void test() {
        Calculator obj;
        vector<string> inputs = {
            "1+2+4",
            "2*3+4",
            "1+2*3/4",
            "5/4*3",
            "1+2*3/4+5/4",
            "1+2*3/4+5/4*3",
            "4*4+5-2/5+3/1+3"
        };

        for (auto& input : inputs) {
            double res = obj.calculate(input);
            cout << "Res of " << input << " = " << res << endl;
            string pf = obj.getPostfix(input);
            res = obj.evaludatePostfix(pf);
            cout << "Postfix " << pf << " = " << res << endl;
        }
    }

    double calculate(string input) {
        stack<double> operands;
        stack<string> operators;

        vector<string> parts = split(input, { "/","*","+","-","(",")" });
        for (auto& part : parts) {
            if (isOperator(part)) {
                while (!operators.empty() && prec(part) <= prec(operators.top())) {
                    string curOp = operators.top();
                    operators.pop();

                    double second = operands.top(); operands.pop();
                    double first = operands.top(); operands.pop();

                    double res = eval(first, second, curOp);
                    operands.push(res);
                }
                operators.push(part);
            }
            else {
                operands.push(stod(part));
            }
        }

        while (!operators.empty()) {
            string curOp = operators.top();
            operators.pop();

            double second = operands.top(); operands.pop();
            double first = operands.top(); operands.pop();

            double res = eval(first, second, curOp);
            operands.push(res);
        }

        return operands.top();
    }

    vector<string> split(string input, vector<string> regex, bool exclude = false) {
        vector<string> parts;
        while (!input.empty()) {
            size_t mnPos = string::npos;
            for (auto ex : regex) {
                size_t cur = input.find(ex);
                if (cur != string::npos) {
                    if (mnPos == string::npos) mnPos = cur;
                    else mnPos = min(cur, mnPos);
                }
            }
            if (mnPos == string::npos) {
                parts.push_back(input);
                break;
            }
            parts.push_back(input.substr(0, mnPos));
            if (!exclude) parts.push_back(input.substr(mnPos, 1));
            input = input.substr(mnPos + 1);
        }
        return parts;
    }

    bool isOperator(string op) {
        return op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/';
    }

    int prec(string op) {
        return precMap[op];
    }

    double eval(double a, double b, string op) {
        switch (op[0]) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
        }
        return 0;
    }

    string getPostfix(string input) {
        vector<string> parts = split(input, { "/","*","+","-","(",")" });
        string res;
        stack<string> operators;

        for (auto& part : parts) {
            if (isOperator(part)) {
                while (!operators.empty() && prec(part) <= prec(operators.top())) {
                    string curOp = operators.top();
                    operators.pop();

                    res += " " + curOp;
                }
                operators.push(part);
            }
            else {
                if (!res.empty()) res += " ";
                res += part;
            }
        }

        while (!operators.empty()) {
            res += " " + operators.top(); operators.pop();
        }

        return res;
    }

    double evaludatePostfix(string postfix) {
        stack<double> operands;
        vector<string> parts = split(postfix, { " " }, true);
        for (auto& part : parts) {
            if (isOperator(part)) {
                double s = operands.top(); operands.pop();
                double f = operands.top(); operands.pop();
                double res = eval(f, s, part);
                operands.push(res);
            }
            else {
                operands.push(stod(part));
            }
        }

        return operands.top();
    }
};