#pragma once
#include "../header.h"

class LargestNumber {
public:
    static void test() {
        LargestNumber obj;
        vector<int> input = { 3, 30, 34, 5, 9 };
        string expected = "9534330";
        cout << obj.largestNumber(input) << endl;
    }

    string largestNumber(vector<int> input) {
        vector<string> sv;
        for (auto& i : input) sv.push_back(to_string(i));
        sort(sv.begin(), sv.end(), [](const auto& a, const auto& b) {return a + b > b + a; });
        //debug
        cout << to_string(sv) << endl;
        string result;
        for (auto& s : sv) result += s;

        return result;
    }
};