package programs.misc;

import java.util.Arrays;

/*

This is one of the interview questions during the Amazon SDE interview. Request your help in providing the solution.
Question - We are interested in building a special type of sequence. for a given number N, we want to arrange the numbers {1,1,2,2,3,3,... N,N} such that they have the following property.
For each number / in (1,N) there should be exactly / numbers between the first appearance of the number and the second appearance. Below example would clarify further.

Input:
A Single number N for which we want to produce the sequence.

Output:
A space separated list of sequence or NA if there is no possible sequence.

Example Input:
3

Example Output:
2 3 1 2 1 3

Explanation : There is 1 number between 1s(2). There are 2 numbers between the 2's(3 1 ). There are 3 numbers between the 3's(1 2 1 ).
 */
public class ArrangeElements {
    public static void test() {
        arrange(4);
    }

    private static void arrange(int n) {
        int[] arr = new int[2 * n];
        var res = arrange(arr, n);
        if (res) {
            System.out.println(Arrays.toString(arr));
        }
    }

    private static boolean arrange(int[] arr, int gap) {
        if (gap == 0) return true;
        for (int i = arr.length - 1; i - gap > 0; i--) {
            if (arr[i] == 0 && arr[i - gap - 1] == 0) {
                arr[i] = arr[i - gap - 1] = gap;
                if (arrange(arr, gap - 1)) return true;
                else {
                    arr[i] = arr[i - gap - 1] = 0;
                }
            }
        }
        return false;
    }
}

/*
public static int[] findSolution(int n){
    int[] sol = new int[2*n];
    if (explore(sol, n)) return sol;
    return null;
  }

  public static boolean explore(int[] sol, int gap){
    if (gap == 0) return true;
    for (int i = sol.length-1; i - gap > 0 ; i--) {
      if (sol[i] == 0 && sol[i-gap-1] == 0) {
        sol[i] = gap;
        sol[i-gap-1] = gap;
        if (explore(sol, gap-1)) return true;
        else {
          sol[i] = 0;
          sol[i-gap-1] = 0;
        }
      }
    }
    return false;
  }
 */