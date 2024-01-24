package programs.string;

/*
Given a string (for example: "a?bc?def?g"), write a program to generate all the possible strings by replacing ? with 0 and 1.
Example:
Input : a?b?c?
Output: a0b0c0, a0b0c1, a0b1c0, a0b1c1, a1b0c0, a1b0c1, a1b1c0, a1b1c1.


No Recursion needed.

Complexity: O(n) * no of combinations

The simplest way to solve this is to consider the number of diff combinations (num_of_comb) and representing that in binary starting from 0 to (num_of_comb - 1).

Ex a?b?c? has 8 comb. i.e 2^3 . i.e. 2 power no of '?'s. Obviously the possible combinations are 000, 001, 010, ..... 110, 111.

Complexity: O(n) * no of combinations.
O(n) to find no of '?'s.

Down below is the complete working code with minor description along. Comment if you can improvise further.


#include <iostream>
#include <cmath>
using namespace std;


void stringReplace ( char *str )
{
  char *temp = str;
  int count = 0, num_of_comb = 0, value = 0;

  while ( *temp ) {
    if ( *temp == '?' )
      count++;
    temp++;
  }
  temp = str;

  num_of_comb = pow(2,count);       // count the num of combinations
  cout << "There are " << num_of_comb << " different possible combinations";

  while ( value < num_of_comb ) {
    cout << endl;
    int calc = value;

    while ( *temp ) {
            if ( *temp == '?' ) {
            char ch = ( calc % 2 ) ? '1' : '0';
            calc /= 2;
            cout << ch << flush;  // do use 'flush' instead of unwanted 'newline' on Linux console to flush the buffer
            }

            else cout << *temp << flush;

            temp++;
            }

            temp = str;
            value++;
            }
            }


            int main ()
            {
            char A[] = "????";      // makes it easy to see the combinations. You could obviously add letters
            stringReplace(A);
            while (1);
            }
 */

import java.util.ArrayList;
import java.util.List;

public class GenerateAllPossibleStrings {
    public static void test() {
        GenerateAllPossibleStrings obj = new GenerateAllPossibleStrings();
        String input = "a?bc?def?g";
        List<String> output = obj.generateCombinationsRecursion(input);
        System.out.println(output);
    }

    // Total Time = O(2^k)
    private List<String> generateCombinations(String input) {
        List<String> result = new ArrayList<>();
        List<Integer> positions = new ArrayList<>();
        // Time = O(n)
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == '?')
                positions.add(i);
        }
        double count = Math.pow(2, positions.size());
        // Time = O(2^k)
        for (int cnt = 0; cnt < count; cnt++) {
            char[] cur = input.toCharArray();
            // Time = O(k)
            for (int j = 0; j < positions.size(); j++) {
                int shift = positions.size() - j - 1;
                if ((cnt & (1 << shift)) == 0) cur[positions.get(j)] = '0';
                else cur[positions.get(j)] = '1';
            }
            result.add(new String(cur));
        }
        return result;
    }

    private List<String> generateCombinationsRecursion(String input) {
        List<String> result = new ArrayList<>();
        generateCombinationsRecursion(input.toCharArray(), result, input.length() - 1);
        return result;
    }

    private void generateCombinationsRecursion(char[] input, List<String> result, int pos) {
        if (pos < 0) return;
        if (pos == 0) {
            result.add(new String(input));
            return;
        }
        if (input[pos] != '?') {
            generateCombinationsRecursion(input, result, pos - 1);
            return;
        }
        input[pos] = '0';
        generateCombinationsRecursion(input, result, pos - 1);
        input[pos] = '1';
        generateCombinationsRecursion(input, result, pos - 1);
        input[pos] = '?';
    }
}
