#include "../header.h"

/*
https://careercup.com/question?id=6234634354425856

Given "n", generate all valid parenthesis strings of length "2n".

Example:
Given n=2

Output:
(())
()()

The code prints all forms without duplicates. This question (solution) is in "Cracking the coding interview" Book.

def paren(left,right,string):
    if(left == 0 and right == 0):
        print string
    if(left>right):
        return
    if (left > 0):
        paren(left-1,right,string+"(")
    if (right > 0):
        paren(left,right-1,string+")")

def parentheses(n):
    paren(n/2,n/2,"")

parentheses(6)
output:
((()))
(()())
(())()
()(())
()()()
*/

class GenerateParentheses {
   public:
    static void test() {
        GenerateParentheses obj;

        START_METHOD()
        obj.generate(3, 3, "");
        END_METHOD()
    }

    void generate(int l, int r, string str) {
        if (l < 0 || r < 0 || r < l) return;
        if (l == 0 && r == 0) {
            cout << str << " ";
            cout << endl;
        }

        generate(l - 1, r, str + "(");
        generate(l, r - 1, str + ")");
    }
};