package Java.dp;

import java.util.HashMap;

public class ProbabilityOfBeingAlive {
    public static void test() {
        ProbabilityOfBeingAlive obj = new ProbabilityOfBeingAlive();
        int n = 8;
        int steps = 12;
        int x = 3, y = 5; // point
        HashMap<String, Double> memo = new HashMap<>();

        double prob = obj.probabilityOfAlive(3, 5, n, steps, memo);
        System.out.println("Probability of being alive: " + prob);
    }

    private double probabilityOfAlive(int x, int y, int n, int steps, HashMap<String, Double> memo) {
        // if no more steps can be taken, then are already within the limits.
        if (0 == steps) {
            return 1.0;
        }

        // if the state is already calculated, return from HashMap
        String key = "";
        {
            StringBuffer sb = new StringBuffer();
            sb.append(x + ",");
            sb.append(y + ",");
            sb.append(steps + ".");
            key = sb.toString();
        }
        if (memo.containsKey(key)) {
            return memo.get(key);
        }

        // calculate the probability of a state
        double probability = 0.0;
        if (x > 0) {
            probability += 0.25 * probabilityOfAlive(x - 1, y, n, steps - 1, memo);
        }
        if (x < (n - 1)) {
            probability += 0.25 * probabilityOfAlive(x + 1, y, n, steps - 1, memo);
        }
        if (y > 0) {
            probability += 0.25 * probabilityOfAlive(x, y - 1, n, steps - 1, memo);
        }
        if (y < (n - 1)) {
            probability += 0.25 * probabilityOfAlive(x, y + 1, n, steps - 1, memo);
        }

        // save the result to HashMap and return
        memo.put(key, probability);

        return probability;
    }
};