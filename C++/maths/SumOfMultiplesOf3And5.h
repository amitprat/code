#include "../header.h"

/*
https://careercup.com/question?id=5631511174840320

write an algorithm to find sum of numbers which are smaller than N and divisible by 3 or 5

Example:
N = 9 => 3 + 5 + 6 = 14
N = 10 => 3 + 5 + 6 + 9 = 23


21
of 21 vote
Firstly, I solved it by designing O(N) algorithm but than, by the help of interviewer, I came up with a solution that solves the problem in O(1)

My final solution is as follows:


public int SumOfNumber(int N){
    N--;
    int divisibleBy3 = N/3;
    divisibleBy3 = (divisibleBy3 * (divisibleBy3 + 1) /2)*3;

    int divisibleBy5 = N/5;
    divisibleBy5 = (divisibleBy5 * (divisibleBy5 + 1) /2)*5;

    int divisibleBy15 = N/15;
    divisibleBy15 = (divisibleBy15 * (divisibleBy15 + 1) /2)*15;

    return divisibleBy3 + divisibleBy5 - divisibleBy15
}
*/
class SumOfMultiplesOf3And5 {
    int count(int n) {
        int mul3 = (n - 1) / 3;
        int mul5 = (n - 1) / 5;
        int mul15 = (n - 1) / 15;

        return 3 * sum(mul3) + 5 * sum(mul5) - 15 * sum(mul15);
    }

    int sum(int n) {
        return n * (n + 1) / 2;
    }
};