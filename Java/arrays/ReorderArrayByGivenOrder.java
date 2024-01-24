package programs.arrays;

import java.util.Arrays;

/*
We have an array of objects A and an array of indexes B. Reorder objects in array A with given indexes in array B. Do not change array A's length.

example:


var A = [C, D, E, F, G];
var B = [3, 0, 4, 1, 2];


public void reorder(char [] A, int [] B){
		   for (int i = 0 ; i < B.length ; ++i) {
			   int tmp = i ;
			   while (B[tmp] != tmp) {
				   swap(A, B[tmp], tmp);
				   swapIndex (B, B[tmp], tmp) ;
				   tmp = B[tmp] ;
			   }
		   }
		}


		private void swap (char [] A, int i , int j){
			char tmp = A[i] ;
			A[i] = A[j] ;
			A[j] = tmp ;
		}

		private void swapIndex (int [] A, int i , int j){
			int tmp = A[i] ;
			A[i] = A[j] ;
			A[j] = tmp ;
}
 */
public class ReorderArrayByGivenOrder {
    public static void test() {
        ReorderArrayByGivenOrder obj = new ReorderArrayByGivenOrder();
        var A = new char[]{'C', 'D', 'E', 'F', 'G'};
        var B = new int[]{3, 0, 4, 1, 2};

        obj.sort(A, B);
        System.out.println(Arrays.toString(A));
    }

    private void sort(char[] arr, int[] order) {
        int len = order.length;
        for (int i = 0; i < len; i++) {
            int tmp = i;
            while (order[tmp] != tmp) {
                swap(arr, tmp, order[tmp]);
                swap(order, tmp, order[tmp]);
                tmp = order[tmp];
            }
        }
    }

    private void swap(int[] order, int first, int second) {
        int tmp = order[first];
        order[first] = order[second];
        order[second] = tmp;
    }

    private void swap(char[] arr, int first, int second) {
        char tmp = arr[first];
        arr[first] = arr[second];
        arr[second] = tmp;
    }
}
