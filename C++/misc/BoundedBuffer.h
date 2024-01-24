#pragma once
#include "../header.h"

class BoundedBuffer {
private:
    class Node {
    public:
        string label;
        int time;
        Node(string label, int time) : label(label), time(time) {}
        string to_string() {
            return "{" + label + "," + std::to_string(time) + "}";
        }
    };
private:
    deque<Node> dq;
    int capacity;
    int oldestAllowedTime;

public:
    BoundedBuffer(int capacity, int oldest)
        : capacity(capacity), oldestAllowedTime(oldest) {}


    static void test() {
        BoundedBuffer buffer(50, 10);
        for (int i = 0; i < 100; i++) {
            buffer.add(Node("sdfsdf", i));
        }

        cout << to_string(buffer.getLastNodes(5, 5, 100)) << endl;
        cout << to_string(buffer.getLastNodes(5, 10, 100)) << endl;
        cout << to_string(buffer.getLastNodes(10, 5, 100)) << endl;
    }

    static string to_string(vector<Node> n) {
        string ss;
        for (auto i : n) {
            ss += i.to_string() + ",";
        }
        return ss;
    }

    void add(Node n) {
        if (dq.size() >= capacity) {
            dq.pop_front();
        }
        dq.push_back(n);
        while (!dq.empty() && dq.front().time + oldestAllowedTime < n.time) {
            dq.pop_front();
        }
    }

    vector<Node> getLastNodes(int cnt, int past, int curTime) {
        int curOffTime = curTime - past;
        vector<Node> res;
        for (int i = dq.size() - 1; i >= 0 && cnt-- && dq[i].time >= curOffTime; i--) {
            res.push_back(dq[i]);
        }
        return res;
    }
};