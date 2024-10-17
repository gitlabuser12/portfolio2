import java.util.Arrays;
import java.util.HashMap;

public abstract class Main {

    public static void main(String[] args) {
        int[] arr = {37, 12, 28, 9, 100, 56, 80, 5, 12};
        int[] sortedArr = arr.clone();  // Clone the array to preserve the original
        Arrays.sort(sortedArr);         // Sort the cloned array

        HashMap<Integer, Integer> rankMap = new HashMap<>();

        // Assign ranks to each element
        int rank = 1;
        for (int num : sortedArr) {
            if (!rankMap.containsKey(num)) {
                rankMap.put(num, rank++);
            }
        }

        // Create an array to store ranks corresponding to the original array
        int[] rankArr = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            rankArr[i] = rankMap.get(arr[i]);
        }

        // Output the rank array
        System.out.println(Arrays.toString(rankArr));



    }

}