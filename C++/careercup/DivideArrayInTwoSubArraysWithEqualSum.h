#include "../header.h"

/*
https://careercup.com/question?id=5716403849003008

Given an array of integers greater than zero, find if it is possible to split it in two (without reordering the elements),
such that the sum of the two resulting arrays is the same. Print the resulting arrays.

space: O(n) (only bc of the slice)
time: O(n)


const testCases = [
  [1,2,3,4,5,6,21],
  [1,90, 50, 30, 5, 3, 2, 1 ],
  [1, 50, 900, 1000 ],
];

const arraySums = arr => {
  let sum1 = 0;
  let sum2 = arr.reduce((sum, v) => sum + v, 0);

  for (let i=0; i< arr.length; i++) {
    sum2 -= arr[i];
    sum1 += arr[i];
    if (sum1 === sum2) {
      return [
        arr.slice(0, i + 1),
        arr.slice(i),
      ];
    }
  }

  return false;
}

testCases.map(arraySums)
*/
class DivideArrayInTwoSubArraysWithEqualSum {
};