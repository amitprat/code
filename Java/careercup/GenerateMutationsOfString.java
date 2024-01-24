package programs.careercup;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

import static java.util.Map.entry;

public class GenerateMutationsOfString {
    public static void test() {
        GenerateMutationsOfString obj = new GenerateMutationsOfString();
        Map<Character, List<Character>> M = Map.ofEntries(
                entry('f', Arrays.asList('F', '4')),
                entry('b', Arrays.asList('B', '8'))
        );
        String S = "fab";

        obj.generateMutations(S, 0, M, "");
    }

    private void generateMutations(String s, int index, Map<Character, List<Character>> m, String out) {
        if (index == s.length()) {
            System.out.println(out);
            return;
        }

        generateMutations(s, index + 1, m, out + s.charAt(index));
        if (!m.containsKey(s.charAt(index))) return;
        for (var e : m.get(s.charAt(index))) {
            generateMutations(s, index + 1, m, out + e);
        }
    }
}
