package Java.arrays;

public class TrappedRainWater {
    public static void test() {
        TrappedRainWater obj = new TrappedRainWater();

        int[] hist = { 6, 2, 5, 4, 5, 1, 6 };
        var trappedWater = obj.trappedRainWater(hist);
        System.out.println("Trapped water = " + trappedWater);
    }

    public int trappedRainWater(int[] hist) {
        int l = 0, r = hist.length - 1;
        int edgeLevel = 0;
        int water = 0;
        while (l < r) {
            int currentLevel = hist[l] < hist[r] ? hist[l++] : hist[r--];
            edgeLevel = Math.max(edgeLevel, currentLevel);

            water += edgeLevel - currentLevel;
        }

        return water;
    }
}
