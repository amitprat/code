/*
Rearrange characters in a string so that no character repeats twice.

Input: aaabc
Output: abaca

Input: aa
Output: No valid output

Input: aaaabc
Output: No valid output
*/

/*
Here is an approach that runs in O(n) time.

To clarify the idea, we will first assume that every character occurs in the string less than N/2 times, where N is the length of the string. This is not a perfect assumption, because the string may still be valid if there's one letter that occurs N/2 or (N+1)/2 times. e.g. abaca is a valid arrangement. After discussing the general approach, we can take care of this special case.

First, we count the number of occurrences of each character using an array or hash table, depending on whether the size of the alphabet is small or large. After that, we place occurrences of the first character at indices 0, 2, 4, 6, ..., etc., so that occurrences of the character are never together. If the first character used indices 0, 2, ..., 20, the second character would be placed at 22, 24, 26, etc. Upon reaching the end of the array, we would wrap around and start filling odd indices, like 1, 3, 5, in that order

To be precise, we keep a numCharsPlaced variable. If we've already written a total of numCharsPlaced characters (counting repeated chars), the next character is to be placed at (2*numCharsPlaced)%arr.length+adjustment, where adjustment is 1 if the array size is even, 0 if it's odd.

Note that this algorithm never places two identical characters next to each other, except when a character's count is so high that the wraparound to odd indices occurs and we get all the way back to where the even-indexed occurrences of the character occurred. This can only happen if a character occurs at least N/2 times.

If a character occurs (N+1)/2 times, all other character counts are less than N/2. The solution is to detect that character when validating the character occurrence counts, and ensure we start (at index 0) with that character (this will give this character enough space, and all other characters have enough space by the general proof given before). If a character occurs exactly N/2 times, we use the same remedy as for the (N+1)/2 case. In the N/2 case, it's possible that there is one other character that also occurs N/2 times, but we verify that the algorithm behaves correctly in this case.

If a character occurs more than (N+1)/2 times, there is no solution. That's because you can split the input into that many pairs of adjacent locations, and you can argue by pigeonhole principle that at least one such pair of locations must have more than one of the same character, which would mean that the same character occurs twice consecutively.
*/
#include <bits/stdc++.h>
using namespace std;

string rearrange(string str)
{
    unordered_map<char, int> map;
    for (auto ch : str)
        map[ch]++;
    using Node = pair<char, int>;
    auto comp = [](const auto &f, const auto &s) { return f.second < s.second; };
    priority_queue<Node, vector<Node>, decltype(comp)> pq(comp);
    for (auto e : map)
        pq.push(e);

    string result;
    while (!pq.empty())
    {
        auto f = pq.top();
        pq.pop();
        if (pq.empty() && !result.empty() && result.back() == f.first)
        {
            cout << "Not possible" << endl;
            break;
        }
        result += f.first;
        if (!pq.empty())
        {
            auto s = pq.top();
            pq.pop();
            result += s.first;
            if (s.second > 1)
                pq.push({s.first, s.second - 1});
        }
        if (f.second > 1)
            pq.push({f.first, f.second - 1});
    }

    return result;
}

int main()
{
    string str = "gaaaabaaefbcbbcaaadaafa";
    auto res = rearrange(str);
    cout << res << endl;
    cout << res.length() << " " << str.length() << endl;

    return 0;
}
