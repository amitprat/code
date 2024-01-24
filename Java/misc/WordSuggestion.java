package programs.misc;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class WordSuggestion {
    Node root = null;
    int[][] freqMap = new int[64][26];

    public static void test() {
        WordSuggestion obj = new WordSuggestion();
        List<String> words = Arrays.asList("abc", "bcd", "cba","bcda","acbd","acdb","aaaa","abcc","cccc","bbbb","bbbd");
        obj.insert(words);

        System.out.println(obj.suggest(0));
        System.out.println(obj.suggest(1));
        System.out.println(obj.suggest(2));
    }

    private void insert(List<String> words) {
        for (var word : words) {
            root = insert(root, word, 0);
        }
    }

    private Node insert(Node node, String word, int pos) {
        if (node == null) node = new Node();
        node.freq++;
        if (pos == word.length()) {
            node.isEnd = true;
            return node;
        }

        int p = word.charAt(pos) - 'a';
        freqMap[pos][p]++;
        node.children[p] = insert(node.children[p], word, pos + 1);

        return node;
    }

    private Set<Character> suggest(int pos) {
        Set<Character> result = new HashSet<>();
        suggest(root, 0, pos, result);

        return result;
    }

    private void suggest(Node node, int pos, int target, Set<Character> result) {
        if (node == null) return;

        int mx = 0;
        for (int i = 0; i < freqMap[pos].length; i++) {
            mx = Math.max(mx, freqMap[pos][i]);
        }
        for (int i = 0; i < 26; i++) {
            if (freqMap[pos][i] >= mx) {
                if (pos == target) {
                    result.add((char) ('a' + i));
                } else {
                    suggest(node.children[i], pos + 1, target, result);
                }
            }
        }
    }

    class Node {
        int freq = 0;
        boolean isEnd = false;
        Node[] children = new Node[26];
    }
}
