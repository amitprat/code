#include "../Header.h"

/*
https://www.careercup.com/question?id=5725584103571456

Given a number "n", find the least number of perfect square numbers sum needed to get "n"

Example:
n=12, return 3 (4 + 4 + 4) = (2^2 + 2^2 + 2^2) NOT (3^2 + 1 + 1 + 1)
n = 6, return 3 (4 + 1 + 1) = (2^2 + 1^2 + 1^2)
*/

int num_squares(int n)
{
    int table[n + 1];
    int max = floor(sqrt(n));
    int squared;

    for (int i = 0; i <= n; i++)
    {
        table[i] = i;
    }
    for (int i = 2; i <= max; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            squared = pow(i, 2);
            if (squared <= j)
                table[j] = min(table[j], table[j - squared] + 1);
        }
    }
    return table[n];
}

// Mine

void getSqSum(int n, int r, vector<int> curRes, vector<int> &res, int cur)
{
    if (cur > n)
        return;
    if (cur == n)
    {
        if (res.empty() || curRes.size() < res.size())
            res = curRes;
        return;
    }
    for (int j = r; j >= 1; j--)
    {
        curRes.push_back(j * j);
        getSqSum(n, j, curRes, res, cur + j * j);
        curRes.pop_back();
    }
}

struct Node
{
    int cnt;
    vector<int> nums;
};

int getSqSumDP(int n)
{
    Node memo[n + 1];
    memo[0] = {0, {}};

    for (int i = 1; i <= n; i++)
    {
        memo[i].cnt = i;
        for (int k = 0; k < i; k++)
            memo[i].nums.push_back(1);
        int r = sqrt(i);
        for (int j = r; j >= 1; j--)
        {
            if (1 + memo[i - j * j].cnt < memo[i].cnt)
            {
                auto tmp = memo[i - j * j].nums;
                tmp.push_back(j * j);
                memo[i].cnt = 1 + memo[i - j * j].cnt;
                memo[i].nums = tmp;
            }
        }
    }
    for (auto i : memo[n].nums)
        cout << i << " ";
    cout << endl;

    return memo[n].cnt;
}

int main()
{
    int n = 99;
    int r = sqrt(n);
    vector<int> arr;

    getSqSum(n, r, {}, arr, 0);
    for (auto i : arr)
        cout << i << " ";
    cout << endl;

    auto res = getSqSumDP(n);
    cout << res << endl;

    return 0;
}
