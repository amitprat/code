#include "../header.h"

/*
https://careercup.com/question?id=7937661

Write a c++ program to find the LCM of all the elements of an array.

I have a solution that doesn't require any prime test. Basically note that

LCM (a, b, c) = LCM(LCM (a, b), c)

This is easy to prove: basically LCM(a, b) takes the maximum index in the prime factorization of a, b. LCM(a, b, c) takes the maximum index of all possible primes in a, b, and c, which is equivalent to finding the maximum index of primes from a, b and then c.

Based on these, and the fact that LCM(a, b) = a * b / GCD(a, b), we can do an iterative algorithm that only requires a GCD procedure, which can be easily done using the Euclid's algorithm.

int GCD(int a, int b){
    if(b==0) return a;
    return GCD(b, a%b);
}

int LCM(int a, int b){
    return a*b/GCD(a,b);
}

int LCM2(int *a, int i, int n){
    if(i == n){
        return 1;
    }

    return LCM(a[i],LCM2(a,i+1,n));
}

int a[] = {3,5,2};
LCM2(a,0,3) will be the call.
*/
class CalculateLCMOfArray {
   private:
    int GCD(int a, int b) {
        if (b == 0) return a;
        return GCD(b, a % b);
    }

    int LCM(int a, int b) {
        return a * b / GCD(a, b);
    }

    int LCM2(int *a, int i, int n) {
        if (i == n) {
            return 1;
        }

        return LCM(a[i], LCM2(a, i + 1, n));
    }
};