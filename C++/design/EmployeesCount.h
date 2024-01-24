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

class TimeFormat
{
public:
    TimeFormat(string start, string end) : start(start), end(end) {}
    string start;
    string end;
};

class EmployeesCount
{
public:
    EmployeesCount() {
        int sz = 60 * 60 * 24;
        countHolder = new unsigned int[sz];
        for (int i = 0; i < sz; i++) countHolder[i] = 0;
    }

    void test()
    {
        vector<TimeFormat> v = {
            TimeFormat("00:12:23", "07:14:35"),
            TimeFormat("04:34:01", "05:23:40"),
            TimeFormat("05:12:23", "05:14:35"),
            TimeFormat("06:12:23", "11:14:35"),
            TimeFormat("07:34:01", "13:23:40"),
            TimeFormat("08:34:01", "13:23:40"),
            TimeFormat("09:12:23", "11:14:35"),
            TimeFormat("10:34:01", "13:23:40"),
            TimeFormat("11:12:23", "11:14:35"),
            TimeFormat("11:34:01", "13:23:40"),
            TimeFormat("12:12:23", "15:14:35"),
            TimeFormat("12:34:01", "20:23:40"),
            TimeFormat("13:00:00", "23:00:59"),
            TimeFormat("13:34:01", "13:43:40"),
            TimeFormat("14:12:23", "16:14:35"),
            TimeFormat("14:34:01", "15:23:40"),
            TimeFormat("16:12:23", "17:14:35"),
            TimeFormat("17:34:01", "18:23:40"),
            TimeFormat("18:12:23", "21:14:35"),
            TimeFormat("19:34:01", "23:23:40"),
            TimeFormat("20:34:31", "21:20:10")
        };
        preProcess(v);

        srand(time(NULL));
        for (int i = 0; i < 10; i++) {
            int hr = rand() % 24;
            int minute = rand() % 60;
            int second = rand() % 60;

            string tm = to_string(hr) + ":" + to_string(minute) + ":" + to_string(second);

            cout << "Employees inside office at : " << tm << " = " << GetEmployeesCount(tm) << endl;
        }
    }

    void preProcess(vector<TimeFormat> input)
    {
        for (auto i : input) {
            int num1 = getNum(i.start);
            int num2 = getNum(i.end);

            for (int i = num1; i < num2; i++) countHolder[i]++;
        }
    }

    int GetEmployeesCount(string tm) {
        return countHolder[getNum(tm)];
    }

private:
    unsigned int* countHolder;

    unsigned int getNum(string str) {
        char delimiter = ':';
        int start = 0;
        int pos = str.find(delimiter);
        int hr = stoi(str.substr(start, pos - start));

        start = pos + 1;
        pos = str.find(delimiter, start);
        int minute = stoi(str.substr(start, pos - start));

        start = pos + 1;
        int second = stoi(str.substr(start));

        return hr * 24 + minute * 60 + second;
    }
};