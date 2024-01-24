#include "../Header.h"

/*
https://www.careercup.com/question?id=18460667

Eliminate all ‘b’ and ‘ac’ in an array of characters, you have to replace them in-place, and you are only allowed to iterate over the char array once.

Examples:
abc -> ac
ac->''
react->rt
*/

//It can be solved using two pointers thats it :-)

void replace(char *str)
{
    int i = 0;
    char *q = str;
    while (*q)
    {
        if (*q == 'b')
            q++;
        else
        {
            if (*q == 'c' && (str[i - 1] == 'a' && i > ; 0))
            {
                q++;
                i--;
            }

            else
            {
                str[i] = *q;
                q++;
                i++;
            }
        }
    }
    str[i] = '\0';
}

// Mine
string remove(string str)
{
    int i = 0, j = 0;
    while (j < str.length())
    {
        if (str[j] == 'b')
            j++;
        else if (str[j] == 'c' && (j > 0 && str[i - 1] == 'a'))
        {
            j++;
            i--;
        }
        else
            str[i++] = str[j++];
    }

    return str.substr(0, i);
}

int main()
{
    string str = "babcaaabcccbccabbc";
    str = remove(str);

    cout << str << endl;

    return 0;
}
