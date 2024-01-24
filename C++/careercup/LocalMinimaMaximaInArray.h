#include "../header.h"

/*
https://careercup.com/question?id=5113392333324288

Given an array such that every next element differs from the previous by +/- 1. (i.e. a[i+1] = a[i] +/-1 ) Find the local max OR min in O(1) time. The interviewer mentioned one more condition that the min or max should be non-edge elements of the array
Example: 1 2 3 4 5 4 3 2 1 -> Local max is 5
1 2 3 4 5 -> No local max or min exists
5 4 3 2 1 -> No local max or min exists

It can be done in constant time. There should be one more condition in the question that there should be only one local maximum and one local minimum.
Given array A, local maxima or local minima is


A[0] +/- (A[ A.length -1 ] + A.length - A[0])/2
*/
class LocalMinimaMaximaInArray {
};