#include <bits/stdc++.h>
using namespace std;

int count(int n)
{
    if (n <= 6)
        return n;

    return max(2 * count(n - 3),
               max(3 * count(n - 4),
                   4 * count(n - 5)));
}

int countDP(int n)
{
    int dp[n + 1];
    for (int i = 0; i <= 6 && i <= n; i++)
        dp[i] = i;
    for (int i = 7; i <= n; i++)
    {
        dp[i] = max(2 * dp[i - 3], max(3 * dp[i - 4], 4 * dp[i - 5]));
    }
    return dp[n];
}

int main()
{
    int n = 7;
    cout << countDP(n) << endl;

    return 0;
}