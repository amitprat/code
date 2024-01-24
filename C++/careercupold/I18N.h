#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=5733696185303040
i18n (where 18 stands for the number of letters between the first i and the last n in the word “internationalization,”) Wiki it.
Generate all such possible i18n strings for any given string. for eg. "careercup"=>"c7p","ca6p","c6up","car5p","ca5up","care4p","car4up","caree3p","care3up"..
till the count is 0 which means its the complete string again.
*/

class I18N
{
public:
	static void test() {
		string str = "careercup";

		print(str);
	}

	static void print(string str) {
		int n = str.length();
		for (int i = n - 2; i >= 1; i--) { // always have atleast one character on left and one on right
			int rem = n - i;
			for (int k = 1; k < rem; k++)
			{
				string first = str.substr(0, k); // print the first character(s)
				string middle = to_string(i); // integers inbetween
				string second = str.substr(n - (rem - k), rem - k); // print the last character(s)
				cout << first << middle << second << endl;
			}
		}
	}
};