#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <sstream>
#include <future>
using namespace std;

class StringWithValidParen
{
public:
    static void test()
    {
        StringWithValidParen obj;
        string strs[] = { "", "a", "(", "((", "(a)", "((a(b))", "(a(b))))(c(d)))", "abcd(e(f(g(h)(g(k)))))" };
        for (auto str : strs) {
            auto res = obj.execute(str);
            cout << "original=" << str << "::" << "Modified=" << res << endl;

            cout << "-----------" << endl;
            res = obj.executeWithoutMemory(str);
            cout << "original=" << str << "::" << "Modified=" << res << endl;
            cout << endl << "==================" << endl;
        }
    }

    string execute(string str)
    {
        stack<int> positions;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') positions.push(i);
            else if (str[i] == ')') {
                if (!positions.empty()) {
                    positions.pop();
                }
                else {
                    str.erase(i--, 1);
                }
            }
        }
        while (!positions.empty()) {
            str.erase(positions.top(), 1);
            positions.pop();
        }

        return str;
    }

    string executeWithoutMemory(string str)
    {
        int paren = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') paren++;
            else if (str[i] == ')') {
                if (paren > 0) paren--;
                else str.erase(i--, 1);
            }
        }

        paren = 0;
        for (int i = str.length() - 1; i >= 0; i--) {
            if (str[i] == ')') paren++;
            else if (str[i] == '(') {
                if (paren > 0) paren--;
                else str.erase(i, 1);
            }
        }

        return str;
    }
};