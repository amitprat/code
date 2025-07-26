#pragma once
#include "../header.h"

/*
* https://leetcode.com/problems/candy/description/?envType=study-plan-v2&envId=top-interview-150
* There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
* You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
*/

class DistributeCandies {
   public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 0) return 0;

        vector<int> candies(n, 1);
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
        }

        int totalCnt = candies.back();
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) candies[i] = max(candies[i], candies[i + 1] + 1);
            totalCnt += candies[i];
        }

        return totalCnt;
    }

    int candy2(vector<int>& ratings) {
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> pq;  // rating[index] -> index (Min priority queue)
        unordered_map<int, int> m;                    // index -> candies given

        for (int i = 0; i < ratings.size(); i++) {
            pq.push({ratings[i], i});
        }

        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();

            int candy = 1;
            if (m.contains(f.second - 1) && f.first > ratings[f.second - 1]) candy = max(candy, m[f.second - 1] + 1);
            if (m.contains(f.second + 1) && f.first > ratings[f.second + 1]) candy = max(candy, m[f.second + 1] + 1);
            m[f.second] = candy;
        }

        int total = 0;
        for (auto& [index, candy] : m) {
            total += candy;
            cout << index << " " << candy << endl;
        }

        return total;
    }
};