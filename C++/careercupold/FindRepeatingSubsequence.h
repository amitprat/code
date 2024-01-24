#pragma once
#include "../Header.h"

/*
Given a string (1-d array) , find if there is any sub-sequence that repeats itself.
Here, sub-sequence can be a non-contiguous pattern, with the same relative order.

Eg:

1. abab <------yes, ab is repeated
2. abba <---- No, a and b follow different order
3. acbdaghfb <-------- yes there is a followed by b at two places
4. abcdacb <----- yes a followed by b twice

The above should be applicable to ANY TWO (or every two) characters in the string and optimum over time.

In the sense, it should be checked for every pair of characters in the string.
*/

/*
We can implement this as a variation of the longest common subsequence in O(n^2), using dynamic programming. In the general problem, given two strings, 'a' and 'b', we find the longest common subsequence by computing a matrix M of size len(a)* len(b) defined as follows: M[ i ][ j ] is the value of the longest common subsequence between the strings "a0...ai" and "b0...bj". In particular, if a[ i ] == b[ j ], then M[ i ][ j ] = max (1 + M[ i-1 ][ j-1], M[ i - 1 ][ j ], M[ i ][ j-1 ]) , otherwise M[ i ][ j ] = max (M[ i - 1 ][ j ], M[ i ][ j-1 ]). The value of longest common subsequence is therefore M[ len(a) -1 ][ len(b) - 1].

Now we can modify the longest_common_subsequence(a, a) to find the value of the longest repeated subsequence in a by excluding the cases when i == j, (which we know are always equal in this case). Here is the code in python:

abba
0 0 0 1
0 0 1 1
0 1 1 1
1 1 1 1

abcabc
0 0 0 1 1 1
0 0 0 1 2 2
0 0 0 1 2 3
1 1 1 1 2 3
1 2 2 2 2 3
1 2 3 3 3 3

abab
0 0 1 1
0 0 1 2
1 1 1 2
1 2 2 2
*/
class FindRepeatingSubstring {
public:
    static void test() {
        FindRepeatingSubstring obj;
    }
};


/*
def longest_repeated_subsequence(a) :
    n = len(a)

    M = [[0]* n for i in range(n)]

    M[0][0] = 0

    # First row
    for j in range(1, n) :
        if a[0] == a[j] :
            M[0][j] = 1
        else : M[0][j] = M[0][j - 1]

            # First column
            for i in range(1, n) :
                if a[i] == a[0] :
                    M[i][0] = 1
                else : M[i][0] = M[i - 1][0]

                    for i in range(1, n) :
                        for j in range(1, n) :
                            if a[i] == a[j] and i != j :
                                M[i][j] = max(
                                    M[i - 1][j - 1] + 1, M[i - 1][j], M[i][j - 1])
                            else :
                                M[i][j] = max(M[i - 1][j], M[i][j - 1])

                                return M[n - 1][n - 1]
                                and, to test it :


def main() :
    strings = [
        'abab',
            'abba',
            'acbdaghfb',
            'abcdacb'
    ]

    for s in strings :
        print(longest_repeated_subsequence(s) > 1)
*/