#include "../header.h"

/*
https://careercup.com/question?id=5658697553412096

Given a random function with equal probability of getting 1 or 0 ie 50% each. write a custom function which uses the above random function
such that your function should return 1 with 75% probability and 0 with 25% probability.
*/
class ProbabilityOfGenerating1sWith75PercentProbability {
   private:
    int generate() {
        return rand50() | rand50();
    }

   private:
    int int myRandom() {
        int roll1 = rand50();
        int roll2 = rand50();

        // Only 4 possible combinations, with equal probabilities:
        // roll1 = roll2 = 0
        // roll1 = roll2 = 1
        // roll1 = 0; roll2 = 1
        // roll1 = 1; roll2 = 0

        if (roll1 == 0 && roll2 == 0)  // 25% probability
            return 0;
        else  // 75% probability
            return 1;
    }
};