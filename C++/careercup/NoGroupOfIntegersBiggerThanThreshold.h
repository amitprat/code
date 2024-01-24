#include "../header.h"

/*
https://careercup.com/question?id=6026101998485504

Given an unordered array of positive integers, create an algorithm that makes sure no group of integers of size bigger than M have the same integers.

Input: 2,1,1,1,3,4,4,4,5 M = 2
Output: 2,1,1,3,1,4,4,5,4

we can take two pointers and store the occurance count and move left to right and swapping at any occurance of more than M with the next difference number.
this will leave same digits in the end .. so you will need to move from right to left and refill them.. will have no solution if a digit occurs more than N - (N/M) times in the pattern

*/
class NoGroupOfIntegersBiggerThanThreshold {
};