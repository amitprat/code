package Java.string;

import Java.types.Pair;

/*
https://www.careercup.com/question?id=5389627422670848

Given two (dictionary) words as Strings, determine if they are isomorphic. Two words are called isomorphic
if the letters in one word can be remapped to get the second word. Remapping a letter means replacing all
occurrences of it with another letter while the ordering of the letters remains unchanged. No two letters
may map to the same letter, but a letter may map to itself.

Example:
given "foo", "app"; returns true
we can map 'f' -> 'a' and 'o' -> 'p'
given "bar", "foo"; returns false
we can't map both 'a' and 'r' to 'o'

given "turtle", "tletur"; returns true
we can map 't' -> 't', 'u' -> 'l', 'r' -> 'e', 'l' -> 'u', 'e' -'r'

given "ab", "ca"; returns true
we can map 'a' -> 'c', 'b'

Hash <char, firstseenindex> for each string.
The encoding of first seen indices should match.

E.g. Foo and app both encode to 011
Abcd and hole both encode to 0123

Hate and hell do not match
As encodings are 0123 and 0122
 */
public class IsomorphicString {
    public static void test() {
        IsomorphicString obj = new IsomorphicString();
        Pair<String, String> input1 = new Pair<>("foo", "app");
        Pair<String, String> input2 = new Pair<>("bar", "foo");
        Pair<String, String> input3 = new Pair<>("turtle", "tletur");
        Pair<String, String> input4 = new Pair<>("ab", "ca");

        System.out.println(obj.isomorphic(input1.first, input1.second));
        System.out.println(obj.isomorphic(input2.first, input2.second));
        System.out.println(obj.isomorphic(input3.first, input3.second));
        System.out.println(obj.isomorphic(input4.first, input4.second));
    }

    boolean isomorphic(String first, String second) {
        var dist1 = getDistribution(first);
        var dist2 = getDistribution(second);

        System.out.println("Dist1:" + dist1 + ", " + "Dist2:" + dist2);

        for (int i = 0; i < dist1.length(); i++) {
            if (dist1.charAt(i) != dist2.charAt(i))
                return false;
        }

        return true;
    }

    private String getDistribution(String str) {
        StringBuilder sb = new StringBuilder();

        int[] arr = new int[256];
        int i = 0;
        for (var ch : str.toCharArray()) {
            i++;

            // encode array such that if this char is not seen, then keep its value as
            // current index.
            // if seen, the use the previous seen index.
            arr[ch] = (arr[ch] == 0 ? i : arr[ch]);
            if (arr[ch] != 0)
                sb.append(arr[ch]);
        }

        return sb.toString();
    }
}
