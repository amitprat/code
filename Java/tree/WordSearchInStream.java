package programs.tree;

import java.util.HashMap;
import java.util.Map;

public class WordSearchInStream {
    public static void test() {
        String[] words = {"ok", "test", "one", "try", "trying"};
        Character[] stream = {'a', 'b', 'c', 'o', 'k', 'd', 'e', 'f', 't', 'r', 'y', 'i', 'n', 'g' };

        WordSearchInStream obj = new WordSearchInStream();
        obj.printWords(words, stream);
    }

    private void printWords(String[] words, Character[] stream) {
        Trie trie = new Trie();
        for (var word : words) {
            trie.insert(word);
        }

        Map<Trie.Node, String> map = new HashMap<>();
        for (Character ch : stream) {
            Map<Trie.Node, String> nextMap = new HashMap<>();
            for (var entry : map.entrySet()) {
                if (entry.getKey().isEnd) {
                    System.out.println(entry.getValue());
                }

                Trie.Node next = trie.getNext(entry.getKey(), ch);
                if (next != null) {
                    nextMap.put(next, entry.getValue() + ch);
                }
            }
            map = nextMap;

            Trie.Node next = trie.getNext(ch);
            if (next != null) {
                map.put(next, Character.toString(ch));
            }
        }

        for (var entry : map.entrySet()) {
            if (entry.getKey().isEnd) {
                System.out.println(entry.getValue());
            }
        }
    }

    class Trie {
        Node root = null;

        class Node {
            Node[] children = new Node[26];
            boolean isEnd = false;
        }

        void insert(String word) {
            root = insert(root, word, 0);
        }

        boolean contains(String word) {
            return contains(root, word, 0);
        }

        Node getNext(Character next) {
            return getNext(root, next);
        }

        Node getNext(Node cur, Character next) {
            if (cur == null) return null;
            return cur.children[next - 'a'];
        }

        Node insert(Node node, String word, int index) {
            if (node == null) node = new Node();
            if (index == word.length()) {
                node.isEnd = true;
                return node;
            }

            node.children[getPos(word, index)] = insert(node.children[getPos(word, index)], word, index + 1);

            return node;
        }

        boolean contains(Node node, String word, int index) {
            if (node == null) return false;
            if (index == word.length()) return node.isEnd;

            return contains(node.children[getPos(word, index)], word, index + 1);
        }

        int getPos(String word, int index) {
            return word.charAt(index) - 'a';
        }
    }
}
