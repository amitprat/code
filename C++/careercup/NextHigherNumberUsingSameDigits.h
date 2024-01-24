#include "../header.h"

/*
https://careercup.com/question?id=4869907900530688

Find next higher number with same digits.

Example 1 : if num = 25468, o/p = 25486
Example 2 : if num = 21765, o/p = 25167
Example 3 : If num = 54321, o/p = 54321 (cause it's not possible to gen a higher num than tiz with given digits ).

- Get digits of N in positional order
- Find first digit M that is not in ascending order (searching from right to left)
- If all digits are in ascending order from right to left, then return N
- Find the smallest digit P that is to the right of M and is also larger than M
- Swap positions of M and P
- Sort digits after original position of M in ascending order from left to right
- Build and return from digits
*/
class NextHigherNumberUsingSameDigits {
};