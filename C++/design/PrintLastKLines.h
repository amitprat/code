#pragma once
#include "../header.h"

class PrintLastKLines {
   public:
    static void test() {
        string fileName = "test.txt";
        ofstream out(fileName);
        if (!out) cerr << "Failed to open file" << endl;

        out << "This is first lien" << endl;
        out << "This is second lien" << endl;
        out << "This is third lien" << endl;
        out << "This is fourth lien" << endl;
        out << "This is fifth lien" << endl;
        out << "This is sixth lien" << endl;
        out << "This is seventh lien" << endl;

        auto res = getLastKLines(fileName, 3);
        cout << res << endl;
    }

   public:
    static vector<string> getLastKLines(string fileName, int k) {
        ifstream in(fileName);

        string line;
        vector<string> buffer(k);
        int start = 0, end = -1;
        while (getline(in, line)) {
            cout << "Read line: " << line << endl;
            end = next(end, k);
            if (isfull(start, end)) start = next(start, k);
            buffer[end] = line;
        }

        vector<string> result;
        int i = start;
        while (true) {
            cout << "Pushed line: " << buffer[i] << endl;
            result.push_back(buffer[i]);
            if (i == end) break;
            i = next(i, k);
        }

        return result;
    }

    static bool isfull(int start, int end) {
        return start == end;
    }

    static int next(int end, int k) {
        return (end + 1) % k;
    }
};