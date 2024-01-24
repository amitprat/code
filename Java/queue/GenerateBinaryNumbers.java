package programs.queue;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class GenerateBinaryNumbers {
    public static void test() {
        GenerateBinaryNumbers obj = new GenerateBinaryNumbers();
        int n = 10;
        var res = obj.generate(n);
        for (var s : res) System.out.print(s + " ");
        System.out.println();
    }

    List<String> generate(int n) {
        Queue<String> q = new LinkedList<>();
        List<String> out = new ArrayList<>();
        q.add("1");

        while (n-- != 0) {
            var val = q.poll();
            out.add(val);
            q.add(val + "0");
            q.add(val + "1");
        }

        return out;
    }
}
