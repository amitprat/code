#include "../header.h"

/*
https://www.careercup.com/question?id=12179920

Given a large document and a short pattern consisting of a few words (eg. W1 W2 W3), find the shortest string that has all the words in any order (for eg. W2 foo bar dog W1 cat W3 -- is a valid pattern)

This can be done by modifying the maximum sum subsequence.
Loop through once keeping track of
Most recent position of w1 w2 and w3, minlengthsofar and min.
*/
class ShortestSubsequenceContainingAllStrings {
};