#pragma once
#include "../Header.h"

/*
find the sum of all 4 digit numbers formed from 1, 2, 3, 4 whithout rep .
*/

/*
With 4 placed in units place, there are 3! permutations of 123 in thousandths, hundredths and tenths place. That means 4 occurs in units place 3! times.

Similarly 3 2 and 1 each occur in units place 3! times. The sum of all numbers in units place is therefore 3!(4 + 3 + 2 + 1) = 6 * 10 = 60.

The same value happens to occur in tenths, hundredths and thousandths place as well, except that it gets multiplied by a power of 10 according to its position.

So, the total should be 60 + 600 + 6000 + 60000 = 66660.
*/