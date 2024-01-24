#include "../Header.h"

/*
Given a string and array of strings, find whether the array contains a string with one character difference from the given 
string. Array may contain string of different lengths.

Ex: Given string


banana
and array is


[bana, apple, banaba, bonanza, banamf]
and the outpost should be true as banana and banaba are one character difference.
*/

/*
We can put all the words in hashset, and then for every character in input word, try to change it and lookup in hashset. 
overall complexity O(ALPH * N), where N is the length of word and ALPH is the size of alphabet. Usually we skip constants 
in big O notation, so the complexity O(N)
*/