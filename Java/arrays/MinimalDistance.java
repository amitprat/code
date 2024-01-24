package Java.arrays;
/*
 * https://www.careercup.com/question?id=6273553081040896
 * Given a string and two words which are present in the string, find the minimum distance between the words
    Eg: "the brown qucik frog quick the", "the" "quick" O/P -> 1
    "the quick the brown quick brown the frog", "the" "the" O/P -> 2
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import Java.types.Triplet;

public class MinimalDistance {
    public static void test() {
        Map<String, List<Integer>> wordPositionMap = new HashMap<>();
        wordPositionMap.put("job", Arrays.asList(5, 9, 17));
        wordPositionMap.put("in", Arrays.asList(4, 13, 18));
        wordPositionMap.put("google", Arrays.asList(8, 19, 21));

        System.out.println(getMinimalDistance(wordPositionMap));
    }

    private static boolean getMinimalDistance(Map<String, List<Integer>> wordPositionMap) {
        PriorityQueue<Triplet<Integer,Integer,Integer>> pq = new PriorityQueue<>((a, b) -> a.first - b.first);

        int index = 0;
        List<Integer> values = new ArrayList<>();
        for(var entry : wordPositionMap.entrySet()) {
            if(entry.getValue().size() > 0) {
                var val = entry.getValue().get(0);
                values.add(val);

                pq.add(new Triplet<Integer,Integer,Integer>(val, index, 0));
            }
            index++;
        }

        int mnValueIndex = min(values);
        int mxValueIndex = max(values);
        int minDistance =  values.get(mxValueIndex) - values.get(mnValueIndex);
        while(!pq.isEmpty()) {
            var top = pq.poll();
            values.set(mnValueIndex, top.first);

        }
    }

    private int minimumDistance(String str) {
        
    }
}
