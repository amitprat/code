#include "../Header.h"

/*
https://www.careercup.com/question?id=5647694703886336

Write a function that would print all positive numbers smaller than n that can be expressed as the sum of two cubes in two
 different ways. Bonus: calculate the complexity of that function.

For example, 1729 is one such number because 1729 = 1^3 + 12^3 = 9^3 + 10^3.
*/

/*
The approach goes like this

Step 1 : Find the cube root of the given 'n', lets call it as 'cubeRoot'

Step2 : Construct an array of size 'cubeRoot' with the (index +1) cubed as the value in the array[index]
For example: For the given 1029, 'cubeRoot' is 12 , a[0]=1, a[1] =8 ... a[11] = 1728

Step3: From here on, it is a famous problem of "Find 2 numbers in a sorted array equal to a given sum "

I have provided the code below in java.
*/

public
void calculateCubeSum(int n)
{

    int cuberoot = (int)Math.cbrt(n);

    int[] a = new int[cuberoot];

    // construct array

    for (int i = 0; i < cuberoot; i++)
    {
        a[i] = (i + 1) * (i + 1) * (i + 1);
    }

    // use forward and backward technique

    int fwd = 0;
    int bck = cuberoot - 1;

    while (fwd < bck)
    {

        if (a[fwd] + a[bck] < n)
            fwd++;
        else if (a[fwd] + a[bck] > n)
            bck--;
        else
        {
            System.out
                .println(Math.cbrt(a[fwd]) + ", " + Math.cbrt(a[bck]));
            fwd++;
            bck--;
        }
    }
}