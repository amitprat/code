#include "../Header.h"

/*
Write a program to find whether a given number is a perfect square or not. You can only use addition and 
subtraction operation to find a solution with min. complexity.

i/p : 25
o/p : True

i/p : 44
o/p: False
*/

int check(int);
void main()
{
    int N;

    printf("\n Enter the N:");
    scanf("%d", &N);
    if (check(N))
    {
        printf("\n[%d] Perfect Square:\n", N);
    }

    else
    {

        printf("\nNot perfect Square\n");
    }
}
int check(int n)
{
    int i = 1;

    while (n > 0)
    {
        n -= i;
        printf("[%d]", n);
        i += 2;
    }
    if (n == 0)
        return 1;

    return 0;
}
//complexity : O(logn) in some cases and < o(n)