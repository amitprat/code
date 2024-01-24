#pragma once
#include "../header.h"
using namespace std;

class CoinChange
{
public:
    void test()
    {
        vector<pair<vector<int>, int>> v = {
            {{9,6,5,1},11}
        };

        for (auto arr : v) {
            cout << "Processing: {{";
            for (auto j : arr.first) cout << j << " ";
            cout << ", amount: " << arr.second;
            cout << "}" << endl;

            int minCoins = minCoinChange(arr.first, arr.first.size(), arr.second);
            cout << "MinCoins = " << minCoins << endl;

            minCoins = minCoinChangeDP(arr.first, arr.first.size(), arr.second);
            cout << "minCoinChangeDP = " << minCoins << endl;

            minCoins = minCoinChangeGreedy(arr.first, arr.first.size(), arr.second);
            cout << "minCoinChangeGreedy = " << minCoins << endl;

            int numWays = numWaysToMakeChange(arr.first, arr.first.size(), arr.second);
            cout << "NumWaysToMakeChange = " << numWays << endl;

            numWays = numWaysToMakeChangeDP(arr.first, arr.first.size(), arr.second);
            cout << "numWaysToMakeChangeDP = " << numWays << endl;
        }
    }

    int minCoinChange(vector<int> denom, int length, int amount)
    {
        if (amount <= 0) return 0;
        if (length == 0) return INT_MAX;

        int including = minCoinChange(denom, length, amount - denom[length - 1]);
        int excluding = minCoinChange(denom, length - 1, amount);
        if (including != INT_MAX) including += 1;

        return min(including, excluding);
    }

    int numWaysToMakeChange(vector<int> denom, int length, int amount)
    {
        if (amount == 0) return 1;
        if (length == 0 || amount < 0) return 0;

        int including = numWaysToMakeChange(denom, length, amount - denom[length - 1]);
        int excluding = numWaysToMakeChange(denom, length - 1, amount);

        return including + excluding;
    }

    int minCoinChangeDP(vector<int> denom, int length, int amount)
    {
        int* table = new int[amount + 1];
        table[0] = 0;

        for (int am = 1; am <= amount; am++)
        {
            table[am] = INT_MAX;
            for (int d = 0; d < length; d++) {
                if (denom[d] <= am && table[am - denom[d]] != INT_MAX) {
                    table[am] = min(table[am], 1+table[am - denom[d]]);
                }
            }
        }
        for (int i = 0; i <= amount; i++) cout << table[i] << " ";
        cout << endl;

        return table[amount];
    }

    int minCoinChangeGreedy(vector<int> denom, int length, int amount)
    {
        int result = 0;
        vector<int> v;
        for (int i = 0; i < length;)
        {
            if (denom[i] <= amount) {
                amount -= denom[i];
                v.push_back(denom[i]);
                result++;
            }
            else i++;
        }
        for (auto j : v) cout << j << " ";
        cout << endl;
        return result;
    }

    int numWaysToMakeChangeDP(vector<int> denom, int length, int amount)
    {
        int* table = new int[amount + 1];
        for (int i = 1; i <= amount; i++) table[i] = 0;
        table[0] = 1;

        for (int i = 0; i < length; i++)
            for (int j = denom[i]; j <= amount; j++)
                table[j] += table[j - denom[i]];

        return table[amount];
    }
};