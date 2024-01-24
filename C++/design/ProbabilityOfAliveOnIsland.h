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

struct Point
{
    int x, y;
};
struct Matrix
{
    Point p;
    int N;
    int S;
};
class IslandProbability
{
public:
    static void test()
    {
        IslandProbability obj;
        vector<Matrix> p = { {{0,0},2,1},{{0,0},2,2},{{0,1},3,1},{{2,3},4,5} };
        for (auto m : p) {
            cout << obj.probability(m.p, m.S, m.N) << endl;
        }
    }

    double probability(Point p, int steps, int N)
    {
        static unordered_map<string, double> map;
        if (steps == 0) return 1.0;
        if (steps < 0 || p.x < 0 || p.y < 0 || p.x >= N || p.y >= N) return 0;
        auto neighbours = getNeighbours(p, N);
        double prob = 0.0;
        string key = to_string(p.x) + ":" + to_string(p.y) + ":" + to_string(steps);
        if (map.find(key) != map.end()) prob = map[key];
        else {
            for (auto n : neighbours)
            {
                prob += 0.25 * probability(n, steps - 1, N);
            }
            map[key] = prob;
        }

        return prob;
    }

    vector<Point> getNeighbours(Point p, int N)
    {
        vector<Point> res;
        if (p.x - 1 >= 0) res.push_back({ p.x - 1,p.y });
        if (p.y - 1 >= 0) res.push_back({ p.x,p.y - 1 });
        if (p.x + 1 < N) res.push_back({ p.x + 1,p.y });
        if (p.y + 1 < N) res.push_back({ p.x,p.y + 1 });

        return res;
    }
};