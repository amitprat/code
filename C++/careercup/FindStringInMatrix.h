#pragma once
#include "../header.h"
/*
https://careercup.com/question?id=5738491640020992

In a matrix of characters, find an string. String can be in any way (all 8 neighbors to be considered),
like find Microsoft in below matrix.

A-C-P-R-C
X-S-O-P-C
V-O-V-N-I
W-G-F-M-N
Q-A-T-I-T

String Microsoft is present in the matrix above ?
There also a slight variation where a diagonal neighbor is not considered.
Do BFS from each element as 'M' in matrix;

for i to m
  for j to n
    if a[i][j] = 'M'
      bool visited[m][n];
      memset(visited,false,m*n*sizeof(bool));
      bool res = recur(a,string+1,visited) //this method itself is O(mn)

Complexity = O(m.n.m.n) = O(m2n2)
*/

/*
There is another version of it where we can't move up row to search for word, i.e., the next character is either on right or down.
In this we can make single string from matrix iterating row by row and then can do lcs(longest common subsequence). If lcs is same as
string to look for, then we have that string
https://www.careercup.com/question?id=15616673

How can I find if a String exists in a double dimension Array. For eg. Does CAT exist in

'c','b','k'
'd','a','l'
'g','t','i'

It does exist. What will be an optimal way to do it ?

Assume you don't have to move upwards in the Array.
So in the below Array cat does not exist.
'c','b','t'
'd','a','l'
'g','J','i'
*/