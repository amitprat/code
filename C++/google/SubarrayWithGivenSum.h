#include "../Header.h"

/*
Given an array having positive integers, find a continous subarray which adds to a given number.
*/

/*
It can be done O(n).
My logic is as follows:- Keep adding elements to a running sum till it is either equal to given number or is greater than
 the given number. As soon as we add a number and the running number is greater than the given number we subtract the elements
  from the beginning of the array till it is again less than the given number. After the current sum is less than the given 
  number we add the next element and check and continue the same process.
*/
