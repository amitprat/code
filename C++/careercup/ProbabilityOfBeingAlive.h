#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=15556758

There is an island which is represented by square matrix NxN.
A person on the island is standing at any given co-ordinates (x,y).
He can move in any direction one step right, left, up, down on the island. If he steps outside the island, he dies.

Let island is represented as (0,0) to (N-1,N-1) (i.e NxN matrix) & person is standing at given co-ordinates (x,y).
He is allowed to move n steps on the island (along the matrix). What is the probability that he is alive after
he walks n steps on the island?

Write a psuedocode & then full code for function
" float probabilityofalive(int x,int y, int n) ".

I presume that the probabilities of move up/donw/left/right are equal(0.25).
Then P(x, y, n, step) = (P(x-1, y, n, step-1) + P(x+1, y, n, step-1) + P(x, y-1, n, step-1) + P(x, y+1, n, step-1)) / 4.
(x, y) is the position. (n) is the size of island. (step) is the remaining step.
The following code is my Java implementation with some simple tests.
Dynamic Programming is also used.
*/

class ProbabilityOfBeingAlive {
   public:
    static void test() {
        ProbabilityOfBeingAlive obj;
        unordered_map<string, double> visited;
        double prob1 = obj.getProbabilityOfBeingAlive({0, 0}, 10, 20, visited);
        double prob2 = obj.getProbabilityOfBeingAlive2({0, 0}, 10, 20);
        double prob3 = obj.testIslandProbabilty();
        assert(prob1 == prob2);
        assert(prob1 == prob3);

        cout << "Result: " << prob1 << endl;
    }

   private:
    double getProbabilityOfBeingAlive(Point startPos, int n, int steps, unordered_map<string, double>& visited) {
        if (!isValid(startPos, n)) return 0.0;  // If not valid, return 0
        if (steps == 0) return 1.0;             // if steps == 0, then point is already inside so return 1

        // If this point is already cached, return the cached value.
        string key = to_string(startPos.x) + ":" + to_string(startPos.y) + ":" + to_string(steps);
        if (visited.find(key) != visited.end()) return visited[key];

        double value = 0.25 * getProbabilityOfBeingAlive({startPos.x, startPos.y - 1}, n, steps - 1, visited) +
                       0.25 * getProbabilityOfBeingAlive({startPos.x, startPos.y + 1}, n, steps - 1, visited) +
                       0.25 * getProbabilityOfBeingAlive({startPos.x - 1, startPos.y}, n, steps - 1, visited) +
                       0.25 * getProbabilityOfBeingAlive({startPos.x + 1, startPos.y}, n, steps - 1, visited);

        visited[key] = value;

        return visited[key];
    }

    bool isValid(Point pos, int n) {
        return pos.x < n && pos.y < n && pos.x >= 0 && pos.y >= 0;
    }

   private:
    double getProbabilityOfBeingAlive2(Point p, int n, int steps) {
        static unordered_map<string, double> map;
        if (steps == 0) return 1.0;
        if (steps < 0 || p.x < 0 || p.y < 0 || p.x >= n || p.y >= n) return 0;

        double prob = 0.0;
        string key = to_string(p.x) + ":" + to_string(p.y) + ":" + to_string(steps);
        if (map.find(key) != map.end()) {
            prob = map[key];
        } else {
            auto neighbours = getNeighbours(p, n);
            for (auto neighbour : neighbours) {
                prob += 0.25 * getProbabilityOfBeingAlive2(neighbour, n, steps - 1);
            }
            map[key] = prob;
        }

        return prob;
    }

    vector<Point> getNeighbours(Point p, int N) {
        vector<Point> res;

        if (p.x - 1 >= 0) res.push_back({p.x - 1, p.y});
        if (p.y - 1 >= 0) res.push_back({p.x, p.y - 1});
        if (p.x + 1 < N) res.push_back({p.x + 1, p.y});
        if (p.y + 1 < N) res.push_back({p.x, p.y + 1});

        return res;
    }

   private:
    // For the case, when island is arbitary and don't always starts with (0,0) and rectangle.
    template <class T>
    class Island {
       public:
        Point top, bottom;
        Island(Point top, Point bottom) : top(top), bottom(bottom) {}
        string to_string() {
            return "{" + top.to_string() + ", " + bottom.to_string() + "}";
        }
        bool isValid(Point p) {
            return p.x >= top.x && p.y >= top.y && p.y <= bottom.x && p.y <= bottom.y;
        }
    };

    double testIslandProbabilty() {
        int n = 10;
        int steps = 20;
        Point p(0, 0);
        Island<int> island({0, 0}, {n, n});
        unordered_map<string, double> memo;

        return getProbabilityOfBeingAlive3(island, p, steps, memo);
    }

    double getProbabilityOfBeingAlive3(Island<int> island, Point pos, int step, unordered_map<string, double>& memo) {
        if (!island.isValid(pos)) return 0.0;
        if (step == 0) return 1.0;

        string k = key(pos, step);
        if (memo.find(k) != memo.end()) return memo[k];

        memo[k] = 0.25 * getProbabilityOfBeingAlive3(island, pos + Point{-1, 0}, step - 1, memo) +
                  0.25 * getProbabilityOfBeingAlive3(island, pos + Point{1, 0}, step - 1, memo) +
                  0.25 * getProbabilityOfBeingAlive3(island, pos + Point{0, 1}, step - 1, memo) +
                  0.25 * getProbabilityOfBeingAlive3(island, pos + Point{0, -1}, step - 1, memo);

        return memo[k];
    }

    string key(Point pos, int step) {
        string k = "key=(";
        k += pos.to_string();
        k += ", " + std::to_string(step);
        k += ")";
        return k;
    }
};