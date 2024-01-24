#include "../header.h"

/*
https://careercup.com/question?id=6303093824159744

If a canoe can hold 2 kids and a max weight of 150 lbs, write a function that returns the minimum number of canoes needed, given a list of kids and their weights.

Algorithm is to sort the array (ascending) and walk indexes toward the middle, comparing the sum of the values at the two indexes with the max weight of the canoes (150). If the summed weight is less than 150, increment boat counter and move both indexes closer to middle of array. If summed weight is higher than 150, only increment boat counter if heaver child is less than max weight, then only move higher index toward center (decrement). The reasoning here is that we'll try to pair the lighter child with the next heaviest child on the list, so we want to leave the low index pointer where it is and then go to the next iteration.

I tried a few test cases and it seems to be working as expected.

Complexity would be O(nlogn) due to the sort at the beginning.
*/
class MinimumNumberOfCanoeNeededToCarryChildren {
   private:
    int minimumNumberOfCanoes(vector<int> weights) {
        int count = 0;
        sort(weights.begin(), weights.end());
        int l = 0, r = weights.size() - 1;
        while (l <= r) {
            if (weights[l] + weights[r] <= 150) {
                count++;
                l++;
            } else if (weights[r] <= 150) {
                count++;
            }
            r--;
        }

        return count;
    }
};