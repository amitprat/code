package Java.careercup;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/*
  Input: 4 2 -3 1 6
  1) 
    run two loops
    check if sum of zero, return
  2) 
    take a hashmap of size n
    initialize sum with zero
    calculate sum from 0 to i ( i from 0 to n)
    hash the sum
    if currrent element is zero or this element make sum as zero then return true;
    critical - if you find the sum already existing in hash, means the sum of elements inbetween must be zero and hence return true
     
    for each element in array
      sum += arr[i];
      if( arr[i] == 0 || sum == 0 || hash.find(sum) != hash.end() )
        return true;
*/

public class MaxLengthSubarrayWithGivenSum {
    static Boolean printZeroSumSubarray(int arr[]) {
        HashMap<Integer, Integer> hashMap = new HashMap<Integer, Integer>();
        int sum = 0;

        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];

            // Return true in following cases
            // a) Current element is 0
            // b) sum of elements from 0 to i is 0
            // c) sum is already present in hash map
            if (arr[i] == 0 || sum == 0 || hashMap.get(sum) != null)
                return true;

            // Add sum to hash map
            hashMap.put(sum, i);
        }

        // We reach here only when there is no subarray with 0 sum
        return false;
    }
}
