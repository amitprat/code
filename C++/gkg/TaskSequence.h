#pragma once
#include "../Header.h"

/*
Task schedule: given a sequence of task like A B C(means 3 different tasks), and a coldtime, which means you need to wait for that much time to start next [same] task. Now----

Input: string, n
Output: the best task-finishing sequence.

eg. input: AAABBB, 2
Output: AB_AB_AB
( "_" represents do nothing and wait)
*/

class TaskSequence {
    struct Node {
        char val;
        int freq;
    };
public:
    static void test() {
        TaskSequence obj;
        string str = "AAABBBCCDE";
        int n = 2;

        string res = obj.getSeq(str, n);
        cout << res << endl;
    }

    string getSeq(string str, int n) {
        auto comp = [](const Node& f, const Node& s) {return f.freq < s.freq; };
        priority_queue<Node, vector<Node>, decltype(comp)> pq(comp);

        int charFreq[256] = { 0 };
        for (auto ch : str) charFreq[(int)ch]++;

        for (int i = 0; i < 256; i++) {
            if (charFreq[i] > 0) pq.push({ (char)i, charFreq[i] });
        }
        string result;

        while (!pq.empty()) {
            queue<Node> tmp;
            for (int i = 0; i < n && !pq.empty(); i++) {
                auto f = pq.top(); pq.pop();
                result += f.val;
                f.freq--;
                tmp.push(f);
            }

            int sz = tmp.size();
            while (!tmp.empty()) {
                auto f = tmp.front(); tmp.pop();
                if (f.freq > 0) pq.push(f);
            }

            if (!pq.empty()) {
                if (n + 1 - sz > 0) result += string(n + 1 - sz, '_');
            }
        }

        return result;
    }
};

/*
Use a maxheap with the frequency of each task being the key, everytime pop n item from the heap, and put in the result and update the keys. if there is less than n item in the heap then we should fill the gap with '_'


def fastestTaskSequence(tasks, n):
    frequencies = dict()
    a = []
    for ch in tasks:
        if ch in frequencies:
            frequencies[ch] += 1
        else:
            frequencies[ch] = 1
    for key, val in frequencies.iteritems():
        maxheappush(a, [val, key])
    result = ''
    while len(a):
        temp = []
        for i in range(n+1):
            if len(a):
                task = maxheappop(a)
                result += task[1]
                temp.append(task)
            else:
                break
        itemPushed = len(temp)
        while len(temp):
            task = temp.pop()
            task[0] -= 1
            if task[0] > 0:
                maxheappush(a, task)
        if len(a):
            result += '_' * (n+1-itemPushed)
    return result
*/