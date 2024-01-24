#include "../header.h"

/*
https://careercup.com/question?id=4911380140392448

Input: A string equation that contains numbers, '+' and '*'
Output: Result as int.

For example:
Input: 3*5+8 (as String)
Output: 23 (as int)

int ans = 0;
string[] Pluses = InputString.split('+');
for (String multString: Pluses)
{
    String[] mults = multString.split('*');
    int multAcc = 1;
    for (String num: mults)
    {
        multAcc *= Integer.parseInt(num);
    }
    ans += multAcc;
}
*/
class SimpleExpressionEvaluation {
   public:
};