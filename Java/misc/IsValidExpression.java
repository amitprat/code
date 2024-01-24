package programs.misc;

import programs.types.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/*
Q: If you were given a series of equations e.g. [A = B, B = D, C = D, F = G, E = H, H = C]
and then another series [A != C, D != H, ..., F != A ]

Check whether the equations combined is valid.

For the example given, your program should return 'invalid', because the first series implies that A = C,
which contradicts the statement A != C in the second series.
 */
public class IsValidExpression {
    public static void test() {
        IsValidExpression obj = new IsValidExpression();
        List<Pair<String, String>> exprs = new ArrayList<>() {{
            add(new Pair<>("A", "B"));
            //add(new Pair<String, String>("B", "D"));
            add(new Pair<>("C", "D"));
            //add(new Pair<String, String>("F", "G"));
            add(new Pair<>("E", "H"));
            //add(new Pair<String, String>("H", "C"));
        }};

        List<Pair<String, String>> negExprs = new ArrayList<>() {
            {
                add(new Pair<>("A", "F"));
            }
        };

        UnionFind uf = new UnionFind();
        for (var expr : exprs) {
            uf.union(expr.first, expr.second);
        }

        for (var expr : negExprs) {
            if (uf.connected(expr.first, expr.second)) {
                System.out.println("Invalid expression");
            }
        }

        System.out.println("Valid expression");

        for (char a = 'A'; a <= 'F'; a++) {
            for (char b = (char) (a + 1); b <= 'F'; b++) {
                System.out.println(uf.find(Character.toString(a)) + " " + uf.find(Character.toString(b)));
            }
        }
    }
}

class UnionFind {
    private final HashMap<String, String> map = new HashMap<>();

    public boolean union(String p, String q) {
        if (!map.containsKey(p)) map.put(p, p);
        if (!map.containsKey(q)) map.put(q, q);

        var rootP = find(p);
        var rootQ = find(q);

        if (rootP == rootQ) return false;

        map.put(rootP, rootQ);

        return true;
    }

    public String find(String p) {
        while (p != map.get(p)) {
            p = map.get(p);
        }
        return p;
    }

    public boolean connected(String p, String q) {
        return find(p) == find(q);
    }
}

/*
This is a 'merge set' question. Given a graph, figure out which nodes belong to the same connected component and put them into a set.
Since the input comes in as an edge set, UNION FIND will be a good way to solve this.

Initially every node sources to itself. As we read the statement X = Y, we point the source of Y to the source of X so that they join the same set. After all connected components are sorted out. We check the unequal statements X != Y. If any of the X, Y pairs do share the same source, then X != Y contradicts with the equal statements.

 public class CheckStatements {
    public boolean validStatements(char[][] equal, char[][] unequal) {
        int[] sets = new int[26];
        for(int i = 0; i < 26; i++) {
            sets[i] = i;
        }

        for(char[] pair: equal) {
            mergeSets(sets, pair[0] - 'A', pair[1] - 'A');
        }
        for(int i = 0; i < 26; i++) {
            findSrc(sets, i);
        }

        for(char[] pair: unequal) {
            if(sets[pair[0] - 'A'] == sets[pair[1] - 'A']) return false;
        }
        return true;
    }

    private int findSrc(int[] sets, int i) {
        int src = i;
        while(src != sets[src]) {
            src = sets[src];
        }
        int tmp;
        while (i != sets[i]) {
            tmp = sets[i];
            sets[i] = src;
            i = tmp;
        }
        return src;
    }

    private void mergeSets(int[] sets, int a, int b) {
        int srcA = findSrc(sets, a);
        int srcB = findSrc(sets, b);
        sets[srcB] = srcA;
    }
}
 */