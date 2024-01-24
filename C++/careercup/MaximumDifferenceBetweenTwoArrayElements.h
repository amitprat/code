#include "../header.h"

/*
https://careercup.com/question?id=6051351341563904

Completely blew it on this question today.

1.) Given an array, find the maximum difference between two array elements given the second element comes after the first.

For example.

array = [1,2,3,4,5,6,7]

We can take the difference between 2 and 1 (2-1), but not the different between 1 and 2 (1-2).

This question is super easy, I solved it within minutes of getting of the phone. I came up with an O(n^2) solution over the phone. My improved solution was O(n).

int maxDiff(int arr[], int arr_size)
{
    int max_diff = arr[1] - arr[0];
    int min_element = arr[0];
    int i;
    for(i = 1; i < arr_size; i++)
    {
        if(arr[i] - min_element > max_diff)
            max_diff = arr[i] - min_element;
        if(arr[i] < min_element)
            min_element = arr[i];
    }
    return max_diff;
}
*/
class MaximumDifferenceBetweenTwoArrayElements {
};