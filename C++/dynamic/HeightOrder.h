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
using namespace std;

struct Node
{
    int height;
    int position;

    string to_string() {
        stringstream ss;
        ss << "{" << height << ", " << position << "}";
        return ss.str();
    }
};
class HeightOrder
{
public:
    static void test()
    {
        vector<vector<Node>> inputs = {
            {{3,0}},
        {{1,1},{3,0}},
            {{3,0},{2,1},{1,2}},
            {{3,0},{2,1},{1,1}},
            {{6,0},{5,0},{4,0},{3,2}, {2,2}, {1,4}}
        };

        for (auto input : inputs) {
            print(input);
            rearrange(input);
            print(input);
        }
    }

    static void rearrange(vector<Node>& input)
    {
        for (int i = 1; i < input.size(); i++) {
            auto key = input[i];
            int j = i - 1;
            for (; j >= 0 && swapNeeded(input[j], key); j--) {
                input[j + 1] = input[j];
                input[j + 1].position++;
            }
            input[j + 1] = key;
        }
    }

    static bool swapNeeded(Node& a, Node& b)
    {
        if (a.position < b.position)
            return false;
        if (a.position == b.position && a.height <= b.height)
            return false;
        return true;
    }

private:
    static void print(vector<Node> input)
    {
        stringstream ss;
        for (auto i : input) {
            ss << i.to_string() << " , ";
        }
        cout << ss.str() << endl;
    }
};