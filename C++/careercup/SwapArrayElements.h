/*
If [a1,a2,a3...,an,b1,b2...bn] is given input change this to [a1,b1,a2,b2.....an,bn] , solution should be in-place

Algorithm:

First swap elements in the middle pair
Next swap elements in the middle two pairs
Next swap elements in the middle three pairs
iterate n-1 steps.

Ex: with n = 4.
a1 a2 a3 a4 b1 b2 b3 b4
a1 a2 a3 b1 a4 b2 b3 b4
a1 a2 b1 a3 b2 a4 b3 b4
a1 b1 a2 b2 a3 b3 a4 b4
*/

int interleave(int arr[], int len) {
  int n = len/2;
  for (int i = 1; i < n; i++) { // my step no.
    for (int j = 0; j < i; j++) { // no. of swaps
      swap(arr, n-i+2*j, n-i+2*j+1);
    }
  }
}