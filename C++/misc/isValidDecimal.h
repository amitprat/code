#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

class IsValidDecimal {
public:
    static void test() {
        IsValidDecimal obj;
        std::vector<pair<string, bool>> tests = {
            {"10.0", true},
            {"0e3", true},
            {"e3", false},
            {"+e3", false},
            {"10.4e4", true},
            {"0.4", true},
            {".4", true},
            {"-0.4", true},
            {"+0.4", true},
            {"4.", true},
            {"e.3", false},
            {".2.", false},
            {"23.e", false},
            {"sdfs", false},
            {"  sd23 ", false},
            {"  23  . 2323", false},
            {"2e10", true},
            {"10.0", true},
            {"0.10", true},
            {"0", true},
            {" 0.1 ",true},
            {"abc", false},
            {"1 a",false},
            {"2e10", true},
            {" -90e3   ",true},
            {" 1e", false},
            {"e3", false},
            {" 6e-1", true},
            {" 99e2.5 ", false},
            {"53.5e93", true},
            {" --6 ", false},
            {"-+3", false},
            {"95a54e53", false}
        };

        for (auto test : tests) {
            bool out = false;
            if (test.second != (out = obj.isNumber(test.first))) {
                cout << test.first << " : " << to_string(out) << ", expected = " << test.second << endl;
            }
        }
    }
    bool isNumber(string s) {
        int i = 0;
        int l = s.length();
        trimWhitespace(s, i, l);
        int part1 = -1, part2 = -1;
        bool isDecimal = false, isExp = false;
        if (!isFirstPartValid(s, i, l, part1, isDecimal, isExp) || !isSecondPartValid(s, i, l, part2, isExp)) return false;
        return part1 != -1 && part2 != -1;;

        //if (isSign(s[i])) i++;

        //bool isDecimal = false;
        //bool isExp = false;
        //int part1 = 0;
        //int part2 = -1;

        //for (; i < l; i++) {
        //    int cur = -1;
        //    if (!isValidDecDigit(s[i], isDecimal, isExp, cur)) return false;
        //    if (cur != -1) {
        //        if (isDecimal || isExp) {
        //            if (part2 == -1) part2 = 0;
        //            part2 = part2 * 10 + cur;
        //        }
        //        else part1 = part1 * 10 + cur;
        //    }
        //}

        //if (isDecimal) return part2 != -1;
        //if (isExp) return part1 != 0 && part2 != -1;

        //return true;
    }

private:
    void trimWhitespace(const string& str, int& s, int& e) {
        for (; s < e; s++) {
            if (!isWhitespace(str[s])) break;
        }
        for (; e > 0; e--) {
            if (!isWhitespace(str[e - 1])) break;
        }
    }

    bool isFirstPartValid(string str, int& s, int& e, int& part1, bool& isDec, bool& isExp) {
        if (isSign(str[s])) s++;
        for (; s < e && !isDivider(str[s], isDec, isExp); s++) {
            int cur = -1;
            if (!isValidDecDigit(str[s], cur)) return false;
            if (part1 != -1) part1 = 0;
            part1 = part1 * 10 + cur;
        }
        if (isDec || isExp) s++;
        return true;
    }

    bool isSecondPartValid(string str, int& s, int& e, int& part2, bool isExp) {
        if (isExp && isSign(str[s])) s++;
        if (s == e) return false;
        for (; s < e; s++) {
            int cur = -1;
            if (!isValidDecDigit(str[s], cur)) return false;
            if (part2 != -1) part2 = 0;
            part2 = part2 * 10 + cur;
        }
        return s == e;
    }

    bool isWhitespace(char ch) {
        return (ch == ' ' || ch == '\t' || ch == '\n');
    }

    bool isSign(char ch) {
        return ch == '+' || ch == '-';
    }

    bool isValidDecDigit(char ch, int& cur) {
        if (ch >= '0' && ch <= '9') { cur = ch - '0'; return true; }
        return false;
    }

    bool isDivider(char ch, bool& isDec, bool& isExp) {
        if (ch == '.') isDec = true;
        if (ch == 'e') isExp = true;
        return isDec || isExp;
    }
};