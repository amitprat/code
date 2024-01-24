#pragma once
#include "../Header.h"

/*
Given 2n points on a circle.find the number of ways to draw n non intersecting chords.
*/

Cal(n){
  if (n is Odd) return 0;
  if (n==2) return 1;
  else
    for i from 2 to n{
      sum += (Cal(i-2) * Cal(n-i);
    }
  return sum;
}