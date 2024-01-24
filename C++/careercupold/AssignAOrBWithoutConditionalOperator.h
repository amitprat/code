#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5135296679116800

You are given four integers 'a', 'b', 'y' and 'x', where 'x' can only be either zero or one. Your task is as follows:

If 'x' is zero assign value 'a' to the variable 'y', if 'x' is one assign value 'b' to the variable 'y'.

You are not allowed to use any conditional operator (including ternary operator).
Follow up: Solve the problem without utilizing arithmetic operators '+ - * /'.
*/
class AssignAOrBWithoutConditionalOperator
{
public:
    static void test()
    {

    }

    void fun(int a, int b, int x, int y)
    {
        int arr[2];
        arr[0] = a;
        arr[1] = b;
        y = arr[x];
    }

    void fun2(int a, int b, int x, int y)
    {
        int y = (1 - x) * a + x * b;
    }

    void fun3(int a, int b, int x, int y)
    {
        int y = (x && b) || a;
    }

    void fun4(int a, int b, int x, int y)
    {
        int arr[] = { a, b };
        y = arr[x];
    }
};