#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5717453712654336

Given a length n, return the number of strings of length n that can be made up of the letters 'a', 'b', and 'c', where there can only be a maximum of 1 'b's and can only have up to two consecutive 'c's

Example:
findStrings(3) returns 19
since the possible combinations are: aaa,aab,aac,aba,abc,aca,acb,baa,bac,bca,caa,cab,cac,cba,cbc,acc,bcc,cca,ccb
and the invalid combinations are:
abb,bab,bba,bbb,bbc,bcb,cbb,ccc
*/
class FindStrings
{
public:
    static void test() {
        int res = findStrings(3, 1, 2, "");

        cout << res << endl;

        cout << findStrings(3, 1, 2) << endl;
    }

    static int findStrings(int n, int b, int c, string word) {
        if (b < 0 || c < 0) return 0;
        if (n == 0) {
            cout << word << " ";
            return 1;
        }

        int res = findStrings(n - 1, b, 2, word + "a");
        res += findStrings(n - 1, b - 1, 2, word + "b");
        res += findStrings(n - 1, b, c - 1, word + "c");

        return res;
    }

    /*
    O(n) solution is provided.

    We can divide strings in two types;
    A type which does not contain ‘b’
    and B type which contain ‘b’.
    We can define matrix A and B as follows.

    A[i]: the number of strings of length i in A type.
    B[i]: the number of strings of length i in B type.

    And the answer is A[n] + B[n]

    Because B type strings with lengh i can be generated
    by picking any sting in A type strings with length i-1,
    and put ‘b’ in any position in the string.
    There are total i positions to insert ‘b’,
    thus, following equation holds between A[i] and B[i].

    B[i] = i * A[i-1]

    So, it is enough to compute A[i].
    For considering strings in A, there are three possible
    prefixes which end with ‘a’.
    (because there is no constraint in the substring after ‘a’)

    1. ‘a’ + A type strings with length i - 1
    2. ‘ca’ + A type strings with length i - 2
    3. ‘cca’ + A type strings with length i - 3

    i.e., A[i] = A[i-1] + A[i-2] + A[i-3]
    where A[1] = 2, A[2] = 4, A[3] = 7

    We can compute matrix A iteratively.

    As an example, the number of strings of length 3 is
    A[3] + B[3] = A[3] + 3 * A[2] = 7 + 3*4 = 19.
    */
    static int findStrings(int n, int b, int c)
    {
        vector<int> A(n + 1, 0);
        A[0] = 1, A[1] = 2, A[2] = 4;

        for (int i = 3; i <= n; i++) {
            A[i] = A[i - 1] + A[i - 2] + A[i - 3];
        }

        return A[n] + n * A[n - 1];
    }
};