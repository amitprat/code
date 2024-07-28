#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5720615388446720

We have words and there positions in a paragraph in sorted order. Write an algorithm to find the least distance for a given 3 words.
eg. for 3 words
job: 5, 9 , 17
in: 4, 13, 18
google: 8, 19, 21
...
...
Answer: 17, 18, 19
Can you extend it to "n" words?

Context: In Google search results, the search terms are highlighted in the short paragraph that shows up. We need to find the shortest
sentence that has all the words if we have word positions as mentioned above.
*/

class FindLeastDistanceInGivenThreeWords {
   public:
    double MinimalDistance(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        int i, j, k = 0;
        double min_value = INT_MIN;
        double current_val;
        int opt_indexes[3] = {0, 0, 0};

    while (i < arr1.size() || j < arr2.size() || k < arr3.size()) {
        current_val = calculate_distance(A[i], B[j], C[k]);
        if (current_val < min_value) {
            min_value = current_val;
            opt_indexes[1] = i;
            opt_indexes[2] = j;
            opt_indexes[3] = k;
        }

        if (A[i] < B[j] && A[i] < C[k] && i < A.size)
            i++;
        else if (B[j] < C[k] && j < B.size)
            j++;
        else
            k++;
    }

    return min_value;
    }
};