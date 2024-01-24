package programs.arrays;

import programs.types.Pair;

/*
Given a sorted integer array and a number, find the start and end indexes of the number in the array.

Ex1: Array = {0,0,2,3,3,3,3,4,7,7,9} and Number = 3 --> Output = {3,6}
Ex2: Array = {0,0,2,3,3,3,3,4,7,7,9} and Number = 5 --> Output = {-1,-1}

Complexity should be less than O(n)
 */
public class SearchRangeInSortedArray {
    public static void test() {
        SearchRangeInSortedArray obj = new SearchRangeInSortedArray();
        int[] arr1 = {0, 0, 2, 3, 3, 3, 3, 4, 7, 7, 9};
        int num1 = 3;

        int[] arr2 = {0, 0, 2, 3, 3, 3, 3, 4, 7, 7, 9};
        int num2 = 5;

        System.out.println("Range for" + num1 + ":" + obj.getRange(arr1, num1));
        System.out.println("Range for" + num2 + ":" + obj.getRange(arr2, num2));
    }

    Pair<Integer, Integer> getRange(int[] arr, int num) {
        return new Pair(startIndex(arr, num), endIndex(arr, num));
    }

    int startIndex(int[] arr, int num) {
        int s = 0, e = arr.length - 1;
        while (s < e) {
            int m = (s + e) / 2;
            if (arr[m] < num) s = m + 1;
            else e = m;
        }
        return arr[s] == num ? s : -1;
    }

    int endIndex(int[] arr, int num) {
        int s = 0, e = arr.length - 1;
        while (s < e) {
            int m = (s + e+1) / 2;
            if (arr[m] > num) e = m - 1;
            else s = m;
        }
        return arr[e] == num ? e : -1;
    }
}
