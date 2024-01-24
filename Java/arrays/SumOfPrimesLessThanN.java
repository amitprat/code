package programs.arrays;

public class SumOfPrimesLessThanN {
    public static void test() {
        int n = 20;
        SumOfPrimesLessThanN obj = new SumOfPrimesLessThanN();

        System.out.println(obj.sumOfPrimes(n));
    }

    private int sumOfPrimes(int n) {
        boolean[] arr = new boolean[n];

        int curSum = 0;
        for (int i = 2; i < n; i++) {
            if (!arr[i]) {
                curSum += i;
                for (int j = 2; j * i < n; j++) {
                    arr[j * i] = true;
                }
            }
        }

        return curSum;
    }
}
