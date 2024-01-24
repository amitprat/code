#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=4774716350922752


In a language, there are only 4 characters h,i,r,e. and we have to write a function which takes a string as input and returns whether the given input string is a �valid word� or not.

Definition of valid word :
1. A given word is a valid word if it is of the form h^n i^n r^n e^n where n >=1. (eg: hhiirree)
2. Valid words has concatenation property i.e. if w1 and w2 are valid words w1w2 is also a valid word.


Let's make it an "ordered" alphabet array
by letting (compile time fixed or get from somewhere at runtime):
alpha[]={ your ordered list of characters in your alphabet }
M be size of your ordered alphabet (i.e., size of alphabet array above)

idea:


for(t=0,i = 0,count=0; i < str.length ; i++)
    if( str[i] == alpha[t % M] ) count++;
    else if( str[i] == alpha[++t % M] && count > 1) count=1;
    else return false;

return ( count >;1 && t==M-1) ? true : false;
*/

class CheckIfWordIsValid
{
public:
    static void test()
    {
        CheckIfWordIsValid obj;
        vector<char> dict = { 'h','i','r','e' };
        {
            string str = "hhiirreehhiirreehhiirree";

            bool res = obj.isValid(str, dict);
            cout << str << " is valid? " << res << endl;
        }

        {
            string str = "hhiirrhhiirreehhiirree";

            bool res = obj.isValid(str, dict);
            cout << str << " is valid? " << res << endl;
        }

        {
            string str = "hire";

            bool res = obj.isValid(str, dict);
            cout << str << " is valid? " << res << endl;
        }

        {
            string str = "hre";

            bool res = obj.isValid(str, dict);
            cout << str << " is valid? " << res << endl;
        }

        {
            string str = "ire";

            bool res = obj.isValid(str, dict);
            cout << str << " is valid? " << res << endl;
        }

        {
            string str = "hir";

            bool res = obj.isValid(str, dict);
            cout << str << " is valid? " << res << endl;
        }
    }

    bool isValid(string str, vector<char> dict)
    {
        int n = str.length();
        int m = dict.size();
        int j = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (str[i] == dict[j]) {
                cnt++;
                continue; // if match with current char, then continue
            }
            if (cnt > 1 && j < m - 1 && str[i] == dict[j + 1]) {
                cnt = 1;
                j++;
                continue; // if match with next char, then continue
            }
            if (cnt > 1 && j == m - 1) {
                j = 0;
                continue;
            }

            return false;
        }

        return cnt >= 1 && j == m - 1;
    }
};