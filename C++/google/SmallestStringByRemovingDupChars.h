#include "../Header.h"

/*
https://www.careercup.com/question?id=5758790009880576
Given a string which only contains lowercase. You need delete the repeated letters only leave one, and try to make the
 lexicographical order of new string is smallest.
i.e:
bcabc
You need delete 1 'b' and 1 'c', so you delete the first 'b' and first 'c', the new string will be abc which is smallest.

ps: If you try to use greedy algorithm to solve this problem, you must sure that you could pass this case:
cbacdcbc. answer is acdb not adcb

I can't solve this problem well and the interviewer said that you can scan the string twice. First scan is do some preprocess,
 and the second is to get the answer, but I really can't come up this idea.
*/

/*

8
of 8 vote
UPD: I could find a way to optimize my code to O(N). Main idea is the same. I added updated part after my old explanations


Here's my O(N^2) idea which is absoloutly true:D ( proved, and tested with many random test cases)

Let's say we have string S:

I define next[i] = next position (after i) which is equal to S[i], if there is not, -1.

So if S="bacdbcb", next={4,-1,5,-1,6,-1,-1}

Now, I iterate through S, from left to right, and at each position, I decide whether to pick the current character or not. Also, there is an array called visited, which visited[i]=true means character i has been picked.

Greedy part:
If we are at position i, (let's say x=S[i]), we need to find the first j>i which next[j]=-1 and visited[j]=false, call it y=S[j]. Also I need to know what is the smallest character from i to j, call it z( and obviously visited[z]=false). If the smallest character in between, z, is bigger than x, then add x to answer and visited[x] = true, otherwise skip x and continue to i+1.

Here's the reason:
We have something like this.
....x .... z ... y ...
It means definietly y is the part of answer string (since its next is -1). So if there is nothing smaller than x between x and y (including y), for sure it's better to choose x to have a smaller lexicographic answer.(note that all the characters between x and y have another copy after y, since y is the first position which has no next, so it's safe to postpone picking them, if needed). On the other hand, if z<x for sure it's better to skip x and choose another x later on.

Because at each position i, we need to see, in worst case, all next characters, so time complexity is O(N^2).

I couldn't find a way to find y in O(logn) or O(1), if there is any suggestion please let me know.

Also, I really really enjoyed the problem and it took me a day to come up with this solution!
*/

string removeRepeated(string s)
{
    int N = s.size();
    vector<int> next(N);
    int lastPos[26];
    for (int i = 0; i < ; 26; i++)
        lastPos[i] = -1;

    for (int i = N - 1; i >= 0; i--)
    {
        int ind = s[i] - 'a';
        next[i] = lastPos[ind];
        lastPos[ind] = i;
    }

    vector<bool> visited(26, false);
    string ans;
    for (int i = 0; i < N; i++)
    {
        int cur = s[i] - 'a';

        if (visited[cur])
            continue;
        if (next[i] == -1)
        {
            ans += s[i];
            visited[cur] = true;
        }
        else
        {

            int j = i + 1;
            char smaller = s[i];
            while (j < N)
            {
                if (visited[s[j] - 'a'] == false)
                {
                    smaller = min(smaller, s[j]);
                    if (next[j] == -1)
                        break;
                }
                j++;
            }

            if (s[i] <= smaller)
            {
                ans += s[i];
                visited[cur] = true;
            }
        }
    }

    return ans;
}