#include "../Header.h"

/*

Given a file containing a list of ip addresses that have lost their dots(.'s), write a program to find the ip addresses,
 assume ipv4. input: 11111 output. 1.1.1.11, 11.1.1.1, etc
*/

void fillDots(string str, int index, int prevNumber, string curResult, vector<string> &results)
{
    if (index == str.length())
    {
        results.push_back(curResult);
        return;
    }

    if (prevNumber != -1)
    {
        fillDots(str, index + 1, -1, curResult + '.' + '0', results);
    }
    if (prevNumber == -1)
        prevNumber = 0;

    prevNumber = prevNumber * 10 + (str[index] - '0');
    if (prevNumber <= 255)
        fillDots(str, index + 1, prevNumber, curResult + str[index], results);
}