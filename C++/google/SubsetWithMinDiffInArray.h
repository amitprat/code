#include <bits/stdc++.h>
using namespace std;

/*
https://www.careercup.com/question?id=10244832

Partition a set of numbers into two such that difference between their sum is minimum, and both sets have equal number of elements.

For example: {1, 4, 9, 16} is partitioned as {1,16} and {4,9} with diff = 17-13=4.

Does greedy work here? First sorting, and then picking smallest and largest to fall in set 1, and picking 2nd smallest and 2nd largest to fall in set 2.

I was asked to prove which I failed :(

Observing the insanity of above posts which claim to develop a greedy O(nlogn) solution for a variation of partition problem, I was compelled to code the program. Being NP-hard by nature, the solution falls into pseudo-polynomial time algorithm with complexity O(n^2W) where n = # of elements, W = sum of elements.


void fun (int items[], int n)
{
	int total = accumulate (items, items+n, 0) / 2;
	int maxSubsetSz = n/2 ;
	
	vector< vector<int> > T (maxSubsetSz+1, vector<int> (total+1, 0) );

	//T[i][j] is set if there exists subset of size i that sum up to j
	T[0][0] = 1;	

	for(int i = 0; i < n; i++) //consider taking i-th item 		
           for(int k = maxSubsetSz-1; k >= 0; k--) //each item must be taken once, hence loop backwards
	       for(int j = 0; j <= total-items[i]; j++)  
	           if ( T[k][j] && items[i]+j <= total )		      		    
                         T [k+1] [j+items[i]] = 1;

	for(int j = total; j >= 1; j--)
	   if ( T [maxSubsetSz][j] ) {
		cout << "sum : " << j << endl; 
		break;
	}
}
*/

struct Node
{
    int sum;
    vector<int> elements;
};

int subsetSum(vector<int> arr, int sum)
{
    Node dp[sum + 1];
    for (int i = 0; i <= sum; i++)
        dp[i] = {INT_MAX, {}};
    dp[0] = {0, {}};
    for (int i = 0; i < arr.size(); i++)
    {
        for (int s = sum; s >= 1; s--)
        {
            if (s >= arr[i])
            {
                int newdiff = abs(s - arr[i] - dp[s - arr[i]].sum);
                int olddiff = abs(s - dp[s].sum);
                if (newdiff < olddiff)
                {
                    auto elements = dp[s - arr[i]].elements;
                    elements.push_back(arr[i]);
                    dp[s] = {arr[i] + dp[s - arr[i]].sum, elements};
                }
            }
        }
    }
    int mnIndex = -1;
    int mnDiff = INT_MAX;
    for (int u = 0; u <= sum; u++)
    {
        if (dp[u].elements.size() == arr.size() / 2 &&
            abs(sum - dp[u].sum) < mnDiff)
        {
            mnDiff = abs(sum - dp[u].sum);
            mnIndex = u;
        }
    }
    if (mnIndex != -1)
    {
        cout << "Elements :";
        for (auto e : dp[mnIndex].elements)
            cout << e << " ";
        cout << endl;
    }

    return dp[sum].sum;
}

bool subsetSum1(vector<int> arr, int sum)
{
    bool dp[sum + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int s = sum; s >= 1; s--)
        {
            if (s >= arr[i])
                dp[s] |= dp[s - arr[i]];
        }
    }

    return dp[sum];
}

int main()
{
    vector<int> arr = {1, 16, 9, 20, 5, 6, 3, 1, 1};
    int s = accumulate(arr.begin(), arr.end(), 0);
    cout << "Sum =" << s << endl;

    int desired = s / 2;
    subsetSum(arr, desired);

    cout << "Subset with given sum exists? " << subsetSum1(arr, 20) << endl;

    return 0;
}