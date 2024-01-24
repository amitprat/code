#pragma once

#pragma once
#pragma once

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

using namespace std;

class SortFiles
{
public:
    void test()
    {
        //GenLoad();
        printFiles();

        cout << "Elements: ";
        while (!empty()) {
            cout << poll() << " ";
        }
    }

    void printFiles()
    {
        for (auto p : inputFiles) {
            cout << " From " << p.second.first << " : ";
            ifstream istream(p.second.first);
            int elem;
            while (!istream.eof()) {
                istream >> elem;
                cout << elem << ", ";
            }
            cout << endl;
        }
    }

    bool empty() { return processed && pqueue.empty(); }
    int peek() {
        if (pqueue.empty()) populate();
        return pqueue.top().second;
    }
    int poll() {
        if (pqueue.empty()) populate();
        auto item = pqueue.top(); pqueue.pop();
        populate(item.first);
        return item.second;
    }

    void GenLoad()
    {
        srand(time(NULL));
        for (auto p : inputFiles) {
            ofstream ofile(p.second.first);
            for (int i = 0; i < p.second.second; i++) {
                ofile << genRandom() << " ";
            }
            ofile.close();
        }
    }
private:
    bool processed = false;
    priority_queue<pair<int, int>> pqueue;
    vector<pair<int, pair<string, int>>> inputFiles = { {0, {"in1", 2}}, {1, {"in2",2}}, {2, {"in3",3}}, {3, {"in4",5}}, {4, {"in5",7}} };
    string output = "op";
    unordered_map<string, ifstream> m;

    void populate()
    {
        processed = true;
        for (auto e : inputFiles) {
            m[e.second.first] = ifstream(e.second.first);
            int elem;
            if (!m[e.second.first].eof()) {
                m[e.second.first] >> elem;
                pqueue.push({ e.first, elem });
            }
        }
    }
    void populate(int index)
    {
        string file;
        for (auto e : inputFiles) {
            if (e.first == index) file = e.second.first;
        }
        if (!m[file].eof()) {
            int elem;
            m[file] >> elem;
            pqueue.push({ index, elem });
        }
    }

    int genRandom() {
        return rand() % 10;
    }
};