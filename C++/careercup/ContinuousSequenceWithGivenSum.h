#include "../header.h"

/*
https://careercup.com/question?id=6305076727513088

Question: Given a sequence of positive integers A and an integer T, return whether there is a continuous sequence of A that sums up to exactly T
Example
[23, 5, 4, 7, 2, 11], 20. Return True because 7 + 2 + 11 = 20
[1, 3, 5, 23, 2], 8. Return True because 3 + 5 = 8
[1, 3, 5, 23, 2], 7 Return False because no sequence in this array adds up to 7

public boolean findSum (int [] A ,int T){
                int sum = 0 ;
                int j = 0;
                for (int i = 0 ; i < A.length ; ++i) {
                        while (j < A.length &&  sum < T) {
                                sum += A[j] ;
                                j++;
                        }
                        if (sum == T) {
                                return true ;
                        }
                        sum -= A[i] ;
                }

                return false ;
}
*/
class ContinuousSequenceWithGivenSum {
   public:
   private:
};