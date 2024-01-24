package programs.string;

import programs.types.Pair;

/*
Hash <char, firstseenindex> for each string.

The encoding of first seenindices shud match.

E.g. Foo and app both encode to 011
Abcd and hole both encode to 0123

Hate and hell do not match
As encodings are 0123 and 0122

def string_color_distribution(s):
    max_color_so_far = -1
    color_mapping = {}
    color_distribution = []
    for c in s:
        if c in color_mapping:
            curr_color = color_mapping[c]
        else:
            curr_color = max_color_so_far + 1
            max_color_so_far += 1
            color_mapping[c] = curr_color
        color_distribution.append(curr_color)
    return color_distribution

def are_isomorphs(s1, s2):
    if len(s1) != len(s2) or len(set(a)) != len(set(b)):
        return False
    s1_cd = string_color_distribution(s1)
    s2_cd = string_color_distribution(s2)

    for i, color in enumerate(s1_cd):
        if color != s2_cd[i]:
            return False
    return True

a = raw_input()
b = raw_input()
print are_isomorphs(a,b)
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

    private String getDistribution(String str) {
        StringBuilder sb = new StringBuilder();
        int[] arr = new int[256];
        int i = 0;
        for (var ch : str.toCharArray()) {
            i++;
            arr[ch] = (arr[ch] == 0 ? i : arr[ch]);
            if (arr[ch] != 0) sb.append(arr[ch]);
        }
        return sb.toString();
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
}
