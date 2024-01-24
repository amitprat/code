#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <fstream>
using namespace std;

class ReadLastNLines
{
public:
    static void test()
    {
        int N = 2;
        ReadLastNLines obj;
        {
            string smallFile = "small.txt";
            ifstream sin;
            sin.open(smallFile, ifstream::in | ifstream::binary);
            if (!sin.is_open())
            {
                cout << "Failed to open file :" << smallFile << endl;
                return;
            }

            vector<string> result = obj.readSmallFile(sin, N);
            cout << "Last N Lines:" << endl;
            for (auto i : result) cout << i << endl;
            cout << endl << endl;
        }

        {
            vector<ios_base::streampos> positions;
            string largeFile = "large.txt";
            ifstream lin;
            lin.open(largeFile, ifstream::in | ifstream::binary);
            if (!lin.is_open())
            {
                cout << "Failed to open file :" << largeFile << endl;
                return;
            }
            while (!lin.eof()) {
                positions.push_back(ios_base::cur);
                string line;
                getline(lin, line);
            }
            lin.seekg(ios_base::beg);

            vector<string> result = obj.readLargeFile(lin, N);
            cout << "Last N Lines:" << endl;
            for (auto i : result) cout << i << endl;
            cout << endl << endl;
        }
    }

    vector<string> readSmallFile(ifstream& in, int N)
    {
        queue<string> q;
        vector<string> res;

        while (!in.eof()) {
            string line;
            getline(in, line);
            q.push(line);
            while (q.size() > N) q.pop();
        }

        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }

        return res;
    }

    vector<string> readLargeFile(ifstream& in, int N)
    {
        in.seekg(-1, ios_base::end);
        vector<string> res;
        if (in.tellg() < 1) return res;

        int lines = 0;
        while (lines < N) {
            char ch;
            in.get(ch);

            if (ch == '\n') lines++;
            in.seekg(-2, ios_base::cur);
        }
        in.seekg(2, ios_base::cur);

        while (!in.eof()) {
            string line;
            getline(in, line);
            res.push_back(line);
        }

        return res;
    }
};