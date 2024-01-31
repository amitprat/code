package Java.maths;

import Java.types.Pair;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Power {
    static Map<String, Double> cache = new HashMap<>();

    public static void test() {
        Runtime.getRuntime().addShutdownHook(new ForceClosedMessage());

        Power obj = new Power();
        List<Pair<Integer, Integer>> inputs = Arrays.asList(
                new Pair<Integer, Integer>(0, 0),
                new Pair<Integer, Integer>(1, 0),
                new Pair<Integer, Integer>(2, 0),
                new Pair<Integer, Integer>(0, 1),
                new Pair<Integer, Integer>(0, 2),
                new Pair<Integer, Integer>(2, -1),
                new Pair<Integer, Integer>(-2, 1),
                new Pair<Integer, Integer>(-2, 2),
                new Pair<Integer, Integer>(5, -3),
                new Pair<Integer, Integer>(-3, 5),
                new Pair<Integer, Integer>(10, -10),
                new Pair<Integer, Integer>(-10, 10),
                new Pair<Integer, Integer>(50, 7));

        for (var in : inputs) {
            System.out.println("Power of " + in + "=" + obj.power(in.first, in.second));
        }
    }

    private double power(Integer first, Integer second) {
        if (first == 0)
            return first;
        if (second == 0)
            return first;

        if (first < 0)
            return (second % 2 != 0) ? -_power(-first, second) : _power(-first, second);
        if (second < 0) {
            var t = _power(first, -second);
            System.out.print("t :1/" + t + ", ");
            return 1.0 / t;
        }
        return _power(first, second);
    }

    private double _power(int val, int pow) {
        String key = val + "^" + pow;
        if (cache.containsKey(key))
            return cache.get(key);
        if (pow == 1)
            return val;
        
        double cur = _power(val, pow / 2);
        cache.put(key, cur);
        
        return pow % 2 == 1 ? val * cur * cur : cur * cur;
    }

    static class ForceClosedMessage extends Thread {
        public void run() {
            System.out.println(cache);
        }
    }
}
