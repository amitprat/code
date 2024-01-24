package programs.careercup;

/*
https://www.careercup.com/question?id=5758790009880576

Given a string which only contains lowercase. You need delete the repeated letters only leave one, and try to make the lexicographical order of new string is smallest.
i.e:
bcabc
You need delete 1 'b' and 1 'c', so you delete the first 'b' and first 'c', the new string will be abc which is smallest.

ps: If you try to use greedy algorithm to solve this problem, you must sure that you could pass this case:
cbacdcbc. answer is acdb not adcb

I can't solve this problem well and the interviewer said that you can scan the string twice. First scan is do some preprocess, and the second is to get the answer, but I really can't come up this idea.

UPD: I could find a way to optimize my code to O(N). Main idea is the same. I added updated part after my old explanations


Here's my O(N^2) idea which is absoloutly true:D ( proved, and tested with many random test cases)

Let's say we have string S:

I define next[i] = next position (after i) which is equal to S[i], if there is not, -1.

So if S="bacdbcb", next={4,-1,5,-1,6,-1,-1}

Now, I iterate through S, from left to right, and at each position, I decide whether to pick the current character or not. Also, there is an array called visited, which visited[i]=true means character i has been picked.

Greedy part:
If we are at position i, (let's say x=S[i]), we need to find the first j>i which next[j]=-1 and visited[j]=false, call it y=S[j]. Also I need to know what is the smallest character from i to j, call it z( and obviously visited[z]=false). If the smallest character in between, z, is bigger than x, then add x to answer and visited[x] = true, otherwise skip x and continue to i+1.

Here's the reason:
We have something like this.
....x .... z ... y ...
It means definietly y is the part of answer string (since its next is -1). So if there is nothing smaller than x between x and y (including y), for sure it's better to choose x to have a smaller lexicographic answer.(note that all the characters between x and y have another copy after y, since y is the first position which has no next, so it's safe to postpone picking them, if needed). On the other hand, if z<x for sure it's better to skip x and choose another x later on.

Because at each position i, we need to see, in worst case, all next characters, so time complexity is O(N^2).

I couldn't find a way to find y in O(logn) or O(1), if there is any suggestion please let me know.

Also, I really really enjoyed the problem and it took me a day to come up with this solution!
 */

public class LexographicSmallestStringWithoutRepeatingChars {
    public static void test() {
        LexographicSmallestStringWithoutRepeatingChars obj = new LexographicSmallestStringWithoutRepeatingChars();
        String str = "cbacdcbc";
        String res = obj.smallestStringWithoutRepeatingChars(str);
        System.out.println("Result: " + res);
    }

    private String smallestStringWithoutRepeatingChars(String str) {
        int[] lastIndex = new int[26];
        int[] nextIndex = new int[26];

        // set the last index of each character in string as -1
        for(int i=0;i<26;i++) {
            lastIndex[i] = -1;
        }

        // Update the nextIndex of character at position 'i' to last index of character at this position
        for(int i=str.length()-1;i>=0;i--) {
            int idx = str.charAt(i)-'a';
            nextIndex[i] = lastIndex[idx];
            lastIndex[idx] = i;
        }

        boolean[] visited = new boolean[26];
        String result = "";
        for(int i=0;i<str.length();i++) {
            int idx = str.charAt(i) - 'a';
            if(visited[idx]) continue; // if this character already included, skip this

            // If this is last index for this character, then add this character to result
            if(nextIndex[i] == -1) {
                result += str.charAt(i);
                visited[idx] = true;
            } else { // otherwise, find the next smaller character
                int j = i+1;
                char smaller = str.charAt(i);
                while(j<str.length()) {
                    idx = str.charAt(j) - 'a';
                    if(!visited[idx]) {
                        smaller = smaller < str.charAt(j) ? smaller : str.charAt(j);
                        if(nextIndex[idx] == -1) break;
                    }
                    j++;
                }

                // if the character at smaller position, then add character
                if(str.charAt(i) <= smaller) {
                    result += str.charAt(i);
                    visited[str.charAt(i)-'a'] = true;
                }
            }
        }

        return result;
    }
}
