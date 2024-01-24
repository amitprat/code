package programs.misc;

/*
Sparse number is an integer if there are no adjacent 1 in it's binary representation.
Like: 5 -> 101 (no adjacent 1)
9 -> 1001 (no adjacent 1)
while 6-> 110 is not sparse number.
Now you are given an integer find the NEXT BIGGER sparse number.Please mind 'it is next bigger'.
 */

/*
Not sure about sparse number but below code will give no adjacent 1. Can someone check

private static void nextSparse(int x) {
		for (int i = x + 1; i < Integer.MAX_VALUE; i++) {
			if ((i & (i * 2)) == 0) {
				System.out.println(i);
				return;
			}
		}
	}
 */
public class FindSparseNumbers {
    public static void test() {
        printMissing();
    }

    private static void printMissing() {
        for (int i = 1; i <= 100; i++) {
            if ((i & (i >> 1)) == 0) {
                System.out.println(i);
            }
        }
    }
}
