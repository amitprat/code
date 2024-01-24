#include "../header.h"

/*
https://careercup.com/question?id=5659801074794496

You are given a string "abc" which is encoded like "123" where alphabets are mapped like a => 1 to z => 26. Now find out how many string can be formed by reverse engineering encode string "123".

For ex. given string "123" we can form 3 string "abc"(1,2,3), "lc" (i.e 12,3), "aw"(1,23).

for string "1234" we have following possible combinations, I might be missing some of them but you get the idea

{12, 3, 4}
{1, 23, 4}
{1, 2, 3, 4}

bool isValid(string s){
        istringstream ibuf(s);
        int num;
        ibuf >> num;
        if(num>=1 && num <=26)
                return true;
        else
                return false;
}
int numEncoding(string s){
        if(s.length()==0) return 1;
        if(s.length()==1) return 1;
        int num = 0;
        num += numEncoding(s.substr(1));
        if(isValid(s.substr(0,2)))
                num += numEncoding(s.substr(2));
        return num;
}
*/
class ValidEncodingOfNumberToAlphabets {
};