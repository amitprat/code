#include "../header.h"

/*
https://www.geeksforgeeks.org/random-number-generator-in-arbitrary-probability-distribution-fashion/
Random number generator in arbitrary probability distribution fashion

https://www.careercup.com/question?id=5767234518515712

How to randomly select a number in an array?
array: [15, 2, 4, 5, 1, -2, 0]

Follow-up:
Given a second array freq where freq[i] represents the occurrence of the ith number in array, how to randomly select a number in array based on the frequency.

Extra requirement:
Could you complete the selection in a single-pass(go through each array only once)?
*/
class GenerateRandomNumberWithGivenFrequency {
   public:
    int generate_random(const vector<int>& arr, const vector<int>& freq) {
        vector<int> cumulative_freq(freq.size());

        cumulative_freq[0] = freq[0];
        for (int i = 1; i < freq.size(); i++) {
            cumulative_freq[i] = cumulative_freq[i - 1] + freq[i];
        }

        srand(time(nullptr));
        int largest = cumulative_freq.back();
    int r = (rand()%largest)+1); // random number from 1..largest.

    return find_ceil(arr, 0, arr.size() - 1, r);
    }

    // find the element upto which the random number lies between (freq[i-1]..freq[i])
    int find_ceil(const vector<int>& arr, int l, int r, int elem) {
        if (l > r) return -1;
        if (l == r) return (arr[l] == elem) ? l : -1;

        int m = (l + r + 1) / 2;
        if (elem < arr[m]) return find_ceil(arr, l, m - 1, elem);
        return find_ceil(arr, m, r, elem);
    }

    int find_ceil_alternative(const vector<int>& arr, int l, int r, int elem) {
        if (l > r) return -1;
        if (l == r) return (arr[l] == elem) ? l : -1;

        int m = (l + r) / 2;
        if (elem > arr[m]) return find_ceil_alternative(arr, m + 1, r, elem);
        return find_ceil_alternative(arr, l, m, elem);
    }
};