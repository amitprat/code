/*
Input: A string equation that contains numbers, '+' and '*'
Output: Result as int.

For example:
Input: 3*5+8 (as String)
Output: 23 (as int)
*/
/*
Stack is the generalized way to go, but in this case something very simple would do.
The idea is to split the string by '+' operator.Now, the resultant splits are basically multiplication operations.
Do them first(by spliting them on '*') and then add the results.
*/
/*
PseudoCode :

    int ans = 0;
string[] Pluses = InputString.split('+');
for (String multString : Pluses)
{
    String[] mults = multString.split('*');
    int multAcc = 1;
    for (String num : mults)
    {
        multAcc *= Integer.parseInt(num);
    }
    sum += multAcc;
}
*/