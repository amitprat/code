#include "../Header.h"

/*
There is an island which is represented by square matrix NxN.
A person on the island is standing at any given co-ordinates (x,y). He can move in any direction one step right, left, up, down on the island. If he steps outside the island, he dies.

Let island is represented as (0,0) to (N-1,N-1) (i.e NxN matrix) & person is standing at given co-ordinates (x,y). He is allowed to move n steps on the island (along the matrix). What is the probability that he is alive after he walks n steps on the island?

Write a psuedocode & then full code for function
" float probabilityofalive(int x,int y, int n) ".
*/

/*
I presume that the probabilities of move up/donw/left/right are equal(0.25).
Then P(x, y, n, step) = (P(x-1, y, n, step-1) + P(x+1, y, n, step-1) + P(x, y-1, n, step-1) + P(x, y+1, n, step-1)) / 4.
(x, y) is the position. (n) is the size of island. (step) is the remaining step.
The following code is my Java implementation with some simple tests.
Dynamic Programming is also used.
*/

import java.util.*;

class ProbabilityOfAlive
{
public
    static double probabilityOfAlive(int x, int y, int n)
    {
        if (x < 0 || x > (n - 1) || y < 0 || y > (n - 1) || n < 1)
        {
            return 0.0;
        }
        return probabilityOfAlive(x, y, n, n, new HashMap<String, Double>());
    }

private
    static double probabilityOfAlive(int x, int y, int n, int step, HashMap<String, Double> map)
    {
        if (0 == step)
        {
            return 1.0;
        }
        // if the state is already calculated, return from HashMap
        String key = "";
        {
            StringBuffer sb = new StringBuffer();
            sb.append(x + ",");
            sb.append(y + ",");
            sb.append(step + ".");
            key = sb.toString();
        }
        if (map.containsKey(key))
        {
            return map.get(key);
        }
        // calculate the probability of a state
        double probability = 0.0;
        if (x > 0)
        {
            probability += 0.25 * probabilityOfAlive(x - 1, y, n, step - 1, map);
        }
        if (x < (n - 1))
        {
            probability += 0.25 * probabilityOfAlive(x + 1, y, n, step - 1, map);
        }
        if (y > 0)
        {
            probability += 0.25 * probabilityOfAlive(x, y - 1, n, step - 1, map);
        }
        if (y < (n - 1))
        {
            probability += 0.25 * probabilityOfAlive(x, y + 1, n, step - 1, map);
        }
        // save the result to HashMap and return
        map.put(key, probability);
        return probability;
    }

public
    static void main(String[] args)
    {
        System.out.println("probability1 = " + probabilityOfAlive(0, 0, 1));
        System.out.println("probability2 = " + probabilityOfAlive(0, 0, 2));
        System.out.println("probability3 = " + probabilityOfAlive(0, 0, 3));
    }
}

// Mine
#include <bits/stdc++.h>
using namespace std;

string getKey(int x, int y, int z)
{
    return "{" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "}";
}

int calculate(int x, int y, int n, int steps, unordered_map<string, int> &memo)
{
    if (x < 0 || y < 0 || x >= n || y >= n || steps < 0)
        return 0;
    if (steps == 0)
        return 1;

    string k = getKey(x, y, steps);
    if (memo.find(k) != memo.end())
        return memo[k];

    int success = 0;
    success = success + calculate(x - 1, y, n, steps - 1, memo);
    success = success + calculate(x, y - 1, n, steps - 1, memo);
    success = success + calculate(x + 1, y, n, steps - 1, memo);
    success = success + calculate(x, y + 1, n, steps - 1, memo);

    memo[k] = success;

    return success;
}

double prob1(int x, int y, int n, int steps, unordered_map<string, double> &memo)
{
    if (x < 0 || y < 0 || x >= n || y >= n)
        return 0;
    if (steps == 0)
        return 1;
    string k = getKey(x, y, steps);
    if (memo.find(k) != memo.end())
        return memo[k];

    double p = 0;
    p += 0.25 * prob1(x - 1, y, n, steps - 1, memo);
    p += 0.25 * prob1(x, y - 1, n, steps - 1, memo);
    p += 0.25 * prob1(x + 1, y, n, steps - 1, memo);
    p += 0.25 * prob1(x, y + 1, n, steps - 1, memo);

    memo[k] = p;

    return p;
}

double prob(int x, int y, int n, int steps)
{
    unordered_map<string, int> memo;
    auto success = calculate(x, y, n, steps, memo);
    int total = pow(4, steps);
    return (double)(success) / (double)(total);
}

int main()
{
    int n = 4;
    int steps = 12;
    int x = 1, y = 2;
    double res = prob(x, y, n, steps);

    cout << res << endl;

    unordered_map<string, double> memo;
    cout << prob1(x, y, n, steps, memo) << endl;

    return 0;
}
