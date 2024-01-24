package programs.careercup;

public class ValidateEquation {
    public static void test() {
        ValidateEquation obj = new ValidateEquation();
        char[][] equal = new char[][]{{'A', 'B'}, {'B', 'D'}, {'C', 'D'}, {'F', 'G'}, {'E', 'H'}, {'H', 'C'}};
        char[][] unequal = new char[][]{{'A', 'C'}, {'D', 'H'}, {'F', 'A'}};

        System.out.println(obj.isValid(equal, unequal));
    }

    boolean isValid(char[][] equal, char[][] unequal) {
        int[] map = new int[26];
        for (int i = 0; i < 26; i++) map[i] = i;

        for (var val : equal) {
            union(map, val[0] - 'A', val[1] - 'A');
        }

        for (var val : unequal) {
            if (isConnected(map, val[0] - 'A', val[1] - 'A')) {
                System.out.println(val[0] + " and " + val[1] + " are connected.");
                return false;
            }
        }

        return true;
    }

    boolean isConnected(int[] map, int p, int q) {
        int rootP = find(map, p);
        int rootQ = find(map, q);

        return map[rootP] == map[rootQ];
    }

    void union(int[] map, int p, int q) {
        int rootP = find(map, p);
        int rootQ = find(map, q);
        map[rootP] = rootQ;
    }

    int find(int[] map, int p) {
        while (p != map[p]) p = map[p];
        return p;
    }
}
