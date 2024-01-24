#include "../header.h"

/*
https://careercup.com/question?id=14360665

Answers
Given two strings .Print all the interleavings of the two strings.
Interleaving means that the if B comes after A .It should also come after A in the interleaved string.
ex-
AB and CD
ABCD
ACBD
ACDB
CABD
CADB
CDAB

public static void printInterleavings(String s1,String s2){
    printInterleavings(s1,s2,"");
}


public static void printInterleavings(String s1,String s2,String soFar){
    if((s1==null||s1.length()==0) && (s2==null||s2.length() == 0))
        return;
    if(s1==null || s1.length()==0){
        System.out.print(" " + soFar + s2 +" ");
        return;
    }
    if(s2==null || s2.length()==0){
        System.out.print(" " + soFar + s1 +" ");
        return;
    }
    printInterleavings(s1.substring(1), s2, soFar + s1.charAt(0));
    printInterleavings(s1, s2.substring(1), soFar + s2.charAt(0));

}
*/
class FindInterleavingOfTwoStrings {
    void printInterleaving(string& s1, string& s2, int n, int m) {
        if (n == 0 && m == 0) {
            print(out);
            return;
        }

        if (n == 0) return;
        if (m == 0) return;

        printInterleaving(s1, s2, n, m - 1);
        printInterleaving(s1, s2, n - 1, m);
    }

   private:
    void printInterleavings(std::string res, std::string s1, std::string s2, int m, int n, int i) {
        if (m == 0 && n == 0)
            std::cout << res << std::endl;

        if (m != 0)
            printInterleavings(res + s1[i], s1.substr(1), s2, m - 1, n, i + 1);

        if (n != 0)
            printInterleavings(res + s2[i], s1, s2.substr(1), m, n - 1, i + 1);
    }

    void printInterleavingsWrapper(std::string s1, std::string s2) {
        printInterleavings("", s1, s2, s1.size(), s2.size(), 0);
    }
};