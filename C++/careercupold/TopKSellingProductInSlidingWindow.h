#pragma once
#include "../Header.h"

class TopSellingProducts {
private:
    using Deque = deque<pair<int, unordered_map<string, int>>>;
    using Node = pair<string, int>;
    class Compare
    {
    public:
        bool operator() (Node a, Node b)
        {
            return a.second < b.second;
        }
    };
    using PriorityQue = priority_queue<Node, vector<Node>, Compare>;
    Deque dq;
    PriorityQue pq;
    int window = 20;
public:
    static void test() {
        vector<string> products = { "a","b","c","d","e","f" };
        srand(time(nullptr));
        TopSellingProducts obj;

        auto pub = thread([&obj, products]() {
            for (int i = 0; i < 30; i++) {
                unordered_map<string, int> updatedSet;
                for (auto prod : products) {
                    if (rand() % 2 == 0) updatedSet.insert({ prod,rand() % 10 });
                }
                obj.push(i, updatedSet);
                this_thread::sleep_for(1s);
            }
            });
        auto sub = thread([&obj]() {
            for (int i = 0; i < 30; i++) {
                auto res = obj.poll(i);
                for (auto item : res) {
                    cout << item.first << ":" << item.second << endl;
                }
                this_thread::sleep_for(1s);
            }
            });

        pub.join();
        sub.join();
    }

    void push(int timePoint, unordered_map<string, int> set) {
        while (!dq.empty() && dq.front().first <= timePoint - window) {
            auto cur = dq.front();
            decreaseKeys(cur);
            dq.pop_front();
        }
        dq.push_back({ timePoint,set });
        increaseKeys(set);
    }

    unordered_map<string, int> poll(int timePoint) {
        while (!dq.empty() && dq.front().first <= timePoint - window) {
            auto cur = dq.front();
            decreaseKeys(cur);
            dq.pop_front();
        }

        return getTopKElements();
    }

    void decreaseKeys(unordered_map<string, int> set) {

    }
};